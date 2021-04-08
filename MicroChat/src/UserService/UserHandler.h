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
    UserServiceHandler();
    ~UserServiceHandler() override = default;

    void ping(std::string &_return, const int32_t id) override;
    void Login(std::string &_return, const std::string &username, const std::string &password) override;
    void CreateUser(std::string &_return, const std::string &username, const std::string &name, const std::string &password) override;
    void GetUserID(std::string& _return, const std::string& username) override;

  private:
    std::string _machine_id;
    std::string _secret;
    std::mutex *_thread_lock;
  };

  UserServiceHandler::UserServiceHandler(){};

  void UserServiceHandler::ping(std::string &_return, const int32_t id)
  {
    std::cout << "ID received was " << id << std::endl;
    std::string pong = "Pong from UserService";
    _return = pong;
  }

  void UserServiceHandler::Login(std::string &_return, const std::string &username, const std::string &password)
  {
    std::cout << "Login UserService Method" << std::endl;

    //1. connect with mongoDB
    //2. check username/password combo
    // -if WRONG COMBO, throw SE
    // -if NOT FOUND, throw SE
    // -if RIGHT, set userstatus ONLINE and return userID

    _return = "this will use USERID";
  }

  void UserServiceHandler::CreateUser(std::string &_return, const std::string &username, const std::string &name, const std::string &password)
  {
    std::cout << "CreateUser UserService Method" << std::endl;

    //create userID
    // _thread_lock->lock();
    int64_t timestamp = duration_cast<milliseconds>(
                            system_clock::now().time_since_epoch())
                            .count() -
                        CUSTOM_EPOCH;
    int idx = GetCounter(timestamp);
    // _thread_lock->unlock();

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

    //check if usename already exists in mongoDB

    //if username is unique, store in mongoDB

    //return and "redirect" user to login
    _return = "User successfully created. Please login.";
  }

  void UserServiceHandler::GetUserID(std::string& _return, const std::string& username)
  {

    std::cout << "GetUserID UserService method" << std::endl;

    //connect with mongoDB
    //find username
    // -if WRONG/not found, throw SE
    // -if RIGHT, grab userID and return
    
    _return = "422445416448000";
  }

} //namespace microchat

#endif