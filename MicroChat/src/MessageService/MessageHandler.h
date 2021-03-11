#ifndef MICROCHAT_MESSAGEHANDLER_H
#define MICROCHAT_MESSAGEHANDLER_H

#include <iostream>
#include <string>
#include <regex>
#include <future>

#include "../../gen-cpp/MessageService.h"

#include "../ClientPool.h"
#include "../ThriftClient.h"
#include "../logger.h"

namespace microchat
{

    class MessageServiceHandler : public MessageServiceIf
    {
    public:
        MessageServiceHandler();
        ~MessageServiceHandler() override=default;

        void ping(std::string &_return, const std::string &text) override;
    };
    // constructor
    MessageServiceHandler::MessageServiceHandler() {}

    void MessageServiceHandler::ping(std::string &_return, const std::string &text)
    {
        std::cout << "Ping says " << text << std::endl;
        _return = "Pong from MessageService";
    }

}

#endif //MICROCHAT_MESSAGEHANDLER_H