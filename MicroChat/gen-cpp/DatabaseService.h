/**
 * Autogenerated by Thrift Compiler (0.13.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef DatabaseService_H
#define DatabaseService_H

#include <thrift/TDispatchProcessor.h>
#include <thrift/async/TConcurrentClientSyncInfo.h>
#include <memory>
#include "microchat_types.h"

namespace microchat {

#ifdef _MSC_VER
  #pragma warning( push )
  #pragma warning (disable : 4250 ) //inheriting methods via dominance 
#endif

class DatabaseServiceIf {
 public:
  virtual ~DatabaseServiceIf() {}
  virtual void ping(std::string& _return, const std::string& text) = 0;
  virtual void WriteToDatabase(std::string& _return, const std::string& query) = 0;
  virtual void ReadFromDatabase(std::string& _return, const std::string& query) = 0;
  virtual void CreateUser(std::string& _return, const std::string& username, const std::string& name, const std::string& password, const int64_t userID) = 0;
  virtual void CheckForUser(std::string& _return, const std::string& username) = 0;
  virtual void Login(std::string& _return, const std::string& username, const std::string& password) = 0;
};

class DatabaseServiceIfFactory {
 public:
  typedef DatabaseServiceIf Handler;

  virtual ~DatabaseServiceIfFactory() {}

  virtual DatabaseServiceIf* getHandler(const ::apache::thrift::TConnectionInfo& connInfo) = 0;
  virtual void releaseHandler(DatabaseServiceIf* /* handler */) = 0;
};

class DatabaseServiceIfSingletonFactory : virtual public DatabaseServiceIfFactory {
 public:
  DatabaseServiceIfSingletonFactory(const ::std::shared_ptr<DatabaseServiceIf>& iface) : iface_(iface) {}
  virtual ~DatabaseServiceIfSingletonFactory() {}

  virtual DatabaseServiceIf* getHandler(const ::apache::thrift::TConnectionInfo&) {
    return iface_.get();
  }
  virtual void releaseHandler(DatabaseServiceIf* /* handler */) {}

 protected:
  ::std::shared_ptr<DatabaseServiceIf> iface_;
};

class DatabaseServiceNull : virtual public DatabaseServiceIf {
 public:
  virtual ~DatabaseServiceNull() {}
  void ping(std::string& /* _return */, const std::string& /* text */) {
    return;
  }
  void WriteToDatabase(std::string& /* _return */, const std::string& /* query */) {
    return;
  }
  void ReadFromDatabase(std::string& /* _return */, const std::string& /* query */) {
    return;
  }
  void CreateUser(std::string& /* _return */, const std::string& /* username */, const std::string& /* name */, const std::string& /* password */, const int64_t /* userID */) {
    return;
  }
  void CheckForUser(std::string& /* _return */, const std::string& /* username */) {
    return;
  }
  void Login(std::string& /* _return */, const std::string& /* username */, const std::string& /* password */) {
    return;
  }
};

typedef struct _DatabaseService_ping_args__isset {
  _DatabaseService_ping_args__isset() : text(false) {}
  bool text :1;
} _DatabaseService_ping_args__isset;

class DatabaseService_ping_args {
 public:

  DatabaseService_ping_args(const DatabaseService_ping_args&);
  DatabaseService_ping_args& operator=(const DatabaseService_ping_args&);
  DatabaseService_ping_args() : text() {
  }

  virtual ~DatabaseService_ping_args() noexcept;
  std::string text;

  _DatabaseService_ping_args__isset __isset;

  void __set_text(const std::string& val);

