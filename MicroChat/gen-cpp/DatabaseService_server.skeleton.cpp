// This autogenerated skeleton file illustrates how to build a server.
// You should copy it to another filename to avoid overwriting it.

#include "DatabaseService.h"
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

using namespace  ::microchat;

class DatabaseServiceHandler : virtual public DatabaseServiceIf {
 public:
  DatabaseServiceHandler() {
    // Your initialization goes here
  }

  void ping(std::string& _return, const std::string& text) {
    // Your implementation goes here
    printf("ping\n");
  }

  void WriteToDatabase(std::string& _return, const std::string& query) {
    // Your implementation goes here
    printf("WriteToDatabase\n");
  }

  void ReadFromDatabase(std::string& _return, const std::string& query) {
    // Your implementation goes here
    printf("ReadFromDatabase\n");
  }

};

int main(int argc, char **argv) {
  int port = 9090;
  ::std::shared_ptr<DatabaseServiceHandler> handler(new DatabaseServiceHandler());
  ::std::shared_ptr<TProcessor> processor(new DatabaseServiceProcessor(handler));
  ::std::shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
  ::std::shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
  ::std::shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

  TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
  server.serve();
  return 0;
}

