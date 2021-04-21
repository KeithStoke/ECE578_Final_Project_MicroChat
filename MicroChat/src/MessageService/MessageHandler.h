#ifndef MICROCHAT_MESSAGEHANDLER_H
#define MICROCHAT_MESSAGEHANDLER_H

#include <iostream>
#include <string>
#include <regex>
#include <future>
#include <mongoc.h>
#include <bson/bson.h>
#include <iomanip>
#include <arpa/inet.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <nlohmann/json.hpp>
#include <jwt/jwt.hpp>

#include "../../gen-cpp/MessageService.h"
#include "../../gen-cpp/DatabaseService.h"

#include "../ClientPool.h"
#include "../ThriftClient.h"
#include "../logger.h"
#include "../utils_mongodb.h"

// Custom Epoch (January 1, 2018 Midnight GMT = 2018-01-01T00:00:00Z)
#define CUSTOM_EPOCH 1514764800000
#define MONGODB_TIMEOUT_MS 5000

namespace microchat
{

  using std::chrono::duration_cast;
  using std::chrono::milliseconds;
  using std::chrono::seconds;
  using std::chrono::system_clock;
  using namespace jwt::params;

  static int64_t current_timestamp = -1;
  static int counter = 0;

  //Taken from DeathStarBench Git repo
  static int GetCounter(int64_t timestamp)
  {
    if (current_timestamp > timestamp)
    {
      LOG(fatal) << "Timestamps are not incremental.";
      exit(EXIT_FAILURE);
    }
    if (current_timestamp == timestamp)
    {
      return counter++;
    }
    else
    {
      current_timestamp = timestamp;
      counter = 0;
      return counter++;
    }
  }

  //Taken from DeathStarBench Git repo
  std::string GenRandomString(const int len)
  {
    static const std::string alphanum =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(
        0, static_cast<int>(alphanum.length() - 1));
    std::string s;
    for (int i = 0; i < len; ++i)
    {
      s += alphanum[dist(gen)];
    }
    return s;
  }

  class MessageServiceHandler : public MessageServiceIf
  {
  public:
    MessageServiceHandler(
        std::mutex *,
        const std::string &,
        ClientPool<ThriftClient<DatabaseServiceClient>> *, mongoc_client_pool_t *);
    ~MessageServiceHandler() override = default;

    void ping(std::string &_return, const std::string &text) override;
    void ComposeMessage(std::string &_return, const std::string &text, const std::string &sender, const std::string &user) override;
    void ReadMessage(std::string &_return, const int64_t messageID, const std::string &username) override;
    void GetMessages(std::vector<Message> &_return, const std::string &username) override;
    void GetUnreadMessages(std::vector<Message> &_return, const std::string &username);
    void GetReadMessages(std::vector<Message> &_return, const std::string &username);

  private:
    std::string _machine_id;
    std::mutex *_thread_lock;
    ClientPool<ThriftClient<DatabaseServiceClient>> *_database_client_pool;
    mongoc_client_pool_t *_mongodb_client_pool;
  };

  // constructor
  MessageServiceHandler::MessageServiceHandler(std::mutex *thread_lock,
                                               const std::string &machine_id,
                                               ClientPool<ThriftClient<DatabaseServiceClient>> *database_client_pool,
                                               mongoc_client_pool_t *mongo_pool)
  {
    _thread_lock = thread_lock;
    _machine_id = machine_id;
    _database_client_pool = database_client_pool;
    std::cout << "Before Mongo Pool" << std::endl;
    _mongodb_client_pool = mongo_pool;
    std::cout << "After Mongo Pool" << std::endl;
  };

  void MessageServiceHandler::ping(std::string &_return, const std::string &text)
  {
    std::cout << "Ping says " << text << std::endl;
    _return = "Pong from MessageService";
  }

