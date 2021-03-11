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
  1: i32 userID,
  2: string username,
  3: string name,
  4: UserStatus userStatus,
}

struct Emoji {
  1: i32 emojiID,
  2: string emojiname,
}

struct Message {
  1: i32 messageID,
  2: string text,
  3: User sender,
  4: list<User> recipients,
  5: list<Emoji> reactions,
}

service UserService{

  string Ping(1:i32 id),
  User Login(1:string usernmae, 2:string password)throws(1: ServiceException se),
  User CreateUser(1:string username, 2:string name, 3:string password),

}

service MessageService{
  string ping(1:string text),
}

service FriendRecommendationService{

  string ping(1:string text),
  list<User> GetFriendRecommendations(1:User user),

}

service EmojiPredictionService{
  string ping(1:string text),
  Emoji GetEmoji(1:string text),

}

service DatabaseService{
  string ping(1:string text),
  string WriteToDatabase(1:string query),
  string ReadFromDatabase(1:string query),
}

