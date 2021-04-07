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
  OFFLINE,
  AWAY
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

struct Emoji {
  1: i64 emojiID,
  2: string emojiname,
}

struct Message {
  1: i64 messageID,
  2: string text,
  3: User sender,
  4: list<User> recipients,
  5: list<Emoji> reactions,
  6: i64 timestamp,
}

service UserService{

  string ping(1:i32 id),
  string Login(1:string username, 2:string password) throws (1: ServiceException se),
  void CreateUser(1:string username, 2:string name, 3:string password) throws (1: ServiceException se),
  i64 GetUserID(1:string username) throws (1: ServiceException se)

}

service MessageService{
  string ping(1:string text),
  void ComposeMessage(1:string text, 2:list<string> users) throws (1: ServiceException se),
  string ReadMessage(1:i64 messageID) throws (1: ServiceException se),
  list<Message> GetMessages(1:i64 userID) throws (1: ServiceException se)
}

service FriendRecommendationService{

  string ping(1:string text),
  list<string> GetFriendRecommendations(1:i64 userID) throws (1: ServiceException se),

}

service DatabaseService{
  string ping(1:string text),
  string WriteToDatabase(1:string query) throws (1: ServiceException se),
  string ReadFromDatabase(1:string query) throws (1: ServiceException se),
}