  bool operator == (const DatabaseService_ping_args & rhs) const
  {
    if (!(text == rhs.text))
      return false;
    return true;
  }
  bool operator != (const DatabaseService_ping_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const DatabaseService_ping_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class DatabaseService_ping_pargs {
 public:


  virtual ~DatabaseService_ping_pargs() noexcept;
  const std::string* text;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _DatabaseService_ping_result__isset {
  _DatabaseService_ping_result__isset() : success(false) {}
  bool success :1;
} _DatabaseService_ping_result__isset;

class DatabaseService_ping_result {
 public:

  DatabaseService_ping_result(const DatabaseService_ping_result&);
  DatabaseService_ping_result& operator=(const DatabaseService_ping_result&);
  DatabaseService_ping_result() : success() {
  }

  virtual ~DatabaseService_ping_result() noexcept;
  std::string success;

  _DatabaseService_ping_result__isset __isset;

  void __set_success(const std::string& val);

  bool operator == (const DatabaseService_ping_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    return true;
  }
  bool operator != (const DatabaseService_ping_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const DatabaseService_ping_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _DatabaseService_ping_presult__isset {
  _DatabaseService_ping_presult__isset() : success(false) {}
  bool success :1;
} _DatabaseService_ping_presult__isset;

class DatabaseService_ping_presult {
 public:


  virtual ~DatabaseService_ping_presult() noexcept;
  std::string* success;

  _DatabaseService_ping_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

typedef struct _DatabaseService_WriteToDatabase_args__isset {
  _DatabaseService_WriteToDatabase_args__isset() : query(false) {}
  bool query :1;
} _DatabaseService_WriteToDatabase_args__isset;

class DatabaseService_WriteToDatabase_args {
 public:

  DatabaseService_WriteToDatabase_args(const DatabaseService_WriteToDatabase_args&);
  DatabaseService_WriteToDatabase_args& operator=(const DatabaseService_WriteToDatabase_args&);
  DatabaseService_WriteToDatabase_args() : query() {
  }

  virtual ~DatabaseService_WriteToDatabase_args() noexcept;
  std::string query;

  _DatabaseService_WriteToDatabase_args__isset __isset;

  void __set_query(const std::string& val);

  bool operator == (const DatabaseService_WriteToDatabase_args & rhs) const
  {
    if (!(query == rhs.query))
      return false;
    return true;
  }
  bool operator != (const DatabaseService_WriteToDatabase_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const DatabaseService_WriteToDatabase_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class DatabaseService_WriteToDatabase_pargs {
 public:


  virtual ~DatabaseService_WriteToDatabase_pargs() noexcept;
  const std::string* query;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _DatabaseService_WriteToDatabase_result__isset {
  _DatabaseService_WriteToDatabase_result__isset() : success(false), se(false) {}
  bool success :1;
  bool se :1;
} _DatabaseService_WriteToDatabase_result__isset;

class DatabaseService_WriteToDatabase_result {
 public:

  DatabaseService_WriteToDatabase_result(const DatabaseService_WriteToDatabase_result&);
  DatabaseService_WriteToDatabase_result& operator=(const DatabaseService_WriteToDatabase_result&);
  DatabaseService_WriteToDatabase_result() : success() {
  }

  virtual ~DatabaseService_WriteToDatabase_result() noexcept;
  std::string success;
  ServiceException se;

  _DatabaseService_WriteToDatabase_result__isset __isset;

  void __set_success(const std::string& val);

  void __set_se(const ServiceException& val);

  bool operator == (const DatabaseService_WriteToDatabase_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    if (!(se == rhs.se))
      return false;
    return true;
  }
  bool operator != (const DatabaseService_WriteToDatabase_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const DatabaseService_WriteToDatabase_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _DatabaseService_WriteToDatabase_presult__isset {
  _DatabaseService_WriteToDatabase_presult__isset() : success(false), se(false) {}
  bool success :1;
  bool se :1;
} _DatabaseService_WriteToDatabase_presult__isset;

class DatabaseService_WriteToDatabase_presult {
 public:


  virtual ~DatabaseService_WriteToDatabase_presult() noexcept;
  std::string* success;
  ServiceException se;

  _DatabaseService_WriteToDatabase_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

typedef struct _DatabaseService_ReadFromDatabase_args__isset {
  _DatabaseService_ReadFromDatabase_args__isset() : query(false) {}
  bool query :1;
} _DatabaseService_ReadFromDatabase_args__isset;

class DatabaseService_ReadFromDatabase_args {
 public:

  DatabaseService_ReadFromDatabase_args(const DatabaseService_ReadFromDatabase_args&);
  DatabaseService_ReadFromDatabase_args& operator=(const DatabaseService_ReadFromDatabase_args&);
  DatabaseService_ReadFromDatabase_args() : query() {
  }

  virtual ~DatabaseService_ReadFromDatabase_args() noexcept;
  std::string query;

  _DatabaseService_ReadFromDatabase_args__isset __isset;

  void __set_query(const std::string& val);

  bool operator == (const DatabaseService_ReadFromDatabase_args & rhs) const
  {
    if (!(query == rhs.query))
      return false;
    return true;
  }
  bool operator != (const DatabaseService_ReadFromDatabase_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const DatabaseService_ReadFromDatabase_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class DatabaseService_ReadFromDatabase_pargs {
 public:


  virtual ~DatabaseService_ReadFromDatabase_pargs() noexcept;
  const std::string* query;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _DatabaseService_ReadFromDatabase_result__isset {
  _DatabaseService_ReadFromDatabase_result__isset() : success(false), se(false) {}
  bool success :1;
  bool se :1;
} _DatabaseService_ReadFromDatabase_result__isset;

class DatabaseService_ReadFromDatabase_result {
 public:

  DatabaseService_ReadFromDatabase_result(const DatabaseService_ReadFromDatabase_result&);
  DatabaseService_ReadFromDatabase_result& operator=(const DatabaseService_ReadFromDatabase_result&);
  DatabaseService_ReadFromDatabase_result() : success() {
  }

  virtual ~DatabaseService_ReadFromDatabase_result() noexcept;
  std::string success;
  ServiceException se;

  _DatabaseService_ReadFromDatabase_result__isset __isset;

  void __set_success(const std::string& val);

  void __set_se(const ServiceException& val);

  bool operator == (const DatabaseService_ReadFromDatabase_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    if (!(se == rhs.se))
      return false;
    return true;
  }
  bool operator != (const DatabaseService_ReadFromDatabase_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const DatabaseService_ReadFromDatabase_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _DatabaseService_ReadFromDatabase_presult__isset {
  _DatabaseService_ReadFromDatabase_presult__isset() : success(false), se(false) {}
  bool success :1;
  bool se :1;
} _DatabaseService_ReadFromDatabase_presult__isset;

class DatabaseService_ReadFromDatabase_presult {
 public:


  virtual ~DatabaseService_ReadFromDatabase_presult() noexcept;
  std::string* success;
  ServiceException se;

  _DatabaseService_ReadFromDatabase_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

typedef struct _DatabaseService_CreateUser_args__isset {
  _DatabaseService_CreateUser_args__isset() : username(false), name(false), password(false), userID(false) {}
  bool username :1;
  bool name :1;
  bool password :1;
  bool userID :1;
} _DatabaseService_CreateUser_args__isset;

class DatabaseService_CreateUser_args {
 public:

  DatabaseService_CreateUser_args(const DatabaseService_CreateUser_args&);
  DatabaseService_CreateUser_args& operator=(const DatabaseService_CreateUser_args&);
  DatabaseService_CreateUser_args() : username(), name(), password(), userID(0) {
  }

  virtual ~DatabaseService_CreateUser_args() noexcept;
  std::string username;
  std::string name;
  std::string password;
  int64_t userID;

  _DatabaseService_CreateUser_args__isset __isset;

  void __set_username(const std::string& val);

  void __set_name(const std::string& val);

  void __set_password(const std::string& val);

  void __set_userID(const int64_t val);

  bool operator == (const DatabaseService_CreateUser_args & rhs) const
  {
    if (!(username == rhs.username))
      return false;
    if (!(name == rhs.name))
      return false;
    if (!(password == rhs.password))
      return false;
    if (!(userID == rhs.userID))
      return false;
    return true;
  }
  bool operator != (const DatabaseService_CreateUser_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const DatabaseService_CreateUser_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class DatabaseService_CreateUser_pargs {
 public:


  virtual ~DatabaseService_CreateUser_pargs() noexcept;
  const std::string* username;
  const std::string* name;
  const std::string* password;
  const int64_t* userID;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _DatabaseService_CreateUser_result__isset {
  _DatabaseService_CreateUser_result__isset() : success(false), se(false) {}
  bool success :1;
  bool se :1;
} _DatabaseService_CreateUser_result__isset;

class DatabaseService_CreateUser_result {
 public:

  DatabaseService_CreateUser_result(const DatabaseService_CreateUser_result&);
  DatabaseService_CreateUser_result& operator=(const DatabaseService_CreateUser_result&);
  DatabaseService_CreateUser_result() : success() {
  }

  virtual ~DatabaseService_CreateUser_result() noexcept;
  std::string success;
  ServiceException se;

  _DatabaseService_CreateUser_result__isset __isset;

  void __set_success(const std::string& val);

  void __set_se(const ServiceException& val);

  bool operator == (const DatabaseService_CreateUser_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    if (!(se == rhs.se))
      return false;
    return true;
  }
  bool operator != (const DatabaseService_CreateUser_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const DatabaseService_CreateUser_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _DatabaseService_CreateUser_presult__isset {
  _DatabaseService_CreateUser_presult__isset() : success(false), se(false) {}
  bool success :1;
  bool se :1;
} _DatabaseService_CreateUser_presult__isset;

class DatabaseService_CreateUser_presult {
 public:


  virtual ~DatabaseService_CreateUser_presult() noexcept;
  std::string* success;
  ServiceException se;

  _DatabaseService_CreateUser_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

typedef struct _DatabaseService_CheckForUser_args__isset {
  _DatabaseService_CheckForUser_args__isset() : username(false) {}
  bool username :1;
} _DatabaseService_CheckForUser_args__isset;

class DatabaseService_CheckForUser_args {
 public:

  DatabaseService_CheckForUser_args(const DatabaseService_CheckForUser_args&);
  DatabaseService_CheckForUser_args& operator=(const DatabaseService_CheckForUser_args&);
  DatabaseService_CheckForUser_args() : username() {
  }

  virtual ~DatabaseService_CheckForUser_args() noexcept;
  std::string username;

  _DatabaseService_CheckForUser_args__isset __isset;

  void __set_username(const std::string& val);

  bool operator == (const DatabaseService_CheckForUser_args & rhs) const
  {
    if (!(username == rhs.username))
      return false;
    return true;
  }
  bool operator != (const DatabaseService_CheckForUser_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const DatabaseService_CheckForUser_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class DatabaseService_CheckForUser_pargs {
 public:


  virtual ~DatabaseService_CheckForUser_pargs() noexcept;
  const std::string* username;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _DatabaseService_CheckForUser_result__isset {
  _DatabaseService_CheckForUser_result__isset() : success(false), se(false) {}
  bool success :1;
  bool se :1;
} _DatabaseService_CheckForUser_result__isset;

class DatabaseService_CheckForUser_result {
 public:

  DatabaseService_CheckForUser_result(const DatabaseService_CheckForUser_result&);
  DatabaseService_CheckForUser_result& operator=(const DatabaseService_CheckForUser_result&);
  DatabaseService_CheckForUser_result() : success() {
  }

  virtual ~DatabaseService_CheckForUser_result() noexcept;
  std::string success;
  ServiceException se;

  _DatabaseService_CheckForUser_result__isset __isset;

  void __set_success(const std::string& val);

  void __set_se(const ServiceException& val);

  bool operator == (const DatabaseService_CheckForUser_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    if (!(se == rhs.se))
      return false;
    return true;
  }
  bool operator != (const DatabaseService_CheckForUser_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const DatabaseService_CheckForUser_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _DatabaseService_CheckForUser_presult__isset {
  _DatabaseService_CheckForUser_presult__isset() : success(false), se(false) {}
  bool success :1;
  bool se :1;
} _DatabaseService_CheckForUser_presult__isset;

class DatabaseService_CheckForUser_presult {
 public:


  virtual ~DatabaseService_CheckForUser_presult() noexcept;
  std::string* success;
  ServiceException se;

  _DatabaseService_CheckForUser_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

typedef struct _DatabaseService_Login_args__isset {
  _DatabaseService_Login_args__isset() : username(false), password(false) {}
  bool username :1;
  bool password :1;
} _DatabaseService_Login_args__isset;

class DatabaseService_Login_args {
 public:

  DatabaseService_Login_args(const DatabaseService_Login_args&);
  DatabaseService_Login_args& operator=(const DatabaseService_Login_args&);
  DatabaseService_Login_args() : username(), password() {
  }

  virtual ~DatabaseService_Login_args() noexcept;
  std::string username;
  std::string password;

  _DatabaseService_Login_args__isset __isset;

  void __set_username(const std::string& val);

  void __set_password(const std::string& val);

  bool operator == (const DatabaseService_Login_args & rhs) const
  {
    if (!(username == rhs.username))
      return false;
    if (!(password == rhs.password))
      return false;
    return true;
  }
  bool operator != (const DatabaseService_Login_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const DatabaseService_Login_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class DatabaseService_Login_pargs {
 public:


  virtual ~DatabaseService_Login_pargs() noexcept;
  const std::string* username;
  const std::string* password;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _DatabaseService_Login_result__isset {
  _DatabaseService_Login_result__isset() : success(false), se(false) {}
  bool success :1;
  bool se :1;
} _DatabaseService_Login_result__isset;

class DatabaseService_Login_result {
 public:

  DatabaseService_Login_result(const DatabaseService_Login_result&);
  DatabaseService_Login_result& operator=(const DatabaseService_Login_result&);
  DatabaseService_Login_result() : success() {
  }

  virtual ~DatabaseService_Login_result() noexcept;
  std::string success;
  ServiceException se;

  _DatabaseService_Login_result__isset __isset;

  void __set_success(const std::string& val);

  void __set_se(const ServiceException& val);

  bool operator == (const DatabaseService_Login_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    if (!(se == rhs.se))
      return false;
    return true;
  }
  bool operator != (const DatabaseService_Login_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const DatabaseService_Login_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _DatabaseService_Login_presult__isset {
  _DatabaseService_Login_presult__isset() : success(false), se(false) {}
  bool success :1;
  bool se :1;
} _DatabaseService_Login_presult__isset;

class DatabaseService_Login_presult {
 public:


  virtual ~DatabaseService_Login_presult() noexcept;
  std::string* success;
  ServiceException se;

  _DatabaseService_Login_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

class DatabaseServiceClient : virtual public DatabaseServiceIf {
 public:
  DatabaseServiceClient(std::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
    setProtocol(prot);
  }
  DatabaseServiceClient(std::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, std::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
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
  void WriteToDatabase(std::string& _return, const std::string& query);
  void send_WriteToDatabase(const std::string& query);
  void recv_WriteToDatabase(std::string& _return);
  void ReadFromDatabase(std::string& _return, const std::string& query);
  void send_ReadFromDatabase(const std::string& query);
  void recv_ReadFromDatabase(std::string& _return);
  void CreateUser(std::string& _return, const std::string& username, const std::string& name, const std::string& password, const int64_t userID);
  void send_CreateUser(const std::string& username, const std::string& name, const std::string& password, const int64_t userID);
  void recv_CreateUser(std::string& _return);
  void CheckForUser(std::string& _return, const std::string& username);
  void send_CheckForUser(const std::string& username);
  void recv_CheckForUser(std::string& _return);
  void Login(std::string& _return, const std::string& username, const std::string& password);
  void send_Login(const std::string& username, const std::string& password);
  void recv_Login(std::string& _return);
 protected:
  std::shared_ptr< ::apache::thrift::protocol::TProtocol> piprot_;
  std::shared_ptr< ::apache::thrift::protocol::TProtocol> poprot_;
  ::apache::thrift::protocol::TProtocol* iprot_;
  ::apache::thrift::protocol::TProtocol* oprot_;
};

class DatabaseServiceProcessor : public ::apache::thrift::TDispatchProcessor {
 protected:
  ::std::shared_ptr<DatabaseServiceIf> iface_;
  virtual bool dispatchCall(::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, const std::string& fname, int32_t seqid, void* callContext);
 private:
  typedef  void (DatabaseServiceProcessor::*ProcessFunction)(int32_t, ::apache::thrift::protocol::TProtocol*, ::apache::thrift::protocol::TProtocol*, void*);
  typedef std::map<std::string, ProcessFunction> ProcessMap;
  ProcessMap processMap_;
  void process_ping(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_WriteToDatabase(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_ReadFromDatabase(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_CreateUser(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_CheckForUser(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_Login(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
 public:
  DatabaseServiceProcessor(::std::shared_ptr<DatabaseServiceIf> iface) :
    iface_(iface) {
    processMap_["ping"] = &DatabaseServiceProcessor::process_ping;
    processMap_["WriteToDatabase"] = &DatabaseServiceProcessor::process_WriteToDatabase;
    processMap_["ReadFromDatabase"] = &DatabaseServiceProcessor::process_ReadFromDatabase;
    processMap_["CreateUser"] = &DatabaseServiceProcessor::process_CreateUser;
    processMap_["CheckForUser"] = &DatabaseServiceProcessor::process_CheckForUser;
    processMap_["Login"] = &DatabaseServiceProcessor::process_Login;
  }

  virtual ~DatabaseServiceProcessor() {}
};

class DatabaseServiceProcessorFactory : public ::apache::thrift::TProcessorFactory {
 public:
  DatabaseServiceProcessorFactory(const ::std::shared_ptr< DatabaseServiceIfFactory >& handlerFactory) :
      handlerFactory_(handlerFactory) {}

  ::std::shared_ptr< ::apache::thrift::TProcessor > getProcessor(const ::apache::thrift::TConnectionInfo& connInfo);

 protected:
  ::std::shared_ptr< DatabaseServiceIfFactory > handlerFactory_;
};

class DatabaseServiceMultiface : virtual public DatabaseServiceIf {
 public:
  DatabaseServiceMultiface(std::vector<std::shared_ptr<DatabaseServiceIf> >& ifaces) : ifaces_(ifaces) {
  }
  virtual ~DatabaseServiceMultiface() {}
 protected:
  std::vector<std::shared_ptr<DatabaseServiceIf> > ifaces_;
  DatabaseServiceMultiface() {}
  void add(::std::shared_ptr<DatabaseServiceIf> iface) {
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

  void WriteToDatabase(std::string& _return, const std::string& query) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->WriteToDatabase(_return, query);
    }
    ifaces_[i]->WriteToDatabase(_return, query);
    return;
  }

  void ReadFromDatabase(std::string& _return, const std::string& query) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->ReadFromDatabase(_return, query);
    }
    ifaces_[i]->ReadFromDatabase(_return, query);
    return;
  }

  void CreateUser(std::string& _return, const std::string& username, const std::string& name, const std::string& password, const int64_t userID) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->CreateUser(_return, username, name, password, userID);
    }
    ifaces_[i]->CreateUser(_return, username, name, password, userID);
    return;
  }

  void CheckForUser(std::string& _return, const std::string& username) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->CheckForUser(_return, username);
    }
    ifaces_[i]->CheckForUser(_return, username);
    return;
  }

  void Login(std::string& _return, const std::string& username, const std::string& password) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->Login(_return, username, password);
    }
    ifaces_[i]->Login(_return, username, password);
    return;
  }

};

// The 'concurrent' client is a thread safe client that correctly handles
// out of order responses.  It is slower than the regular client, so should
// only be used when you need to share a connection among multiple threads
class DatabaseServiceConcurrentClient : virtual public DatabaseServiceIf {
 public:
  DatabaseServiceConcurrentClient(std::shared_ptr< ::apache::thrift::protocol::TProtocol> prot, std::shared_ptr<::apache::thrift::async::TConcurrentClientSyncInfo> sync) : sync_(sync)
{
    setProtocol(prot);
  }
  DatabaseServiceConcurrentClient(std::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, std::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot, std::shared_ptr<::apache::thrift::async::TConcurrentClientSyncInfo> sync) : sync_(sync)
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
  void WriteToDatabase(std::string& _return, const std::string& query);
  int32_t send_WriteToDatabase(const std::string& query);
  void recv_WriteToDatabase(std::string& _return, const int32_t seqid);
  void ReadFromDatabase(std::string& _return, const std::string& query);
  int32_t send_ReadFromDatabase(const std::string& query);
  void recv_ReadFromDatabase(std::string& _return, const int32_t seqid);
  void CreateUser(std::string& _return, const std::string& username, const std::string& name, const std::string& password, const int64_t userID);
  int32_t send_CreateUser(const std::string& username, const std::string& name, const std::string& password, const int64_t userID);
  void recv_CreateUser(std::string& _return, const int32_t seqid);
  void CheckForUser(std::string& _return, const std::string& username);
  int32_t send_CheckForUser(const std::string& username);
  void recv_CheckForUser(std::string& _return, const int32_t seqid);
  void Login(std::string& _return, const std::string& username, const std::string& password);
  int32_t send_Login(const std::string& username, const std::string& password);
  void recv_Login(std::string& _return, const int32_t seqid);
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
