#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TThreadedServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include <signal.h>

#include "../utils.h"
#include "FriendRecommendationHandler.h"

using json = nlohmann::json;
using apache::thrift::protocol::TBinaryProtocolFactory;
using apache::thrift::server::TThreadedServer;
using apache::thrift::transport::TFramedTransportFactory;
using apache::thrift::transport::TServerSocket;

using namespace microchat;

// signal handler code
void sigintHandler(int sig)
{
  exit(EXIT_SUCCESS);
}

// entry of this service
int main(int argc, char **argv)
{
  // 1: notify the singal handler if interrupted
  signal(SIGINT, sigintHandler);
  // 1.1: Initialize logging
  init_logger();

  // 2: read the config file for ports and addresses
  json config_json;
  if (load_config_file("config/service-config.json", &config_json) != 0)
  {
    exit(EXIT_FAILURE);
  }

  // 3: get my port
  int my_port = config_json["friend-recommendation-service"]["port"];

  mongoc_client_pool_t *mongodb_client_pool =
      init_mongodb_client_pool(config_json, "user", 128);
  mongoc_client_t *mongodb_client = mongoc_client_pool_pop(mongodb_client_pool);
  if (!mongodb_client)
  {
    std::cout << "Failed to pop user mongoc client";
    return EXIT_FAILURE;
  }
  bool r = false;
  while (!r)
  {
    r = CreateIndex(mongodb_client, "user", "user_id", true);
    if (!r)
    {
      std::cout << "Failed to create mongodb index, try again";
      sleep(1);
    }
  }
  mongoc_client_pool_push(mongodb_client_pool, mongodb_client);

  // 4: configure this server
  TThreadedServer server(
      std::make_shared<FriendRecommendationServiceProcessor>(
          std::make_shared<FriendRecommendationServiceHandler>(mongodb_client_pool)),
      std::make_shared<TServerSocket>("0.0.0.0", my_port),
      std::make_shared<TFramedTransportFactory>(),
      std::make_shared<TBinaryProtocolFactory>());

  // 5: start the server
  std::cout << "Starting the friend recommendation server ..." << std::endl;
  server.serve();
  return 0;
}