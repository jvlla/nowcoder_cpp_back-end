#include "RedisKeyUtil.h"
#include <string>
using namespace std;

const string SPLIT = ":";
const string PREFIX_ENTITY_LIKE = "like:entity";
const string PREFIX_USER_LIKE = "like:user";
const string PREFIX_FOLLOWEE = "followee";
const string PREFIX_FOLLOWER = "follower";
const string PREFIX_USER = "user";
const string PREFIX_KAPTCHA = "kaptcha";

// like:entity:entityType:entityId -> set(userId)
string get_entity_like_key(int entity_type, int entity_id) {
    return PREFIX_ENTITY_LIKE + SPLIT + to_string(entity_type) + SPLIT + to_string(entity_id);
}

// like:user:userId -> int
string get_user_like_key(int user_id) {
    return PREFIX_USER_LIKE + SPLIT + to_string(user_id);
}

// followee:userId:entityType -> zset(entityId,now)
string get_followee_key(int user_id, int entity_type) {
    return PREFIX_FOLLOWEE + SPLIT + to_string(user_id) + SPLIT + to_string(entity_type);
}

// follower:entityType:entityId -> zset(userId,now)
string get_follower_key(int entity_type, int entity_id) {
    return PREFIX_FOLLOWER + SPLIT + to_string(entity_type) + SPLIT + to_string(entity_id);
}

// user:user_id -> string
string get_user_key(int user_id) {
    return PREFIX_USER + SPLIT + to_string(user_id);
}

// kaptcha:id -> string
string get_kaptcha_key(string kaptcha) {
    return PREFIX_KAPTCHA + SPLIT + kaptcha;
}