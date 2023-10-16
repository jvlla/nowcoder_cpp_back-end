/*
 * 关注相关业务
 */
#pragma once
#include <vector>
#include "../model/User.h"

namespace service {
namespace follow{

/*
 * 关注实体（实际上只回关注别的用户，因此entity_type始终为ENTITY_TYPE_USER）
 * @param user_id 发起关注的用户的用户id
 * @param entity_type 被关注实体类型
 * @param entity_id 被关注实体id
 */
void follow(int user_id, int entity_type, int entity_id);

/*
 * 取关实体（实际上只回关注别的用户，因此entity_type始终为ENTITY_TYPE_USER）
 * @param user_id 发起关注的用户的用户id
 * @param entity_type 被关注实体类型
 * @param entity_id 被关注实体id
 */
void unfollow(int user_id, int entity_type, int entity_id);

/*
 * 查询用户关注的entity_type类实体的数量
 * @param user_id 进行关注的用户的id
 * @param entity_type 被关注的实体的类型
 */
int find_followee_count(int user_id, int entity_type);

/*
 * 查询实体的粉丝的数量
 * @param entity_type 实体类型
 * @param entity_id 实体id
 */
int find_follower_count(int entity_type, int entity_id);

/*
 * 查询当前用户是否已关注该实体
 * user_id 用户id
 * entity_type 实体类型
 * entity_id 实体id
 */
bool has_followed(int user_id, int entity_type, int entity_id);

/*
 * 查询某用户关注的人
 * @param user_id 用户id
 * @offset 偏移量
 * @limit 数量
 * @return 用户和关注时间(秒数)的pair组成的vector
 */
std::vector<std::pair<drogon_model::nowcoder::User, long long>> find_followees(int user_id, int offset, int limit);

/*
 * 查询关注某用户的人
 * @param user_id 用户id
 * @offset 偏移量
 * @limit 数量
 * @return 用户和关注时间(秒数)的pair组成的vector
 */
std::vector<std::pair<drogon_model::nowcoder::User, long long>> find_followers(int user_id, int offset, int limit);

}
}