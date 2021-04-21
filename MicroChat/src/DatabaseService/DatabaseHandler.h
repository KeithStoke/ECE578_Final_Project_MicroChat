#ifndef MICROCHAT_DATABASEHANDLER_H
#define MICROCHAT_DATABASEHANDLER_H

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

#include "../../gen-cpp/DatabaseService.h"
#include "../ClientPool.h"
#include "../ThriftClient.h"
#include "../logger.h"
#include "../utils_mongodb.h"

#define MONGODB_TIMEOUT_MS 5000

namespace microchat
{

  class DatabaseServiceHandler : public DatabaseServiceIf
  {
  public:
    DatabaseServiceHandler(mongoc_client_pool_t *);
    ~DatabaseServiceHandler() override = default;

    void ping(std::string &_return, const std::string &text) override;
   
    void CreateUser(std::string &_return, const std::string &username, const std::string &name, const std::string &password, const int64_t userID) override;
    void CheckForUser(std::string &_return, const std::string &username) override;
    void Login(std::string &_return, const std::string &username, const std::string &password) override;
    void Logout(std::string &_return, const std::string &username) override;

    void UserStatus(std::string& _return, const std::string& username, const int64_t status) override;
    void OnlineUsers(std::string& _return) override;
  private:
    mongoc_client_pool_t *_mongodb_client_pool;
  };

  DatabaseServiceHandler::DatabaseServiceHandler(mongoc_client_pool_t *mongo_pool)
  {
    printf("Before Mongo Pool\n");
    _mongodb_client_pool = mongo_pool;
    printf("After Mongo Pool\n");
  };

  void DatabaseServiceHandler::OnlineUsers(std::string& _return)
  {
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
        mongodb_client, "user", "user");
    if (!collection)
    {
      ServiceException se;
      se.errorCode = ErrorCode::SE_MONGODB_ERROR;
      se.message = "Failed to create collection user from DB user";
      throw se;
    }

    bson_t *query = bson_new();
    BSON_APPEND_INT64(query, "user_status", UserStatus::type::ONLINE);
  
    mongoc_cursor_t *cursor = mongoc_collection_find_with_opts(
        collection, query, nullptr, nullptr);
    const bson_t *doc;
    std::string username_stored;
    //Print off all users
    char* str;
    bson_iter_t iter_username;
   
    while (mongoc_cursor_next (cursor, &doc)) {
      //grab password and userid
       std::cout<< "Users found were:"<<std::endl;
      str = bson_as_canonical_extended_json (doc, NULL);
      printf ("%s\n", str);
      bson_free (str);
      if (bson_iter_init_find(&iter_username, doc, "username"))     
      {
        username_stored = bson_iter_value(&iter_username)->value.v_utf8.str;
        std::cout<< "User Found in Databse is: "<< username_stored<< std::endl;
      }
      else{
        std::cout<<"Users not found in database"<<std::endl;
      }
       bson_iter_t iter_user_id;
       int64_t user_id_stored;
      //grab password and userid
      if (bson_iter_init_find(&iter_user_id, doc, "user_id"))
      {
        user_id_stored = bson_iter_value(&iter_user_id)->value.v_int64;
        std::cout<< "User ID Found in Databse is: "<< user_id_stored<< std::endl;
      }
   }
   std::cout<< "End of Query"<< std::endl;
    bson_error_t error;
    
    if (mongoc_cursor_error(cursor, &error))
    {
      LOG(error) << error.message;
      bson_destroy(query);
      mongoc_cursor_destroy(cursor);
      mongoc_collection_destroy(collection);
      mongoc_client_pool_push(_mongodb_client_pool, mongodb_client);
      ServiceException se;
      se.errorCode = ErrorCode::SE_MONGODB_ERROR;
      se.message = error.message;
      throw se;
    }
      bson_destroy(query);
      mongoc_cursor_destroy(cursor);
      mongoc_collection_destroy(collection);
      mongoc_client_pool_push(_mongodb_client_pool, mongodb_client);

