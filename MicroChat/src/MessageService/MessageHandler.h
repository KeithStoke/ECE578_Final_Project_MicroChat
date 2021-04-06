#ifndef MICROCHAT_MESSAGEHANDLER_H
#define MICROCHAT_MESSAGEHANDLER_H

#include <iostream>
#include <string>
#include <regex>
#include <future>
#include <vector>

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
        ~MessageServiceHandler() override = default;

        void ping(std::string &_return, const std::string &text) override;
        void ComposeMessage(const std::string &text, const std::vector<std::string> &users) override;
        void ReadMessage(std::string &_return, const int64_t messageID) override;
    };

        // constructor
        MessageServiceHandler::MessageServiceHandler() {};

        void MessageServiceHandler::ping(std::string &_return, const std::string &text)
        {
            std::cout << "Ping says " << text << std::endl;
            _return = "Pong from MessageService";
        }

        void MessageServiceHandler::ComposeMessage(const std::string &text, const std::vector<std::string> &users)
        {
            // Your implementation goes here
            printf("ComposeMessage\n");
        }

        void MessageServiceHandler::ReadMessage(std::string &_return, const int64_t messageID)
        {
            // Your implementation goes here
            printf("ReadMessage\n");
        }
    
}

#endif //MICROCHAT_MESSAGEHANDLER_H