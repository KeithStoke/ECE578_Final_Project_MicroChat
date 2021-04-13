#ifndef MICROCHAT_USERHANDLER_H
#define MICROCHAT_USERHANDLER_H

#include <iostream>
#include <string>
#include <regex>
#include <future>
#include <random>
#include <mongoc.h>
#include <bson/bson.h>
#include <iomanip>
#include <arpa/inet.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <nlohmann/json.hpp>
#include <jwt/jwt.hpp>

#include "../../gen-cpp/UserService.h"
#include "../../gen-cpp/DatabaseService.h"
#include "../../gen-cpp/FriendRecommendationService.h"

#include "../ClientPool.h"
#include "../ThriftClient.h"
#include "../logger.h"

// Custom Epoch (January 1, 2018 Midnight GMT = 2018-01-01T00:00:00Z)
#define CUSTOM_EPOCH 1514764800000
#define MONGODB_TIMEOUT_MS 1000

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

  class UserServiceHandler : public UserServiceIf
  {
  public:
    UserServiceHandler(
        std::mutex *,
        const std::string &,
        ClientPool<ThriftClient<DatabaseServiceClient>> *
        ClientPool<ThriftClient<FriendRecommendationServiceClient>> *);
    ~UserServiceHandler() override = default;

    void ping(std::string &_return, const int32_t id) override;
    void Login(std::string &_return, const std::string &username, const std::string &password) override;
    void CreateUser(std::string &_return, const std::string &username, const std::string &name, const std::string &password) override;
    void GetUserID(std::string &_return, const std::string &username) override;
    void Logout(std::string &_return, const std::string &username) override;

  private:
    std::string _machine_id;
    std::mutex *_thread_lock;
    ClientPool<ThriftClient<DatabaseServiceClient>> *_database_client_pool;
    ClientPool<ThriftClient<FriendRecommendationServiceClient>> *_friend_client_pool;
  };

  UserServiceHandler::UserServiceHandler(
      std::mutex *thread_lock,
      const std::string &machine_id,
      ClientPool<ThriftClient<DatabaseServiceClient>> *database_client_pool,
      ClientPool<ThriftClient<FriendRecommendationServiceClient>> *friend_client_pool)
  {
    _thread_lock = thread_lock;
    _machine_id = machine_id;
    _database_client_pool = database_client_pool;
    _friend_client_pool = friend_client_pool;
  };

  void UserServiceHandler::ping(std::string &_return, const int32_t id)
  {
    std::cout << "ID received was " << id << std::endl;
    std::string pong = "Pong from UserService";
    _return = pong;
  }

  void UserServiceHandler::Login(std::string &_return, const std::string &username, const std::string &password)
  {
    std::cout << "Login UserService Method" << std::endl;

    auto database_client_wrapper = _database_client_pool->Pop();
    if (!database_client_wrapper)
    {
      ServiceException se;
      se.errorCode = ErrorCode::SE_THRIFT_CONN_ERROR;
      se.message = "Failed to connect to database-service";
      throw se;
    }
    auto database_client = database_client_wrapper->GetClient();
    std::string user_id = "00000";
    try
    {
      //should return userID
      database_client->Login(user_id, username, password);
    }
    catch (...)
    {
      _database_client_pool->Push(database_client_wrapper);
      LOG(error) << "Failed to send call to database-service ";
      throw;
    }
    _database_client_pool->Push(database_client_wrapper);
    _return = "Login successful. Your userID is: " + user_id;



    auto friend_client_wrapper = _friend_client_pool->Pop();
    if (!friend_client_wrapper)
    {
      ServiceException se;
      se.errorCode = ErrorCode::SE_THRIFT_CONN_ERROR;
      se.message = "Failed to connect to friend-recommendation-service";
      throw se;
    }
    auto friend_client = friend_client_wrapper->GetClient();
    friend_client->onLogin(user_id, username, 1)
    _friend_client_pool->Push(database_client_wrapper);
    
  }

  void UserServiceHandler::CreateUser(std::string &_return, const std::string &username, const std::string &name, const std::string &password)
  {
    std::cout << "CreateUser UserService Method" << std::endl;

    //create userID
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
    std::string user_id_str = _machine_id + timestamp_hex + counter_hex;
    int64_t user_id = stoul(user_id_str, nullptr, 16) & 0x7FFFFFFFFFFFFFFF;
    ;
    LOG(debug) << "The user_id of the this request is " << user_id;
    std::cout << "The user_id of this request is... " << user_id << std::endl;

    auto database_client_wrapper = _database_client_pool->Pop();
    if (!database_client_wrapper)
    {
      ServiceException se;
      se.errorCode = ErrorCode::SE_THRIFT_CONN_ERROR;
      se.message = "Failed to connect to database-service";
      throw se;
    }
    auto database_client = database_client_wrapper->GetClient();

    std::string result = "DEFAULT";
    try
    {
      database_client->CreateUser(result, username, name, password, user_id);
    }
    catch (...)
    {
      _database_client_pool->Push(database_client_wrapper);
      LOG(error) << "Failed to send call to database-service ";
      throw;
    }

    _database_client_pool->Push(database_client_wrapper);
    if(result.compare("SUCCESS") == 0){
      _return = "Registration for user " + username + " was successful. Please login";
    }else{
    _return = "Failed to register user " + username;
    }
  }

  void UserServiceHandler::GetUserID(std::string &_return, const std::string &username)
  {

    std::cout << "GetUserID UserService method" << std::endl;

    //connect with mongoDB
    //find username
    // -if WRONG/not found, throw SE
    // -if RIGHT, grab userID and return

    _return = "422445416448000";
  }

  void UserServiceHandler::Logout(std::string &_return, const std::string &username)
  {
    //set user status to OFFLINE
    std::cout << "Logout UserService method" << std::endl;

    _return = "Logout for user " + username + " was successful";
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

} //namespace microchat

#endif