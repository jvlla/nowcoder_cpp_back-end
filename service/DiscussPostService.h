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
 * 根据id查找帖子
 * @param discuss_post_id discuss_post表中id
 * @return 成功: 查询到的discuss_post; 失败: DiscussPost默认构造
 */
drogon_model::nowcoder::DiscussPost find_discuss_post_by_id(int discuss_post_id);

/*
 * 查找帖子总行数
 * @param user_id 发帖用户id限制，为0不限制
 * @return 帖子行数
 */
int find_discuss_post_rows(int user_id);

/*
 * 插入帖子
 * @param post 要添加的post
 * @return 成功: 添加行数(1); 失败: -1
 */
int add_discuss_post(drogon_model::nowcoder::DiscussPost &post);

/*
 * 更新帖子回帖数
 * @param id 帖子id
 * @param comment_count 回帖数
 * @return 更新行数
 */
int update_comment_count(int id, int comment_count);

}
};
