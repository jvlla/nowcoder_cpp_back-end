/*
 * 点赞相关业务
 */
#pragma once

namespace service {
namespace like{

/*
 * 点赞(如果已点，取消)
 * @param user_id 点赞用户id
 * @param entity_type 被点赞实体类型
 * @param entity_id 被点赞实体id
 * @param entity_user_id 发表实体的用户id(或当实体为用户时，就是该用户id)
 */
void like(int user_id, int entity_type, int entity_id, int entity_user_id);

/*
 * 查找对由entity_type, entity_id表示的实体的点赞数
 * @param entity_type 被点赞的实体类型
 * @param entity_id 被点赞的实体id
 */
int find_entity_like_count(int entity_type, int entity_id);

/*
 * 查询某人对某实体的点赞状态
 * @param user_id 用户id
 * @param entity_type 实体类型
 * @param entity_id 实体id
 * @return 已赞: 1; 未赞: 0
 */
int find_entity_like_status(int user_id, int entity_type, int entity_id);

/*
 * 查询某个用户获得的赞的数量
 * @param user_id 用户id
 */
int find_user_like_count(int user_id);

}
}