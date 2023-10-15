#include <string>

std::string get_entity_like_key(int entity_type, int entity_id);

// 某个用户的赞
// like:user:userId -> int
std::string get_user_like_key(int user_id);

// 某个用户关注的实体
// followee:userId:entityType -> zset(entityId,now)
std::string get_followee_key(int user_id, int entity_type);

// 某个实体拥有的粉丝
// follower:entityType:entityId -> zset(userId,now)
std::string get_follower_key(int entity_type, int entity_id);

// 用户
std::string get_user_key(int user_id);