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
        void ComposeMessage(std::string &_return, const std::string &text, const std::vector<std::string> &users) override;
        void ReadMessage(std::string &_return, const int64_t messageID, const std::string &username) override;
        void GetMessages(std::vector<Message> &_return, const std::string &username) override;
        void GetUnreadMessages(std::vector<Message> &_return, const std::string &username);
        void GetReadMessages(std::vector<Message> &_return, const std::string &username);
    };

    // constructor
    MessageServiceHandler::MessageServiceHandler(){};

    void MessageServiceHandler::ping(std::string &_return, const std::string &text)
    {
        std::cout << "Ping says " << text << std::endl;
        _return = "Pong from MessageService";
    }

    void MessageServiceHandler::ComposeMessage(std::string &_return, const std::string &text, const std::vector<std::string> &users)
    {

        //create new Message object w/ list of recipients
        //create new SimpleMessage object w/ same messageID, username, READ/UNREAD status
        //store 1 Message and X SimpleMessage objects into mongoDB
    }

    void MessageServiceHandler::ReadMessage(std::string &_return, const int64_t messageID, const std::string &username)
    {
        
    }
    void MessageServiceHandler::GetMessages(std::vector<Message> &_return, const std::string &username)
    {
        //FIRST search users to see if username exists
        // if NOT, throw SE
        // else, search db for any messages that include 'username' in list of recipients
        //  grab messages and return to user so they can read them
    }

    void MessageServiceHandler::GetUnreadMessages(std::vector<Message> &_return, const std::string &username)
    {
        // Your implementation goes here
        printf("GetUnreadMessages\n");
    }

    void MessageServiceHandler::GetReadMessages(std::vector<Message> &_return, const std::string &username)
    {
        // Your implementation goes here
        printf("GetReadMessages\n");
    }

}

#endif //MICROCHAT_MESSAGEHANDLER_H