    _return = "Users are online ";
    
  }

  void DatabaseServiceHandler::ping(std::string &_return, const std::string &text)
  {
    std::cout << "Ping from DatabaseServiceHandler... " << std::endl;
    _return = "Pong from DatabaseServiceHandler!";
  }

  void DatabaseServiceHandler::CheckForUser(std::string &_return, const std::string &username)
  {
      _return = "Users are online ";
    
  }

   void DatabaseServiceHandler::Login(std::string &_return, const std::string &username, const std::string &password)
  {

    std::string password_stored;
    int64_t user_id_stored = -1;

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
        mongodb_client, "user", "user");
    if (!collection)
    {
      ServiceException se;
      se.errorCode = ErrorCode::SE_MONGODB_ERROR;
      se.message = "Failed to create collection user from DB user";
      throw se;
    }

    bson_t *query = bson_new();
    BSON_APPEND_UTF8(query, "username", username.c_str());

    mongoc_cursor_t *cursor = mongoc_collection_find_with_opts(
        collection, query, nullptr, nullptr);
    const bson_t *doc;
    bool found = mongoc_cursor_next(cursor, &doc);

    bson_error_t error;
    if (mongoc_cursor_error(cursor, &error))
    {
      LOG(error) << error.message;
      bson_destroy(query);
      mongoc_cursor_destroy(cursor);
      mongoc_collection_destroy(collection);
      mongoc_client_pool_push(_mongodb_client_pool, mongodb_client);
      ServiceException se;
      se.errorCode = ErrorCode::SE_MONGODB_ERROR;
      se.message = error.message;
      throw se;
    }

    if (!found) //username does not exists in database
    {
      LOG(warning) << "User: " << username << " doesn't exist in MongoDB";
      std::cout << "User: " << username << " doesn't exist in MongoDB";
      bson_destroy(query);
      mongoc_cursor_destroy(cursor);
      mongoc_collection_destroy(collection);
      mongoc_client_pool_push(_mongodb_client_pool, mongodb_client);
      ServiceException se;
      se.errorCode = ErrorCode::SE_UNAUTHORIZED;
      se.message = "User: " + username + " is not registered";
      throw se;
    }
    else //we found username!
    {
      LOG(debug) << "Username: " << username << " found in MongoDB";
      std::cout << "Username: " << username << " found in MongoDB" << std::endl;
      bson_iter_t iter_password;
      bson_iter_t iter_user_id;
      //grab password and userid
      if (bson_iter_init_find(&iter_password, doc, "password") &&
          bson_iter_init_find(&iter_user_id, doc, "user_id"))
      {
        password_stored = bson_iter_value(&iter_password)->value.v_utf8.str;
        user_id_stored = bson_iter_value(&iter_user_id)->value.v_int64;
      }
      else //some reason password and/or userid were not stored
      {
        LOG(error) << "user: " << username << " entry is NOT complete";
        std::cout << "user: " << username << " entry is NOT complete";
        bson_destroy(query);
        mongoc_cursor_destroy(cursor);
        mongoc_collection_destroy(collection);
        mongoc_client_pool_push(_mongodb_client_pool, mongodb_client);
        ServiceException se;
        se.errorCode = ErrorCode::SE_THRIFT_HANDLER_ERROR;
        se.message = "user: " + username + " entry is NOT complete";
        throw se;
      }

      bson_t *update_query = bson_new();
      BSON_APPEND_UTF8(update_query, "username", username.c_str());
      bson_t *update = bson_new();
      bson_error_t update_error;
      BSON_APPEND_INT64(update, "user_status", UserStatus::type::ONLINE); //ONLINE = 0
      update = BCON_NEW("$set", "{",
                      "user_status", BCON_INT64(UserStatus::type::ONLINE), BCON_BOOL(true),
                      "}");
      if (!mongoc_collection_update(collection, MONGOC_UPDATE_NONE, update_query, update, NULL, &error))
      {
        std::cout << "Failed to update user status of " << username
                  << " in MongoDB: " << error.message;
        ServiceException se;
        se.errorCode = ErrorCode::SE_THRIFT_HANDLER_ERROR;
        se.message = "Failed to update user status of " + username + " in MongoDB: " + update_error.message;
        bson_destroy(update_query);
        bson_destroy(update);
        mongoc_collection_destroy(collection);
        mongoc_client_pool_push(_mongodb_client_pool, mongodb_client);
        throw se;
      }
      bson_destroy(query);
      mongoc_cursor_destroy(cursor);
      bson_destroy(update_query);
      bson_destroy(update);
      mongoc_collection_destroy(collection);
      mongoc_client_pool_push(_mongodb_client_pool, mongodb_client);

      if (!password_stored.empty() && (password.compare(password_stored) == 0))
      {
        //if passwords match, return SUCCESS
        std::cout << "Password and username were a match" << std::endl;
        _return = std::to_string(user_id_stored);
      }
      else
      {
        //else, incorrect username/password combo
        ServiceException se;
        se.errorCode = ErrorCode::SE_UNAUTHORIZED;
        se.message = "Incorrect username or password";
        throw se;
      }
    }
    OnlineUsers(_return);
  }
 
 void DatabaseServiceHandler::Logout(std::string &_return, const std::string &username)
  {
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
        mongodb_client, "user", "user");
    if (!collection)
    {
      ServiceException se;
      se.errorCode = ErrorCode::SE_MONGODB_ERROR;
      se.message = "Failed to create collection user from DB user";
      throw se;
    }

    bson_error_t error;
    bson_t *query = bson_new();
    BSON_APPEND_UTF8(query, "username", username.c_str());

    bson_t *update = bson_new();
    BSON_APPEND_INT64(update, "user_status", UserStatus::type::OFFLINE); //OFFLINE = 1
    update = BCON_NEW("$set", "{",
                      "user_status", BCON_INT64(UserStatus::type::OFFLINE), BCON_BOOL(true),
                      "}");
    if (!mongoc_collection_update(collection, MONGOC_UPDATE_NONE, query, update, NULL, &error))
    {
      std::cout << "Failed to logout " << username
                << " off MongoDB: " << error.message;
      ServiceException se;
      se.errorCode = ErrorCode::SE_THRIFT_HANDLER_ERROR;
      se.message = "Failed to logout " + username + " of MongoDB: " + error.message;
      bson_destroy(query);
      bson_destroy(update);
      mongoc_collection_destroy(collection);
      mongoc_client_pool_push(_mongodb_client_pool, mongodb_client);
      throw se;
    }

    _return = "Successful logout of user " + username;
  }
  void DatabaseServiceHandler::UserStatus(std::string &_return, const std::string &username,  const int64_t status)
  {
    std::cout << "Setting User Status in Database" <<std::endl;
  }

  void DatabaseServiceHandler::CreateUser(std::string &_return, const std::string &username, const std::string &name, const std::string &password, const int64_t userID)
  {

    std::cout << "CreateUser in Database Service Handler..." << std::endl;

    // Store user info into mongodb
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
        mongodb_client, "user", "user");

    // Check if the username has existed in the database
    bson_t *query = bson_new();
    BSON_APPEND_UTF8(query, "username", username.c_str());
    mongoc_cursor_t *cursor = mongoc_collection_find_with_opts(
        collection, query, nullptr, nullptr);
    const bson_t *doc;
    bson_error_t error;
    bool found = mongoc_cursor_next(cursor, &doc);
    if (mongoc_cursor_error(cursor, &error))
    {
      std::cout << error.message;
      bson_destroy(query);
      mongoc_cursor_destroy(cursor);
      mongoc_collection_destroy(collection);
      mongoc_client_pool_push(_mongodb_client_pool, mongodb_client);
      ServiceException se;
      se.errorCode = ErrorCode::SE_MONGODB_ERROR;
      se.message = error.message;
      throw se;
    }
    else if (found)
    {
      LOG(warning) << "User " << username << " already existed.";
      ServiceException se;
      se.errorCode = ErrorCode::SE_THRIFT_HANDLER_ERROR;
      se.message = "User " + username + " already existed";
      bson_destroy(query);
      mongoc_cursor_destroy(cursor);
      mongoc_collection_destroy(collection);
      mongoc_client_pool_push(_mongodb_client_pool, mongodb_client);
      throw se;
    }
    else
    {
      bson_t *new_doc = bson_new();
      int64_t user_id = userID;
      BSON_APPEND_INT64(new_doc, "user_id", user_id);
      BSON_APPEND_UTF8(new_doc, "name", name.c_str());
      BSON_APPEND_UTF8(new_doc, "username", username.c_str());
      BSON_APPEND_UTF8(new_doc, "password", password.c_str());

      if (!mongoc_collection_insert_one(
              collection, new_doc, nullptr, nullptr, &error))
      {
        std::cout << "Failed to insert user " << username
                  << " to MongoDB: " << error.message;
        ServiceException se;
        se.errorCode = ErrorCode::SE_THRIFT_HANDLER_ERROR;
        se.message = "Failed to insert user " + username + " to MongoDB: " + error.message;
        bson_destroy(query);
        mongoc_cursor_destroy(cursor);
        mongoc_collection_destroy(collection);
        mongoc_client_pool_push(_mongodb_client_pool, mongodb_client);
        throw se;
      }
      else
      {
               std::cout << "User: " <<  username << " registered" << std::endl;
      }

      bson_destroy(new_doc);
    }
    bson_destroy(query);
    mongoc_cursor_destroy(cursor);
    mongoc_collection_destroy(collection);
    mongoc_client_pool_push(_mongodb_client_pool, mongodb_client);

    _return = "SUCCESS";
  }

} //namespace microchat

#endif //MICROCHAT_DATABASEHANDLER_H