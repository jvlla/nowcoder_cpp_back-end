/*
 * discuss_post表对应的数据访问对象
 */
#pragma once
#include "../model/DiscussPost.h"
namespace dao {
namespace discuss_post {

/*
 * select * from discuss_post
 * where status != 2
 * and user_id = #{userId}
 * order by type desc, create_time desc
 * @param user_id 为0不作为查询条件
 * @return 成功: 查询到的discuss_post; 失败: 空vector
 */
std::vector<drogon_model::nowcoder::DiscussPost> select_discuss_post(int user_id, int offset, int limit);

/*
 * select count(id)
 * from discuss_post
 * where status != 2
 * and user_id = #{userId}
 * @param user_id 为0不作为查询条件
 * @return 成功: 查询到的行数; 失败: -1
 */
int select_discuss_post_rows(int userId);

/*
 * insert into discuss_post
 * values(#{discuss_post})
 * @return 成功: 1; 失败: -1
 */
int insert_discuss_post(drogon_model::nowcoder::DiscussPost discuss_post);

/*
 * select *
 * from discuss_post
 * where id = #{id}
 * @return 成功: 查询到的discuss_post; 失败: DiscussPost默认构造
 */
drogon_model::nowcoder::DiscussPost select_discuss_post_by_id(int id);

/*
 * update discuss_post 
 * set comment_count = #{comment_count} 
 * where id = #{id}
 * @return 成功: 更新行数; 失败: -1
 */
int update_comment_count(int id, int comment_count);

}
}
