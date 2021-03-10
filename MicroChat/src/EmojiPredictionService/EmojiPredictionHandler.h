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

  class EmojiPredictionServiceHandler : virtual public EmojiPredictionServiceIf
  {
  public:
    EmojiPredictionServiceHandler();
    ~EmojiPredictionServiceHandler() override = default;

    void ping() override;
    void GetEmoji(Emoji &_return, const std::string &text) override;
  };

  void ping()
  {
    // Your implementation goes here
    printf("ping\n");
  }

  void GetEmoji(Emoji &_return, const std::string &text)
  {
    // Your implementation goes here
    printf("GetEmoji\n");
  }

} //namespace microchat

#endif //MICROCHAT_EMOJIPREDICTIONHANDLER_H