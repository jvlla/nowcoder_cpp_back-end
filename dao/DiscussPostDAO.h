#pragma once
#include "../model/DiscussPost.h"

namespace dao {
/*
 * select * from discuss_post
 * where status != 2
 * and user_id = #{userId}
 * order by type desc, create_time desc
 * @param user_id 为0不作为查询条件
 */
std::vector<drogon_model::nowcoder::DiscussPost> select_discuss_post(int user_id, int offset, int limit);

/*
 * select count(id)
 * from discuss_post
 * where status != 2
 * and user_id = #{userId}
 * @param user_id 为0不作为查询条件
 */
int select_discuss_post_rows(int userId);

/*
 * insert into discuss_post
 * values(#{discuss_post})
 */
int insert_discuss_post(drogon_model::nowcoder::DiscussPost discuss_post);

/*
 * select *
 * from discuss_post
 * where id = #{id}
 */
drogon_model::nowcoder::DiscussPost select_discuss_post_by_id(int id);

/*
 * update discuss_post 
 * set comment_count = #{comment_count} 
 * where id = #{id}
 */
int update_comment_count(int id, int comment_count);

}
