#ifndef MICROCHAT_FRIENDRECOMMENDATIONHANDLER_H
#define MICROCHAT_FRIENDRECOMMENDATIONHANDLER_H

#include <iostream>
#include <string>
#include <regex>
#include <future>
#include <mongoc.h>
#include <bson/bson.h>
#include <iomanip>
#include <arpa/inet.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <nlohmann/json.hpp>
#include <jwt/jwt.hpp>

#include "../../gen-cpp/FriendRecommendationService.h"

#include "../ClientPool.h"
#include "../ThriftClient.h"
#include "../logger.h"
#include "../utils_mongodb.h"

#define MONGODB_TIMEOUT_MS 5000

namespace microchat
{

    class FriendRecommendationServiceHandler : public FriendRecommendationServiceIf
    {
    public:
        FriendRecommendationServiceHandler(mongoc_client_pool_t *);
        ~FriendRecommendationServiceHandler() override = default;

        void ping(std::string &_return, const std::string &text) override;
        void GetFriendRecommendations(std::string &_return, const std::string &username) override;

    private:
        mongoc_client_pool_t *_mongodb_client_pool;
    };

    FriendRecommendationServiceHandler::FriendRecommendationServiceHandler(mongoc_client_pool_t *mongo_pool)
    {

        std::cout << "Before Mongo Pool" << std::endl;
        _mongodb_client_pool = mongo_pool;
        std::cout << "After Mongo Pool" << std::endl;
    };

    void FriendRecommendationServiceHandler::ping(std::string &_return, const std::string &text)
    {
        std::cout << "Ping says " << text << std::endl;
        _return = "Pong from FriendRecommendationService";
    }

    void FriendRecommendationServiceHandler::GetFriendRecommendations(std::string &_return, const std::string &username)
    {

        std::cout << "In friend recommendation service..." << std::endl;

        bson_error_t error;
        const bson_t *doc;
        char *str;

        std::vector<std::string> online_users;

        mongoc_client_t *mongodb_client = mongoc_client_pool_pop(
            _mongodb_client_pool);
        if (!mongodb_client)
        {
            ServiceException se;
            se.errorCode = ErrorCode::SE_MONGODB_ERROR;
            se.message = "Failed to pop a client from MongoDB pool";
            throw se;
        }

        auto collection = mongoc_client_get_collection(
            mongodb_client, "user", "user");
        if (!collection)
        {
            ServiceException se;
            se.errorCode = ErrorCode::SE_MONGODB_ERROR;
            se.message = "Failed to create collection user from DB user";
            throw se;
        }

        //find all users whose status is ONLINE
        bson_t *query = bson_new();
        BSON_APPEND_INT64(query, "user_status", 0);

        mongoc_cursor_t *cursor = mongoc_collection_find_with_opts(
            collection, query, nullptr, nullptr);

        if (mongoc_cursor_error(cursor, &error))
        {
            LOG(error) << error.message;
            bson_destroy(query);
            mongoc_cursor_destroy(cursor);
            mongoc_collection_destroy(collection);
            mongoc_client_pool_push(_mongodb_client_pool, mongodb_client);
            ServiceException se;
            se.errorCode = ErrorCode::SE_MONGODB_ERROR;
            se.message = error.message;
            throw se;
        }
        else
        {
            //no errors

            bson_iter_t iter_username;

            while (mongoc_cursor_next(cursor, &doc))
            {

                //print off what we found for debugging purposes
                str = bson_as_json(doc, NULL);
                std::cout << str << std::endl;
                bson_free(str);

                bson_iter_init_find(&iter_username, doc, "username");
                std::string username_stored = bson_iter_value(&iter_username)->value.v_utf8.str;

                if (username.compare(username_stored) != 0)
                {
                    //if not current user, we add username to list of online users
                    online_users.push_back(username_stored);
                }
            }

            bson_destroy(query);
            mongoc_cursor_destroy(cursor);
            mongoc_collection_destroy(collection);
            mongoc_client_pool_push(_mongodb_client_pool, mongodb_client);

            std::string result = "Online Users\n";
            for (std::string user : online_users)
            {
                result.append(user);
                result.append("\n");
               // std::cout << "appending user " << user << " to result string..." << std::endl;
            }

            //return a list of online users
            _return = result;
        }
    }
} //namespace microchat

#endif //MICROCHAT_FRIENDRECOMMENDATIONHANDLER_H