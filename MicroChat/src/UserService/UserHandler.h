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
   // UserServiceHandler(ClientPool<ThriftClient<DatabaseServiceClient>> *);
    UserServiceHandler();
    ~UserServiceHandler() override=default;

    void Ping(std::string &_return, const int32_t id) override;
    void Login(std::string& _return, const std::string& username, const std::string& password) override;
    void CreateUser(User &_return, const std::string &username, const std::string &name, const std::string &password) override;

 //  ClientPool<ThriftClient<DatabaseServiceClient>> *_database_client_pool;
  };

  // constructor
 /** UserServiceHandler::UserServiceHandler(ClientPool<ThriftClient<DatabaseServiceClient>> *database_client_pool)
  {
    _database_client_pool = database_client_pool;
  } **/

   UserServiceHandler::UserServiceHandler(){};

  void UserServiceHandler::Ping(std::string &_return, const int32_t id)
  {
    std::cout << "ID received was " << id << std::endl;
    std::string pong = "Pong from UserService";
    _return = pong;
  }

 void UserServiceHandler::Login(std::string& _return, const std::string& username, const std::string& password)
  {
    std::cout << "In user service login method" << std::endl;
    std::cout << "username was " << username << " and password was " << password << std::endl;
    std::cout << "Login UserService Method" << std::endl;
/**    auto database_client_wrapper = _database_client_pool->Pop();
    if (!database_client_wrapper)
    {
      ServiceException se;
      se.errorCode = ErrorCode::SE_THRIFT_CONN_ERROR;
      se.message = "Failed to connect to database-service";
      throw se;
    }
    auto database_client = database_client_wrapper->GetClient();
    std::string query_result = "DEFAULT";
    try
    {
      database_client->ReadFromDatabase(query_result, "test query");
    }
    catch (...)
    {
      _database_client_pool->Push(database_client_wrapper);
      LOG(error) << "Failed to send call ReadFromDatabase to database-service";
      throw;
    }

    _database_client_pool->Push(database_client_wrapper);
    std::cout << "Result from ReadFromDatabase query " << query_result << std::endl; **/

    std::string result = "Pong from Login";
        _return = result;
  }

  void UserServiceHandler::CreateUser(User &_return, const std::string &username, const std::string &name, const std::string &password)
  {
    // Your implementation goes here
    printf("CreateUser\n");
  }

} //namespace microchat

#endif