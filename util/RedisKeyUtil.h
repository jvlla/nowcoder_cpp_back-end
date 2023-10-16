#include <string>

/*
 * redis key, 记录对实体点赞的用户id
 * like:entity:entityType:entityId -> set(userId)
 */
std::string get_entity_like_key(int entity_type, int entity_id);

/*
 * redis key, 记录对用户点赞的数量
 * like:user:userId -> int
 */
std::string get_user_like_key(int user_id);

/*
 * redis key, 记录用户关注的实体id和关注时间
 * followee:userId:entityType -> zset(entityId,now)
 */
std::string get_followee_key(int user_id, int entity_type);

/*
 * redis key, 记录关注用户的粉丝id和关注时间
 * follower:entityType:entityId -> zset(userId,now)
 */
std::string get_follower_key(int entity_type, int entity_id);

/*
 * redis key, 记录user_id对应用户信息
 * user:user_id -> string
 */
std::string get_user_key(int user_id);

/*
 * redis key, 记录验证码cookie信息，值为"1"
 * kaptcha:id -> string
 */
std::string get_kaptcha_key(std::string kaptcha);