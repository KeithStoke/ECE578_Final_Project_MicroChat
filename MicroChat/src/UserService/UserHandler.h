#ifndef MICROCHAT_USERHANDLER_H
#define MICROCHAT_USERHANDLER_H

#include <iostream>
#include <string>
#include <regex>
#include <future>

#include "../../gen-cpp/UserService.h"
#include "../../gen-cpp/DatabaseService.h"

#include "../ClientPool.h"
#include "../ThriftClient.h"
#include "../logger.h"

namespace microchat
{

  class UserServiceHandler : public UserServiceIf
  {
  public:
    UserServiceHandler();
    ~UserServiceHandler() override = default;

    void Ping(std::string& _return, const int32_t id) override;
    void Login(std::string &_return, const std::string &username, const std::string &password) override;
    void CreateUser(const std::string &username, const std::string &name, const std::string &password) override;
    int64_t GetUserID(const std::string &username) override;
  };

  UserServiceHandler::UserServiceHandler(){};

  void UserServiceHandler::Ping(std::string& _return, const int32_t id)
  {
    std::cout << "ID received was " << id << std::endl;
    std::string pong = "Pong from UserService";
    _return = pong;
  }

  void UserServiceHandler::Login(std::string &_return, const std::string &username, const std::string &password)
  {
    std::cout << "In user service login method" << std::endl;
    std::cout << "username was " << username << " and password was " << password << std::endl;
    std::cout << "Login UserService Method" << std::endl;

    _return = "Session ID = SOMETHING";
  }

  void UserServiceHandler::CreateUser(const std::string &username, const std::string &name, const std::string &password)
  {
    // Your implementation goes here
    printf("CreateUser\n");
  }

  int64_t UserServiceHandler::GetUserID(const std::string& username) {
    return 64;
  }

} //namespace microchat

#endif