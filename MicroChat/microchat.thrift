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

  string Ping(1:i32 id),
  string Login(1:string username, 2:string password),
  void CreateUser(1:string username, 2:string name, 3:string password),
  i64 GetUserID(1:string username)

}

service MessageService{
  string ping(1:string text),
  void ComposeMessage(1:string text, 2:list<string> users),
  string ReadMessage(1:i64 messageID),
}

service FriendRecommendationService{

  string ping(1:string text),
  list<User> GetFriendRecommendations(1:User user),

}

service DatabaseService{
  string ping(1:string text),
  string WriteToDatabase(1:string query),
  string ReadFromDatabase(1:string query),
}

