#pragma once
#include <vector>
#include "../model/User.h"

namespace service {
namespace follow{

void follow(int user_id, int entity_type, int entity_id);

void unfollow(int user_id, int entity_type, int entity_id);

// 查询关注的实体的数量
int find_followee_count(int user_id, int entity_type);

// 查询实体的粉丝的数量
int find_follower_count(int entity_type, int entity_id);

// 查询当前用户是否已关注该实体
bool has_followed(int user_id, int entity_type, int entity_id);

// 查询某用户关注的人
std::vector<std::pair<drogon_model::nowcoder::User, long long>> find_followees(int user_id, int offset, int limit);

// 查询关注某用户的人
std::vector<std::pair<drogon_model::nowcoder::User, long long>> find_followers(int user_id, int offset, int limit);

}
}