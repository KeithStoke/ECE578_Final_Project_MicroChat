#ifndef MICROCHAT_FRIENDRECOMMENDATIONHANDLER_H
#define MICROCHAT_FRIENDRECOMMENDATIONHANDLER_H

#include <iostream>
#include <string>
#include <regex>
#include <future>
#include <vector>

#include "../../gen-cpp/FriendRecommendationService.h"
#include "../../gen-cpp/DatabaseService.h"

#include "../ClientPool.h"
#include "../ThriftClient.h"
#include "../logger.h"

namespace microchat{

    class FriendRecommendationServiceHandler : public FriendRecommendationServiceIf {
 public:
  FriendRecommendationServiceHandler(
      std::mutex *,
        const std::string &,
        ClientPool<ThriftClient<DatabaseServiceClient>> *);
  ~FriendRecommendationServiceHandler() override=default;

  void ping(std::string &_return, const std::string &text) override;
  void GetFriendRecommendations(std::vector<std::string> & _return, const std::string& username) override;
  void onLogin(std::string & _return, const std::string& username) override;
   private:
    std::string _machine_id;
    std::mutex *_thread_lock;
    ClientPool<ThriftClient<DatabaseServiceClient>> *_database_client_pool;
};

FriendRecommendationServiceHandler::FriendRecommendationServiceHandler(
     std::mutex *thread_lock,
      const std::string &machine_id,
      ClientPool<ThriftClient<DatabaseServiceClient>> *database_client_pool)
) 
{
    _thread_lock = thread_lock;
    _machine_id = machine_id;
    _database_client_pool = database_client_pool;
}

void FriendRecommendationServiceHandler::ping(std::string &_return, const std::string &text){
    std::cout << "Ping says " << text << std::endl;
    _return = "Pong from FriendRecommendationService";
}

void FriendRecommendationServiceHandler::GetFriendRecommendations(std::vector<std::string> & _return, const std::string& username){
    printf("get friend recommendations RPC");
}

void FriendRecommendationServiceHandler::onLogin(std::string & _return, const std::string& username)
{
    std::cout << "On Login from Friend recommendation" <<std::endl;
    
    auto database_client_wrapper = _database_client_pool->Pop();
    if (!database_client_wrapper)
    {
      ServiceException se;
      se.errorCode = ErrorCode::SE_THRIFT_CONN_ERROR;
      se.message = "Failed to connect to database-service";
      throw se;
    }
    auto database_client = database_client_wrapper->GetClient();
}

} //namespace microchat

#endif //MICROCHAT_FRIENDRECOMMENDATIONHANDLER_H