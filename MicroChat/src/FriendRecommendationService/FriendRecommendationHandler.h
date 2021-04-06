#ifndef MICROCHAT_FRIENDRECOMMENDATIONHANDLER_H
#define MICROCHAT_FRIENDRECOMMENDATIONHANDLER_H

#include <iostream>
#include <string>
#include <regex>
#include <future>

#include "../../gen-cpp/FriendRecommendationService.h"

#include "../ClientPool.h"
#include "../ThriftClient.h"
#include "../logger.h"
#include <mongoc.h>
#include <bson/bson.h>
#include "../microchat_utils.h"

namespace microchat{

    class FriendRecommendationServiceHandler : public FriendRecommendationServiceIf {
 public:
  FriendRecommendationServiceHandler(mongoc_client_pool_t *);
  ~FriendRecommendationServiceHandler() override=default;

void ping() override;
void GetFriendRecommendations(std::vector<User> & _return, const User& user) override;
void CreateUser(User &_return, const std::string &username, const std::string &name, const std::string &password);
void CheckForUser(User &_return, std::string username);
private:
mongoc_client_pool_t *_mongodb_client_pool;
};

FriendRecommendationServiceHandler::FriendRecommendationServiceHandler(mongoc_client_pool_t *mongo_pool) 
{
      printf("Before Mongo Pool\n");
      _mongodb_client_pool = mongo_pool;
      printf("After Mongo Pool\n");
}

void FriendRecommendationServiceHandler::ping(){
    printf("PONG!\n");
}

void FriendRecommendationServiceHandler::GetFriendRecommendations(std::vector<User> & _return, const User& user){
    printf("get friend recommendations RPC");
}


void FriendRecommendationServiceHandler::CheckForUser(User &_return, std::string username)
  {
    mongoc_client_t *mongodb_client = mongoc_client_pool_pop(
      _mongodb_client_pool);
  if (!mongodb_client) {
    ServiceException se;
    se.errorCode = ErrorCode::SE_MONGODB_ERROR;
    se.message = "Failed to pop a client from MongoDB pool";
    throw se;
  }
  auto collection = mongoc_client_get_collection(
      mongodb_client, "user", "user");
  //const std::string username = "kstokely";  
      // Check if the username has existed in the database
  bson_t *query = bson_new();
  BSON_APPEND_UTF8(query, "username", username.c_str());
  mongoc_cursor_t *cursor = mongoc_collection_find_with_opts(
      collection, query, nullptr, nullptr);
  const bson_t *doc;
  bson_error_t error;
  bool found = mongoc_cursor_next(cursor, &doc);
  if (mongoc_cursor_error (cursor, &error)) {
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
}

void FriendRecommendationServiceHandler::CreateUser(User &_return, const std::string &username, const std::string &name, const std::string &password)
{
    // Your implementation goes here
    printf("CreateUser\n");
     // Store user info into mongodb
     const int64_t req_id = 10;
  mongoc_client_t *mongodb_client = mongoc_client_pool_pop(
      _mongodb_client_pool);
  if (!mongodb_client) {
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
  if (mongoc_cursor_error (cursor, &error)) {
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
    int64_t user_id = req_id;
    BSON_APPEND_INT64(new_doc, "user_id", user_id);
    BSON_APPEND_UTF8(new_doc, "name", name.c_str());
    BSON_APPEND_UTF8(new_doc, "username", username.c_str());
   // std::string salt = GenRandomString(32);
    //BSON_APPEND_UTF8(new_doc, "salt", salt.c_str());
    //std::string password_hashed = picosha2::hash256_hex_string(password + salt);
    BSON_APPEND_UTF8(new_doc, "password", password.c_str());
    

    if (!mongoc_collection_insert_one(
        collection, new_doc, nullptr, nullptr, &error)) {
      std::cout << "Failed to insert user " << username
          << " to MongoDB: " << error.message;
      ServiceException se;
      se.errorCode = ErrorCode::SE_THRIFT_HANDLER_ERROR;
      se.message = "Failed to insert user " + username + " to MongoDB: "
          + error.message;
      bson_destroy(query);
      mongoc_cursor_destroy(cursor);
      mongoc_collection_destroy(collection);
      mongoc_client_pool_push(_mongodb_client_pool, mongodb_client);
      throw se;
    } else {
      std::cout << "User: " << username << " registered";
    }

    bson_destroy(new_doc);
  }
  bson_destroy(query);
  mongoc_cursor_destroy(cursor);
  mongoc_collection_destroy(collection);
  mongoc_client_pool_push(_mongodb_client_pool, mongodb_client);
}
} //namespace microchat

#endif //MICROCHAT_FRIENDRECOMMENDATIONHANDLER_H