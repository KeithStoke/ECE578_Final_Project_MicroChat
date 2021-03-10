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
  FriendRecommendationServiceHandler() override;
  ~FriendRecommendationServiceHandler() override=default;

  void ping() override;
  void GetFriendRecommendations(std::vector<User> & _return, const User& user) override;

};

FriendRecommendationServiceHandler::FriendRecommendationServiceHandler();

void ping(){
    printf("PONG!\n");
}

void GetFriendRecommendations(std::vector<User> & _return, const User& user){
    printf("EVA TODO");
}

} //namespace microchat

#endif //MICROCHAT_FRIENDRECOMMENDATIONHANDLER_H