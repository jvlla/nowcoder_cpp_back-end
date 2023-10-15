#include "RedisKeyUtil.h"
#include <string>
using namespace std;

string SPLIT = ":";
string PREFIX_ENTITY_LIKE = "like:entity";
string PREFIX_USER_LIKE = "like:user";
string PREFIX_FOLLOWEE = "followee";
string PREFIX_FOLLOWER = "follower";
string PREFIX_USER = "user";

// 某个实体的赞
// like:entity:entityType:entityId -> set(userId)
string get_entity_like_key(int entity_type, int entity_id) {
    return PREFIX_ENTITY_LIKE + SPLIT + to_string(entity_type) + SPLIT + to_string(entity_id);
}

// 某个用户的赞
// like:user:userId -> int
string get_user_like_key(int user_id) {
    return PREFIX_USER_LIKE + SPLIT + to_string(user_id);
}

// 某个用户关注的实体
// followee:userId:entityType -> zset(entityId,now)
string get_followee_key(int user_id, int entity_type) {
    return PREFIX_FOLLOWEE + SPLIT + to_string(user_id) + SPLIT + to_string(entity_type);
}

// 某个实体拥有的粉丝
// follower:entityType:entityId -> zset(userId,now)
string get_follower_key(int entity_type, int entity_id) {
    return PREFIX_FOLLOWER + SPLIT + to_string(entity_type) + SPLIT + to_string(entity_id);
}

// 用户
string get_user_key(int user_id) {
    return PREFIX_USER + SPLIT + to_string(user_id);
}