  void MessageServiceHandler::ComposeMessage(std::string &_return, const std::string &text, const std::string &sender, const std::string &user)
  {

    //create new Message object w/ list of recipients
    //create new SimpleMessage object w/ same messageID, username, READ/UNREAD status
    //store 1 Message and X SimpleMessage objects into mongoDB

    std::cout << "Compose new message..." << std::endl;

    std::string result;
    mongoc_client_t *mongodb_client = mongoc_client_pool_pop(
        _mongodb_client_pool);
    if (!mongodb_client)
    {
      ServiceException se;
      se.errorCode = ErrorCode::SE_MONGODB_ERROR;
      se.message = "Failed to pop a client from MongoDB pool";
      throw se;
    }
    auto collection = mongoc_client_get_collection(
        mongodb_client, "message", "message");

    // create messageID
    _thread_lock->lock();
    int64_t timestamp = duration_cast<milliseconds>(
                            system_clock::now().time_since_epoch())
                            .count() -
                        CUSTOM_EPOCH;
    int idx = GetCounter(timestamp);
    _thread_lock->unlock();

    std::cout << "timestamp is " << timestamp << std::endl;

    std::stringstream sstream;
    sstream << std::hex << timestamp;
    std::string timestamp_hex(sstream.str());
    if (timestamp_hex.size() > 10)
    {
      timestamp_hex.erase(0, timestamp_hex.size() - 10);
    }
    else if (timestamp_hex.size() < 10)
    {
      timestamp_hex =
          std::string(10 - timestamp_hex.size(), '0') + timestamp_hex;
    }
    // Empty the sstream buffer.
    sstream.clear();
    sstream.str(std::string());

    sstream << std::hex << idx;
    std::string counter_hex(sstream.str());

    if (counter_hex.size() > 3)
    {
      counter_hex.erase(0, counter_hex.size() - 3);
    }
    else if (counter_hex.size() < 3)
    {
      counter_hex = std::string(3 - counter_hex.size(), '0') + counter_hex;
    }
    std::string message_id_str = _machine_id + timestamp_hex + counter_hex;
    int64_t message_id = stoul(message_id_str, nullptr, 16) & 0x7FFFFFFFFFFFFFFF;
    ;
    LOG(debug) << "The message_id of the this request is " << message_id;
    std::cout << "The message_id of this request is... " << message_id << std::endl;

    //create new message query
    bson_error_t error;
    bson_t *new_doc = bson_new();
    BSON_APPEND_INT64(new_doc, "message_id", message_id);
    BSON_APPEND_UTF8(new_doc, "text", text.c_str());
    BSON_APPEND_UTF8(new_doc, "sender", sender.c_str());
    BSON_APPEND_UTF8(new_doc, "recipient", user.c_str());
    BSON_APPEND_INT64(new_doc, "timestamp", timestamp);
    BSON_APPEND_INT64(new_doc, "message_status", MessageStatus::type::UNREAD); //UNREAD = 0

    //attempt to insert
    if (!mongoc_collection_insert_one(
            collection, new_doc, nullptr, nullptr, &error))
    {
      std::cout << "Failed to insert new message " << message_id << " to MongoDB: " << error.message;
      ServiceException se;
      se.errorCode = ErrorCode::SE_THRIFT_HANDLER_ERROR;
      se.message = error.message;
      bson_destroy(new_doc);
      mongoc_collection_destroy(collection);
      mongoc_client_pool_push(_mongodb_client_pool, mongodb_client);
      throw se;
    }

    //if successful, return SUCCESS
    bson_destroy(new_doc);
    mongoc_collection_destroy(collection);
    mongoc_client_pool_push(_mongodb_client_pool, mongodb_client);

    _return = "Successfully created and sent message to user " + user;
  }

  void MessageServiceHandler::ReadMessage(std::string &_return, const int64_t messageID, const std::string &username)
  {
  }
  void MessageServiceHandler::GetMessages(std::vector<Message> &_return, const std::string &username)
  {
    //FIRST search users to see if username exists
    // if NOT, throw SE
    // else, search db for any messages that include 'username' in list of recipients
    //  grab messages and return to user so they can read them
  }

  void MessageServiceHandler::GetUnreadMessages(std::vector<Message> &_return, const std::string &username)
  {
    // Your implementation goes here
    printf("GetUnreadMessages\n");
  }

  void MessageServiceHandler::GetReadMessages(std::vector<Message> &_return, const std::string &username)
  {
    // Your implementation goes here
    printf("GetReadMessages\n");
  }

  /*
 * The following code which obtaines machine ID from machine's MAC address was
 * inspired from https://stackoverflow.com/a/16859693.
 */
  u_int16_t HashMacAddressPid(const std::string &mac)
  {
    u_int16_t hash = 0;
    std::string mac_pid = mac + std::to_string(getpid());
    for (unsigned int i = 0; i < mac_pid.size(); i++)
    {
      hash += (mac[i] << ((i & 1) * 8));
    }
    return hash;
  }

  int GetMachineId(std::string *mac_hash)
  {
    std::string mac;
    int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);
    if (sock < 0)
    {
      LOG(error) << "Unable to obtain MAC address";
      return -1;
    }

    struct ifconf conf
    {
    };
    char ifconfbuf[128 * sizeof(struct ifreq)];
    memset(ifconfbuf, 0, sizeof(ifconfbuf));
    conf.ifc_buf = ifconfbuf;
    conf.ifc_len = sizeof(ifconfbuf);
    if (ioctl(sock, SIOCGIFCONF, &conf))
    {
      LOG(error) << "Unable to obtain MAC address";
      return -1;
    }

    struct ifreq *ifr;
    for (
        ifr = conf.ifc_req;
        reinterpret_cast<char *>(ifr) <
        reinterpret_cast<char *>(conf.ifc_req) + conf.ifc_len;
        ifr++)
    {
      if (ifr->ifr_addr.sa_data == (ifr + 1)->ifr_addr.sa_data)
      {
        continue; // duplicate, skip it
      }

      if (ioctl(sock, SIOCGIFFLAGS, ifr))
      {
        continue; // failed to get flags, skip it
      }
      if (ioctl(sock, SIOCGIFHWADDR, ifr) == 0)
      {
        mac = std::string(ifr->ifr_addr.sa_data);
        if (!mac.empty())
        {
          break;
        }
      }
    }
    close(sock);

    std::stringstream stream;
    stream << std::hex << HashMacAddressPid(mac);
    *mac_hash = stream.str();

    if (mac_hash->size() > 3)
    {
      mac_hash->erase(0, mac_hash->size() - 3);
    }
    else if (mac_hash->size() < 3)
    {
      *mac_hash = std::string(3 - mac_hash->size(), '0') + *mac_hash;
    }
    return 0;
  }

}

#endif //MICROCHAT_MESSAGEHANDLER_H