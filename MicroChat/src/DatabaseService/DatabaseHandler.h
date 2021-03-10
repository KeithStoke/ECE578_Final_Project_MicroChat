#ifndef MICROCHAT_DATABASEHANDLER_H
#define MICROCHAT_DATABASEHANDLER_H

#include <iostream>
#include <string>
#include <regex>
#include <future>

#include "../../gen-cpp/DatabaseService.h"

#include "../ClientPool.h"
#include "../ThriftClient.h"
#include "../logger.h"

namespace microchat
{

    class DatabaseServiceHandler : virtual public DatabaseServiceIf
    {
    public:
        DatabaseServiceHandler();
        ~DatabaseServiceHandler() override=default;

        void ping() override;
    };

    DatabaseServiceHandler::DatabaseServiceHandler() {};

    void ping()
    {
        // Your implementation goes here
        printf("ping\n");
    }

} //namespace microchat

#endif //MICROCHAT_DATABASEHANDLER_H