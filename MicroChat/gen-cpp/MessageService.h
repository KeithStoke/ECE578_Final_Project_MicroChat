/**
 * Autogenerated by Thrift Compiler (0.13.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef MessageService_H
#define MessageService_H

#include <thrift/TDispatchProcessor.h>
#include <thrift/async/TConcurrentClientSyncInfo.h>
#include <memory>
#include "microchat_types.h"

namespace microchat {

#ifdef _MSC_VER
  #pragma warning( push )
  #pragma warning (disable : 4250 ) //inheriting methods via dominance 
#endif

class MessageServiceIf {
 public:
  virtual ~MessageServiceIf() {}
  virtual void ping(std::string& _return, const std::string& text) = 0;
  virtual void ComposeMessage(const std::string& text, const std::vector<std::string> & users) = 0;
  virtual void ReadMessage(std::string& _return, const int64_t messageID) = 0;
  virtual void GetMessages(std::vector<Message> & _return, const int64_t userID) = 0;
};

class MessageServiceIfFactory {
 public:
  typedef MessageServiceIf Handler;

  virtual ~MessageServiceIfFactory() {}

  virtual MessageServiceIf* getHandler(const ::apache::thrift::TConnectionInfo& connInfo) = 0;
  virtual void releaseHandler(MessageServiceIf* /* handler */) = 0;
};

class MessageServiceIfSingletonFactory : virtual public MessageServiceIfFactory {
 public:
  MessageServiceIfSingletonFactory(const ::std::shared_ptr<MessageServiceIf>& iface) : iface_(iface) {}
  virtual ~MessageServiceIfSingletonFactory() {}

  virtual MessageServiceIf* getHandler(const ::apache::thrift::TConnectionInfo&) {
    return iface_.get();
  }
  virtual void releaseHandler(MessageServiceIf* /* handler */) {}

 protected:
  ::std::shared_ptr<MessageServiceIf> iface_;
};

class MessageServiceNull : virtual public MessageServiceIf {
 public:
  virtual ~MessageServiceNull() {}
  void ping(std::string& /* _return */, const std::string& /* text */) {
    return;
  }
  void ComposeMessage(const std::string& /* text */, const std::vector<std::string> & /* users */) {
    return;
  }
  void ReadMessage(std::string& /* _return */, const int64_t /* messageID */) {
    return;
  }
  void GetMessages(std::vector<Message> & /* _return */, const int64_t /* userID */) {
    return;
  }
};

typedef struct _MessageService_ping_args__isset {
  _MessageService_ping_args__isset() : text(false) {}
  bool text :1;
} _MessageService_ping_args__isset;

class MessageService_ping_args {
 public:

  MessageService_ping_args(const MessageService_ping_args&);
  MessageService_ping_args& operator=(const MessageService_ping_args&);
  MessageService_ping_args() : text() {
  }

  virtual ~MessageService_ping_args() noexcept;
  std::string text;

  _MessageService_ping_args__isset __isset;

  void __set_text(const std::string& val);

