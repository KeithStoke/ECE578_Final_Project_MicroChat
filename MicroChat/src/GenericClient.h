#ifndef MICROCHAT_GENERICCLIENT_H
#define MICROCHAT_GENERICCLIENT_H

#include <string>

namespace microchat {

class GenericClient{
 public:
  virtual ~GenericClient() = default;
  virtual void Connect() = 0;
  virtual void KeepAlive() = 0;
  virtual void KeepAlive(int) = 0;
  virtual void Disconnect() = 0;
  virtual bool IsConnected() = 0;

 protected:
  std::string _addr;
  int _port;
};

} // namespace microchat

#endif //MICROCHAT_GENERICCLIENT_H
