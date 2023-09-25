/*
 * discuss_post相关业务
 */
#pragma once
#include "../model/DiscussPost.h"

namespace service {
namespace discuss_post {

/*
 * 查找帖子
 * @param user_id 发帖用户id限制，为0不限制
 * @param offset sql查询偏移量
 * @param limit sql查询行数限制
 * @return 帖子查询结果，多个
 */
std::vector<drogon_model::nowcoder::DiscussPost> find_discuss_post(int user_id, int offset, int limit);

/*
 * 查找帖子总行数
 * @param user_id 发帖用户id限制，为0不限制
 * @return 帖子行数
 */
int find_discuss_post_rows(int user_id);

}
};
