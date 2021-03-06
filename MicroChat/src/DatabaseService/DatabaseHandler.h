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

    class DatabaseServiceHandler : public DatabaseServiceIf
    {
    public:
        DatabaseServiceHandler();
        ~DatabaseServiceHandler() override=default;

        void ping() override;
        void WriteToDatabase(std::string& _return, const std::string& query) override;
        void ReadFromDatabase(std::string& _return, const std::string& query) override;
    };

    DatabaseServiceHandler::DatabaseServiceHandler() {};
    

    void DatabaseServiceHandler::ping()
    {
        // Your implementation goes here
        printf("ping\n");
    }

    void DatabaseServiceHandler::WriteToDatabase(std::string& _return, const std::string& query) {
    // Your implementation goes here
    printf("WriteToDatabase\n");
  }

  void DatabaseServiceHandler::ReadFromDatabase(std::string& _return, const std::string& query) {
    // Your implementation goes here
    printf("ReadFromDatabase\n");
  }

} //namespace microchat

#endif //MICROCHAT_DATABASEHANDLER_H