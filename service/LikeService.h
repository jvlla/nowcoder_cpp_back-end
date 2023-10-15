#pragma once

namespace service {
namespace like{

void like(int user_id, int entity_type, int entity_id, int entity_user_id);

int find_entity_like_count(int entity_type, int entity_id);

// 查询某人对某实体的点赞状态
int find_entity_like_status(int user_id, int entity_type, int entity_id);

// 查询某个用户获得的赞
int find_user_like_count(int user_id);

}
}