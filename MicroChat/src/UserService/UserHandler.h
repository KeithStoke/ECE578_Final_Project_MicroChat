#ifndef MICROCHAT_USERHANDLER_H
#define MICROCHAT_USERHANDLER_H

#include <iostream>
#include <string>
#include <regex>
#include <future>
#include <mongoc.h>
#include <bson/bson.h>
#include "../../gen-cpp/UserService.h"

#include "../ClientPool.h"
#include "../ThriftClient.h"
#include "../microchat_utils.h"
#include "../logger.h"

namespace microchat
{
  class UserServiceHandler : public UserServiceIf
  {
  public:
   // UserServiceHandler(ClientPool<ThriftClient<DatabaseServiceClient>> *);
    UserServiceHandler(mongoc_client_pool_t *);
    ~UserServiceHandler() override=default;

    void ping() override;
    void Login(User &_return, const std::string &usernmae, const std::string &password);
    void CreateUser(User &_return, const std::string &username, const std::string &name, const std::string &password);
    void CheckForUser(User &_return, std::string username);
  private:
    mongoc_client_pool_t *_mongodb_client_pool;
    
 //  ClientPool<ThriftClient<DatabaseServiceClient>> *_database_client_pool;
  };

  // constructor
  //UserServiceHandler::UserServiceHandler() {}

   UserServiceHandler::UserServiceHandler(mongoc_client_pool_t *mongo_pool)
   {
     printf("Before Mongo Pool\n");
      _mongodb_client_pool = mongo_pool;
      printf("After Mongo Pool\n");
    
    const std::string first_name = "Keith";
    const std::string last_name = "Stokely";
    const std::string username = "kstokely";
    const std::string password = "test";
  
  microchat::User mUser;
  CreateUser(mUser, username, first_name, password);
 printf("End of Constructor\n");
 printf("Getting ready to ping!\n");
 ping();
  }


  void UserServiceHandler::ping()
  {
      printf("pong!\n");
  
  } 



  }
  
  void UserServiceHandler::Login(User &_return, const std::string &usernmae, const std::string &password)
  {
    // Your implementation goes here
    printf("Login\n");
  }


} //namespace microchat

#endif