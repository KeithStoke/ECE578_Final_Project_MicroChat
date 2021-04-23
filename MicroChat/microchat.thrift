namespace cpp microchat
namespace lua microchat

enum ErrorCode {
  SE_CONNPOOL_TIMEOUT,
  SE_THRIFT_CONN_ERROR,
  SE_UNAUTHORIZED,
  SE_MEMCACHED_ERROR,
  SE_MONGODB_ERROR,
  SE_REDIS_ERROR,
  SE_THRIFT_HANDLER_ERROR,
  SE_RABBITMQ_CONN_ERROR
}

enum UserStatus{
  ONLINE,
  OFFLINE
}

enum MessageStatus{
  UNREAD,
  READ
}

exception ServiceException {
    1: ErrorCode errorCode,
    2: string message,
}

struct User {
  1: i64 userID,
  2: string username,
  3: string name,
  4: UserStatus userStatus,
}

struct Message {
  1: i64 messageID,
  2: string text,
  3: string sender,
  4: string recipient,
  6: i64 timestamp,
  7: MessageStatus messageStatus
}

service UserService{

  string ping(1:i32 id),
  string Login(1:string username, 2:string password) throws (1: ServiceException se),
  string CreateUser(1:string username, 2:string name, 3:string password) throws (1: ServiceException se),
  string GetUserID(1:string username) throws (1: ServiceException se),
  string Logout(1:string username) throws (1:ServiceException se),


}

service MessageService{
  string ComposeMessage(1:string text, 2:string sender, 3:string user) throws (1: ServiceException se),
  string ReadMessage(1:i64 messageID, 2:string username) throws (1: ServiceException se),
  string GetMessages(1:string username) throws (1: ServiceException se),
  string GetUnreadMessages(1:string username) throws(1:ServiceException se),
  string GetReadMessages(1:string username) throws(1:ServiceException se)
}

service FriendRecommendationService{

  string ping(1:string text),
  string GetFriendRecommendations(1:string username) throws (1: ServiceException se),

}

service DatabaseService{
  string CreateUser(1:string username, 2:string name, 3:string password, 4:i64 userID) throws(1:ServiceException se),
  string CheckForUser(1:string username) throws(1:ServiceException se),
  string Login(1:string username, 2:string password) throws(1:ServiceException se),
  string Logout(1:string username) throws(1:ServiceException se),
}

