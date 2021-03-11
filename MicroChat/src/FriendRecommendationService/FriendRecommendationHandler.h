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

namespace microchat{

    class FriendRecommendationServiceHandler : public FriendRecommendationServiceIf {
 public:
  FriendRecommendationServiceHandler();
  ~FriendRecommendationServiceHandler() override=default;

  void ping(std::string &_return, const std::string &text) override;
  void GetFriendRecommendations(std::vector<User> & _return, const User& user) override;

};

FriendRecommendationServiceHandler::FriendRecommendationServiceHandler() {};

void FriendRecommendationServiceHandler::ping(std::string &_return, const std::string &text){
    std::cout << "Ping says " << text << std::endl;
    _return = "Pong from FriendRecommendationService";
}

void FriendRecommendationServiceHandler::GetFriendRecommendations(std::vector<User> & _return, const User& user){
    printf("get friend recommendations RPC");
}

} //namespace microchat

#endif //MICROCHAT_FRIENDRECOMMENDATIONHANDLER_H