#pragma once
#include "../model/Comment.h"

namespace dao {
namespace comment {
/*
 * select *
 * from comment
 * where status = 0
 * and entity_type = #{entityType}
 * and entity_id = #{entityId}
 * order by create_time asc
 * limit #{offset}, #{limit}
 * @return 成功: 查询到的comment; 失败: 空vector
 */
std::vector<drogon_model::nowcoder::Comment> select_comments_by_entity(int entity_type, int entity_id, int offset, int limit);

/*
 * select count(*)
 * from comment
 * where status = 0
 * and entity_type = #{entityType}
 * and entity_id = #{entityId}
 * @param 成功: 查询到的行数; 失败: -1
 */
int select_count_by_entity(int entity_type, int entity_id);

/*
 * insert into comment
 * values(#{comment})
 * @return 成功: 1; 失败: -1
 */
int insert_comment(drogon_model::nowcoder::Comment comment);
}
}