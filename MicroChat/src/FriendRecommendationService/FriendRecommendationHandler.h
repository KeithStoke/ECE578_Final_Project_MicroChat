#ifndef MICROCHAT_FRIENDRECOMMENDATIONHANDLER_H
#define MICROCHAT_FRIENDRECOMMENDATIONHANDLER_H

#include <iostream>
#include <string>
#include <regex>
#include <future>
#include <vector>
#include <iomanip>
#include <arpa/inet.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <nlohmann/json.hpp>
#include <jwt/jwt.hpp>
#include <random>
#include "../../gen-cpp/FriendRecommendationService.h"
#include "../../gen-cpp/DatabaseService.h"

#include "../ClientPool.h"
#include "../ThriftClient.h"
#include "../logger.h"

namespace microchat{

    class FriendRecommendationServiceHandler : public FriendRecommendationServiceIf {
 public:
  FriendRecommendationServiceHandler(ClientPool<ThriftClient<DatabaseServiceClient>> *);
  ~FriendRecommendationServiceHandler() override=default;

  void ping(std::string &_return, const std::string &text) override;
  void GetFriendRecommendations(std::vector<std::string> & _return, const std::string& username) override;
  void onLogin(std::string & _return, const std::string& username) override;
   private:

    ClientPool<ThriftClient<DatabaseServiceClient>> *_database_client_pool;
};
  /*
 * The following code which obtaines machine ID from machine's MAC address was
 * inspired from https://stackoverflow.com/a/16859693.
 */
 
FriendRecommendationServiceHandler::FriendRecommendationServiceHandler(
      ClientPool<ThriftClient<DatabaseServiceClient>> *database_client_pool) 
{
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