#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TThreadedServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include <signal.h>

#include "../utils.h"
#include "UserHandler.h"

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
  int my_port = config_json["user-service"]["port"];

  // get database service port
  int database_service_port = config_json["database-service"]["port"];
  std::string database_service_addr = config_json["database-service"]["addr"];

  std::string machine_id;
  if (GetMachineId(&machine_id) != 0)
  {
    exit(EXIT_FAILURE);
  }

  std::mutex thread_lock;

  ClientPool<ThriftClient<DatabaseServiceClient>> database_client_pool(
      "database-service", database_service_addr, database_service_port, 0, 128, 1000);

  //Get friend service port
  int friend_service_port = config_json["friend-recommendation-service"]["port"];
  std::string friend_service_addr = config_json["friend-recommendation-service"]["addr"];

  std::string machine_id;
  if (GetMachineId(&machine_id) != 0)
  {
    exit(EXIT_FAILURE);
  }

  std::mutex thread_lock;

  ClientPool<ThriftClient<FriendRecommendationServiceClient>> friend_client_pool(
      "friend-recommendation-service", friend_service_addr, friend_service_port, 0, 128, 1000);

  TThreadedServer server(
      std::make_shared<UserServiceProcessor>(
          std::make_shared<UserServiceHandler>(
            &thread_lock,
            machine_id,
            &database_client_pool,
            &friend_client_pool
          )),
      std::make_shared<TServerSocket>("0.0.0.0", my_port),
      std::make_shared<TFramedTransportFactory>(),
      std::make_shared<TBinaryProtocolFactory>()
      );

  // 5: start the server
  std::cout << "Starting the user server ..." << std::endl;
  server.serve();
  return 0;
}