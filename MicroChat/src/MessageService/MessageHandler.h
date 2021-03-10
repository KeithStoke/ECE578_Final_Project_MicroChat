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
        ~MessageServiceHandler() override = default;

        void ping() override;
    };
    // constructor
    MessageServiceHandler::MessageServiceHandler() {}

    void ping()
    {
        printf("pong!\n");
    }

}

#endif //MICROCHAT_MESSAGEHANDLER_H