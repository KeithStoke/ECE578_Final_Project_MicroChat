#ifndef MICROCHAT_EMOJIPREDICTIONHANDLER_H
#define MICROCHAT_EMOJIPREDICTIONHANDLER_H

#include <iostream>
#include <string>
#include <regex>
#include <future>

#include "../../gen-cpp/EmojiPredictionService.h"

#include "../ClientPool.h"
#include "../ThriftClient.h"
#include "../logger.h"

namespace microchat
{

  class EmojiPredictionServiceHandler : public EmojiPredictionServiceIf
  {
  public:
    EmojiPredictionServiceHandler();
    ~EmojiPredictionServiceHandler() override = default;

    void ping(std::string &_return, const std::string &text) override;
    void GetEmoji(Emoji &_return, const std::string &text) override;
  };

  EmojiPredictionServiceHandler::EmojiPredictionServiceHandler() {};

  void EmojiPredictionServiceHandler::ping(std::string &_return, const std::string &text)
  {
    // Your implementation goes here
    std::cout << "Ping says " << text << std::endl;
    _return = "Pong from EmojiPredictionService";
  }

  void EmojiPredictionServiceHandler::GetEmoji(Emoji &_return, const std::string &text)
  {
    // Your implementation goes here
    printf("GetEmoji\n");
  }

} //namespace microchat

#endif //MICROCHAT_EMOJIPREDICTIONHANDLER_H