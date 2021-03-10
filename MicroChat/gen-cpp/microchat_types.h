/**
 * Autogenerated by Thrift Compiler (0.13.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef microchat_TYPES_H
#define microchat_TYPES_H

#include <iosfwd>

#include <thrift/Thrift.h>
#include <thrift/TApplicationException.h>
#include <thrift/TBase.h>
#include <thrift/protocol/TProtocol.h>
#include <thrift/transport/TTransport.h>

#include <functional>
#include <memory>


namespace microchat {

struct ErrorCode {
  enum type {
    SE_CONNPOOL_TIMEOUT = 0,
    SE_THRIFT_CONN_ERROR = 1,
    SE_UNAUTHORIZED = 2,
    SE_MEMCACHED_ERROR = 3,
    SE_MONGODB_ERROR = 4,
    SE_REDIS_ERROR = 5,
    SE_THRIFT_HANDLER_ERROR = 6,
    SE_RABBITMQ_CONN_ERROR = 7
  };
};

extern const std::map<int, const char*> _ErrorCode_VALUES_TO_NAMES;

std::ostream& operator<<(std::ostream& out, const ErrorCode::type& val);

std::string to_string(const ErrorCode::type& val);

struct UserStatus {
  enum type {
    ONLINE = 0,
    OFFLINE = 1,
    AWAY = 2
  };
};

extern const std::map<int, const char*> _UserStatus_VALUES_TO_NAMES;

std::ostream& operator<<(std::ostream& out, const UserStatus::type& val);

std::string to_string(const UserStatus::type& val);

class ServiceException;

class User;

class Emoji;

class Message;

typedef struct _ServiceException__isset {
  _ServiceException__isset() : errorCode(false), message(false) {}
  bool errorCode :1;
  bool message :1;
} _ServiceException__isset;

class ServiceException : public ::apache::thrift::TException {
 public:

  ServiceException(const ServiceException&);
  ServiceException& operator=(const ServiceException&);
  ServiceException() : errorCode((ErrorCode::type)0), message() {
  }

  virtual ~ServiceException() noexcept;
  ErrorCode::type errorCode;
  std::string message;

  _ServiceException__isset __isset;

  void __set_errorCode(const ErrorCode::type val);

  void __set_message(const std::string& val);

  bool operator == (const ServiceException & rhs) const
  {
    if (!(errorCode == rhs.errorCode))
      return false;
    if (!(message == rhs.message))
      return false;
    return true;
  }
  bool operator != (const ServiceException &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const ServiceException & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
  mutable std::string thriftTExceptionMessageHolder_;
  const char* what() const noexcept;
};

void swap(ServiceException &a, ServiceException &b);

std::ostream& operator<<(std::ostream& out, const ServiceException& obj);

typedef struct _User__isset {
  _User__isset() : userID(false), username(false), name(false), userStatus(false) {}
  bool userID :1;
  bool username :1;
  bool name :1;
  bool userStatus :1;
} _User__isset;

class User : public virtual ::apache::thrift::TBase {
 public:

  User(const User&);
  User& operator=(const User&);
  User() : userID(0), username(), name(), userStatus((UserStatus::type)0) {
  }

  virtual ~User() noexcept;
  int32_t userID;
  std::string username;
  std::string name;
  UserStatus::type userStatus;

  _User__isset __isset;

  void __set_userID(const int32_t val);

  void __set_username(const std::string& val);

  void __set_name(const std::string& val);

  void __set_userStatus(const UserStatus::type val);

  bool operator == (const User & rhs) const
  {
    if (!(userID == rhs.userID))
      return false;
    if (!(username == rhs.username))
      return false;
    if (!(name == rhs.name))
      return false;
    if (!(userStatus == rhs.userStatus))
      return false;
    return true;
  }
  bool operator != (const User &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const User & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
};

void swap(User &a, User &b);

std::ostream& operator<<(std::ostream& out, const User& obj);

typedef struct _Emoji__isset {
  _Emoji__isset() : emojiID(false), emojiname(false) {}
  bool emojiID :1;
  bool emojiname :1;
} _Emoji__isset;

class Emoji : public virtual ::apache::thrift::TBase {
 public:

  Emoji(const Emoji&);
  Emoji& operator=(const Emoji&);
  Emoji() : emojiID(0), emojiname() {
  }

  virtual ~Emoji() noexcept;
  int32_t emojiID;
  std::string emojiname;

  _Emoji__isset __isset;

  void __set_emojiID(const int32_t val);

  void __set_emojiname(const std::string& val);

  bool operator == (const Emoji & rhs) const
  {
    if (!(emojiID == rhs.emojiID))
      return false;
    if (!(emojiname == rhs.emojiname))
      return false;
    return true;
  }
  bool operator != (const Emoji &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const Emoji & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
};

void swap(Emoji &a, Emoji &b);

std::ostream& operator<<(std::ostream& out, const Emoji& obj);

typedef struct _Message__isset {
  _Message__isset() : messageID(false), text(false), sender(false), recipients(false), reactions(false) {}
  bool messageID :1;
  bool text :1;
  bool sender :1;
  bool recipients :1;
  bool reactions :1;
} _Message__isset;

class Message : public virtual ::apache::thrift::TBase {
 public:

  Message(const Message&);
  Message& operator=(const Message&);
  Message() : messageID(0), text() {
  }

  virtual ~Message() noexcept;
  int32_t messageID;
  std::string text;
  User sender;
  std::vector<User>  recipients;
  std::vector<Emoji>  reactions;

  _Message__isset __isset;

  void __set_messageID(const int32_t val);

  void __set_text(const std::string& val);

  void __set_sender(const User& val);

  void __set_recipients(const std::vector<User> & val);

  void __set_reactions(const std::vector<Emoji> & val);

  bool operator == (const Message & rhs) const
  {
    if (!(messageID == rhs.messageID))
      return false;
    if (!(text == rhs.text))
      return false;
    if (!(sender == rhs.sender))
      return false;
    if (!(recipients == rhs.recipients))
      return false;
    if (!(reactions == rhs.reactions))
      return false;
    return true;
  }
  bool operator != (const Message &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const Message & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
};

void swap(Message &a, Message &b);

std::ostream& operator<<(std::ostream& out, const Message& obj);

} // namespace

#endif