  bool operator == (const MessageService_ping_args & rhs) const
  {
    if (!(text == rhs.text))
      return false;
    return true;
  }
  bool operator != (const MessageService_ping_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const MessageService_ping_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class MessageService_ping_pargs {
 public:


  virtual ~MessageService_ping_pargs() noexcept;
  const std::string* text;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _MessageService_ping_result__isset {
  _MessageService_ping_result__isset() : success(false) {}
  bool success :1;
} _MessageService_ping_result__isset;

class MessageService_ping_result {
 public:

  MessageService_ping_result(const MessageService_ping_result&);
  MessageService_ping_result& operator=(const MessageService_ping_result&);
  MessageService_ping_result() : success() {
  }

  virtual ~MessageService_ping_result() noexcept;
  std::string success;

  _MessageService_ping_result__isset __isset;

  void __set_success(const std::string& val);

  bool operator == (const MessageService_ping_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    return true;
  }
  bool operator != (const MessageService_ping_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const MessageService_ping_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _MessageService_ping_presult__isset {
  _MessageService_ping_presult__isset() : success(false) {}
  bool success :1;
} _MessageService_ping_presult__isset;

class MessageService_ping_presult {
 public:


  virtual ~MessageService_ping_presult() noexcept;
  std::string* success;

  _MessageService_ping_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

typedef struct _MessageService_ComposeMessage_args__isset {
  _MessageService_ComposeMessage_args__isset() : text(false), users(false) {}
  bool text :1;
  bool users :1;
} _MessageService_ComposeMessage_args__isset;

class MessageService_ComposeMessage_args {
 public:

  MessageService_ComposeMessage_args(const MessageService_ComposeMessage_args&);
  MessageService_ComposeMessage_args& operator=(const MessageService_ComposeMessage_args&);
  MessageService_ComposeMessage_args() : text() {
  }

  virtual ~MessageService_ComposeMessage_args() noexcept;
  std::string text;
  std::vector<std::string>  users;

  _MessageService_ComposeMessage_args__isset __isset;

  void __set_text(const std::string& val);

  void __set_users(const std::vector<std::string> & val);

  bool operator == (const MessageService_ComposeMessage_args & rhs) const
  {
    if (!(text == rhs.text))
      return false;
    if (!(users == rhs.users))
      return false;
    return true;
  }
  bool operator != (const MessageService_ComposeMessage_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const MessageService_ComposeMessage_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class MessageService_ComposeMessage_pargs {
 public:


  virtual ~MessageService_ComposeMessage_pargs() noexcept;
  const std::string* text;
  const std::vector<std::string> * users;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _MessageService_ComposeMessage_result__isset {
  _MessageService_ComposeMessage_result__isset() : se(false) {}
  bool se :1;
} _MessageService_ComposeMessage_result__isset;

class MessageService_ComposeMessage_result {
 public:

  MessageService_ComposeMessage_result(const MessageService_ComposeMessage_result&);
  MessageService_ComposeMessage_result& operator=(const MessageService_ComposeMessage_result&);
  MessageService_ComposeMessage_result() {
  }

  virtual ~MessageService_ComposeMessage_result() noexcept;
  ServiceException se;

  _MessageService_ComposeMessage_result__isset __isset;

  void __set_se(const ServiceException& val);

  bool operator == (const MessageService_ComposeMessage_result & rhs) const
  {
    if (!(se == rhs.se))
      return false;
    return true;
  }
  bool operator != (const MessageService_ComposeMessage_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const MessageService_ComposeMessage_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _MessageService_ComposeMessage_presult__isset {
  _MessageService_ComposeMessage_presult__isset() : se(false) {}
  bool se :1;
} _MessageService_ComposeMessage_presult__isset;

class MessageService_ComposeMessage_presult {
 public:


  virtual ~MessageService_ComposeMessage_presult() noexcept;
  ServiceException se;

  _MessageService_ComposeMessage_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

typedef struct _MessageService_ReadMessage_args__isset {
  _MessageService_ReadMessage_args__isset() : messageID(false) {}
  bool messageID :1;
} _MessageService_ReadMessage_args__isset;

class MessageService_ReadMessage_args {
 public:

  MessageService_ReadMessage_args(const MessageService_ReadMessage_args&);
  MessageService_ReadMessage_args& operator=(const MessageService_ReadMessage_args&);
  MessageService_ReadMessage_args() : messageID(0) {
  }

  virtual ~MessageService_ReadMessage_args() noexcept;
  int64_t messageID;

  _MessageService_ReadMessage_args__isset __isset;

  void __set_messageID(const int64_t val);

  bool operator == (const MessageService_ReadMessage_args & rhs) const
  {
    if (!(messageID == rhs.messageID))
      return false;
    return true;
  }
  bool operator != (const MessageService_ReadMessage_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const MessageService_ReadMessage_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class MessageService_ReadMessage_pargs {
 public:


  virtual ~MessageService_ReadMessage_pargs() noexcept;
  const int64_t* messageID;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _MessageService_ReadMessage_result__isset {
  _MessageService_ReadMessage_result__isset() : success(false), se(false) {}
  bool success :1;
  bool se :1;
} _MessageService_ReadMessage_result__isset;

class MessageService_ReadMessage_result {
 public:

  MessageService_ReadMessage_result(const MessageService_ReadMessage_result&);
  MessageService_ReadMessage_result& operator=(const MessageService_ReadMessage_result&);
  MessageService_ReadMessage_result() : success() {
  }

  virtual ~MessageService_ReadMessage_result() noexcept;
  std::string success;
  ServiceException se;

  _MessageService_ReadMessage_result__isset __isset;

  void __set_success(const std::string& val);

  void __set_se(const ServiceException& val);

  bool operator == (const MessageService_ReadMessage_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    if (!(se == rhs.se))
      return false;
    return true;
  }
  bool operator != (const MessageService_ReadMessage_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const MessageService_ReadMessage_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _MessageService_ReadMessage_presult__isset {
  _MessageService_ReadMessage_presult__isset() : success(false), se(false) {}
  bool success :1;
  bool se :1;
} _MessageService_ReadMessage_presult__isset;

class MessageService_ReadMessage_presult {
 public:


  virtual ~MessageService_ReadMessage_presult() noexcept;
  std::string* success;
  ServiceException se;

  _MessageService_ReadMessage_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

typedef struct _MessageService_GetMessages_args__isset {
  _MessageService_GetMessages_args__isset() : userID(false) {}
  bool userID :1;
} _MessageService_GetMessages_args__isset;

class MessageService_GetMessages_args {
 public:

  MessageService_GetMessages_args(const MessageService_GetMessages_args&);
  MessageService_GetMessages_args& operator=(const MessageService_GetMessages_args&);
  MessageService_GetMessages_args() : userID(0) {
  }

  virtual ~MessageService_GetMessages_args() noexcept;
  int64_t userID;

  _MessageService_GetMessages_args__isset __isset;

  void __set_userID(const int64_t val);

  bool operator == (const MessageService_GetMessages_args & rhs) const
  {
    if (!(userID == rhs.userID))
      return false;
    return true;
  }
  bool operator != (const MessageService_GetMessages_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const MessageService_GetMessages_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class MessageService_GetMessages_pargs {
 public:


  virtual ~MessageService_GetMessages_pargs() noexcept;
  const int64_t* userID;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _MessageService_GetMessages_result__isset {
  _MessageService_GetMessages_result__isset() : success(false), se(false) {}
  bool success :1;
  bool se :1;
} _MessageService_GetMessages_result__isset;

class MessageService_GetMessages_result {
 public:

  MessageService_GetMessages_result(const MessageService_GetMessages_result&);
  MessageService_GetMessages_result& operator=(const MessageService_GetMessages_result&);
  MessageService_GetMessages_result() {
  }

  virtual ~MessageService_GetMessages_result() noexcept;
  std::vector<Message>  success;
  ServiceException se;

  _MessageService_GetMessages_result__isset __isset;

  void __set_success(const std::vector<Message> & val);

  void __set_se(const ServiceException& val);

  bool operator == (const MessageService_GetMessages_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    if (!(se == rhs.se))
      return false;
    return true;
  }
  bool operator != (const MessageService_GetMessages_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const MessageService_GetMessages_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _MessageService_GetMessages_presult__isset {
  _MessageService_GetMessages_presult__isset() : success(false), se(false) {}
  bool success :1;
  bool se :1;
} _MessageService_GetMessages_presult__isset;

class MessageService_GetMessages_presult {
 public:


  virtual ~MessageService_GetMessages_presult() noexcept;
  std::vector<Message> * success;
  ServiceException se;

  _MessageService_GetMessages_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

class MessageServiceClient : virtual public MessageServiceIf {
 public:
  MessageServiceClient(std::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
    setProtocol(prot);
  }
  MessageServiceClient(std::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, std::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
    setProtocol(iprot,oprot);
  }
 private:
  void setProtocol(std::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
  setProtocol(prot,prot);
  }
  void setProtocol(std::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, std::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
    piprot_=iprot;
    poprot_=oprot;
    iprot_ = iprot.get();
    oprot_ = oprot.get();
  }
 public:
  std::shared_ptr< ::apache::thrift::protocol::TProtocol> getInputProtocol() {
    return piprot_;
  }
  std::shared_ptr< ::apache::thrift::protocol::TProtocol> getOutputProtocol() {
    return poprot_;
  }
  void ping(std::string& _return, const std::string& text);
  void send_ping(const std::string& text);
  void recv_ping(std::string& _return);
  void ComposeMessage(const std::string& text, const std::vector<std::string> & users);
  void send_ComposeMessage(const std::string& text, const std::vector<std::string> & users);
  void recv_ComposeMessage();
  void ReadMessage(std::string& _return, const int64_t messageID);
  void send_ReadMessage(const int64_t messageID);
  void recv_ReadMessage(std::string& _return);
  void GetMessages(std::vector<Message> & _return, const int64_t userID);
  void send_GetMessages(const int64_t userID);
  void recv_GetMessages(std::vector<Message> & _return);
 protected:
  std::shared_ptr< ::apache::thrift::protocol::TProtocol> piprot_;
  std::shared_ptr< ::apache::thrift::protocol::TProtocol> poprot_;
  ::apache::thrift::protocol::TProtocol* iprot_;
  ::apache::thrift::protocol::TProtocol* oprot_;
};

class MessageServiceProcessor : public ::apache::thrift::TDispatchProcessor {
 protected:
  ::std::shared_ptr<MessageServiceIf> iface_;
  virtual bool dispatchCall(::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, const std::string& fname, int32_t seqid, void* callContext);
 private:
  typedef  void (MessageServiceProcessor::*ProcessFunction)(int32_t, ::apache::thrift::protocol::TProtocol*, ::apache::thrift::protocol::TProtocol*, void*);
  typedef std::map<std::string, ProcessFunction> ProcessMap;
  ProcessMap processMap_;
  void process_ping(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_ComposeMessage(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_ReadMessage(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_GetMessages(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
 public:
  MessageServiceProcessor(::std::shared_ptr<MessageServiceIf> iface) :
    iface_(iface) {
    processMap_["ping"] = &MessageServiceProcessor::process_ping;
    processMap_["ComposeMessage"] = &MessageServiceProcessor::process_ComposeMessage;
    processMap_["ReadMessage"] = &MessageServiceProcessor::process_ReadMessage;
    processMap_["GetMessages"] = &MessageServiceProcessor::process_GetMessages;
  }

  virtual ~MessageServiceProcessor() {}
};

class MessageServiceProcessorFactory : public ::apache::thrift::TProcessorFactory {
 public:
  MessageServiceProcessorFactory(const ::std::shared_ptr< MessageServiceIfFactory >& handlerFactory) :
      handlerFactory_(handlerFactory) {}

  ::std::shared_ptr< ::apache::thrift::TProcessor > getProcessor(const ::apache::thrift::TConnectionInfo& connInfo);

 protected:
  ::std::shared_ptr< MessageServiceIfFactory > handlerFactory_;
};

class MessageServiceMultiface : virtual public MessageServiceIf {
 public:
  MessageServiceMultiface(std::vector<std::shared_ptr<MessageServiceIf> >& ifaces) : ifaces_(ifaces) {
  }
  virtual ~MessageServiceMultiface() {}
 protected:
  std::vector<std::shared_ptr<MessageServiceIf> > ifaces_;
  MessageServiceMultiface() {}
  void add(::std::shared_ptr<MessageServiceIf> iface) {
    ifaces_.push_back(iface);
  }
 public:
  void ping(std::string& _return, const std::string& text) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->ping(_return, text);
    }
    ifaces_[i]->ping(_return, text);
    return;
  }

  void ComposeMessage(const std::string& text, const std::vector<std::string> & users) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->ComposeMessage(text, users);
    }
    ifaces_[i]->ComposeMessage(text, users);
  }

  void ReadMessage(std::string& _return, const int64_t messageID) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->ReadMessage(_return, messageID);
    }
    ifaces_[i]->ReadMessage(_return, messageID);
    return;
  }

  void GetMessages(std::vector<Message> & _return, const int64_t userID) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->GetMessages(_return, userID);
    }
    ifaces_[i]->GetMessages(_return, userID);
    return;
  }

};

// The 'concurrent' client is a thread safe client that correctly handles
// out of order responses.  It is slower than the regular client, so should
// only be used when you need to share a connection among multiple threads
class MessageServiceConcurrentClient : virtual public MessageServiceIf {
 public:
  MessageServiceConcurrentClient(std::shared_ptr< ::apache::thrift::protocol::TProtocol> prot, std::shared_ptr<::apache::thrift::async::TConcurrentClientSyncInfo> sync) : sync_(sync)
{
    setProtocol(prot);
  }
  MessageServiceConcurrentClient(std::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, std::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot, std::shared_ptr<::apache::thrift::async::TConcurrentClientSyncInfo> sync) : sync_(sync)
{
    setProtocol(iprot,oprot);
  }
 private:
  void setProtocol(std::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
  setProtocol(prot,prot);
  }
  void setProtocol(std::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, std::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
    piprot_=iprot;
    poprot_=oprot;
    iprot_ = iprot.get();
    oprot_ = oprot.get();
  }
 public:
  std::shared_ptr< ::apache::thrift::protocol::TProtocol> getInputProtocol() {
    return piprot_;
  }
  std::shared_ptr< ::apache::thrift::protocol::TProtocol> getOutputProtocol() {
    return poprot_;
  }
  void ping(std::string& _return, const std::string& text);
  int32_t send_ping(const std::string& text);
  void recv_ping(std::string& _return, const int32_t seqid);
  void ComposeMessage(const std::string& text, const std::vector<std::string> & users);
  int32_t send_ComposeMessage(const std::string& text, const std::vector<std::string> & users);
  void recv_ComposeMessage(const int32_t seqid);
  void ReadMessage(std::string& _return, const int64_t messageID);
  int32_t send_ReadMessage(const int64_t messageID);
  void recv_ReadMessage(std::string& _return, const int32_t seqid);
  void GetMessages(std::vector<Message> & _return, const int64_t userID);
  int32_t send_GetMessages(const int64_t userID);
  void recv_GetMessages(std::vector<Message> & _return, const int32_t seqid);
 protected:
  std::shared_ptr< ::apache::thrift::protocol::TProtocol> piprot_;
  std::shared_ptr< ::apache::thrift::protocol::TProtocol> poprot_;
  ::apache::thrift::protocol::TProtocol* iprot_;
  ::apache::thrift::protocol::TProtocol* oprot_;
  std::shared_ptr<::apache::thrift::async::TConcurrentClientSyncInfo> sync_;
};

#ifdef _MSC_VER
  #pragma warning( pop )
#endif

} // namespace

#endif
