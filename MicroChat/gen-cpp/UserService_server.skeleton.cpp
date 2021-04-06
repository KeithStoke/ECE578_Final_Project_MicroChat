// This autogenerated skeleton file illustrates how to build a server.
// You should copy it to another filename to avoid overwriting it.

#include "UserService.h"
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

using namespace  ::microchat;

class UserServiceHandler : virtual public UserServiceIf {
 public:
  UserServiceHandler() {
    // Your initialization goes here
  }

  void Ping(std::string& _return, const int32_t id) {
    // Your implementation goes here
    printf("Ping\n");
  }

  void Login(std::string& _return, const std::string& username, const std::string& password) {
    // Your implementation goes here
    printf("Login\n");
  }

  void CreateUser(const std::string& username, const std::string& name, const std::string& password) {
    // Your implementation goes here
    printf("CreateUser\n");
  }

  int64_t GetUserID(const std::string& username) {
    // Your implementation goes here
    printf("GetUserID\n");
  }

};

int main(int argc, char **argv) {
  int port = 9090;
  ::std::shared_ptr<UserServiceHandler> handler(new UserServiceHandler());
  ::std::shared_ptr<TProcessor> processor(new UserServiceProcessor(handler));
  ::std::shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
  ::std::shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
  ::std::shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

  TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
  server.serve();
  return 0;
}

