/*
 * comment相关业务
 */
#pragma once
#include "../model/Comment.h"

namespace service {
namespace comment{

/*
 * 根据entity_type(帖子或评论)和entity_id(帖子id或评论id)查找评论（回复）
 * entity_type comment表中entity_type字段
 * entity_id comment表中entity_id字段
 * @param offset sql查询偏移量
 * @param limit sql查询行数限制
 * @return 评论查询结果，多个
 */
std::vector<drogon_model::nowcoder::Comment> find_comments_by_entity(int entity_type, int entity_id, int offset, int limit);

/*
 * 查找帖子总行数
 * entity_type 评论回复类型
 * entity_id 评论回复id
 * @return 回复行数
 */
int find_comment_count(int entity_type, int entity_id);

/*
 * 插入评论
 * @param comment 要添加的评论
 * @return 成功: 添加行数(1); 失败: -1
 */
int add_comment(drogon_model::nowcoder::Comment &comment);

}
}