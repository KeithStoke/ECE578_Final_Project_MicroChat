#ifndef MICROCHAT_USERHANDLER_H
#define MICROCHAT_USERHANDLER_H

#include <iostream>
#include <string>
#include <regex>
#include <future>

#include "../../gen-cpp/UserService.h"

#include "../ClientPool.h"
#include "../ThriftClient.h"
#include "../logger.h"

namespace microchat
{

  class UserServiceHandler : public UserServiceIf
  {
  public:
    UserServiceHandler();
    ~UserServiceHandler()override=default;

    void ping(std::string &_return, const std::string &text) override;
    void Login(User &_return, const std::string &usernmae, const std::string &password) override;
    void CreateUser(User &_return, const std::string &username, const std::string &name, const std::string &password) override;
  };

  // constructor
  UserServiceHandler::UserServiceHandler() {}

  void UserServiceHandler::ping(std::string &_return, const std::string &text)
  {
    std::cout << "Ping says " << text << std::endl;
    std::string pong = "Pong from UserService";
    _return = pong;
  }

  void UserServiceHandler::Login(User &_return, const std::string &usernmae, const std::string &password)
  {
    // Your implementation goes here
    printf("Login\n");
  }

  void UserServiceHandler::CreateUser(User &_return, const std::string &username, const std::string &name, const std::string &password)
  {
    // Your implementation goes here
    printf("CreateUser\n");
  }

} //namespace microchat

#endif