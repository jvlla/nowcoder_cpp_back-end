#include "DiscussPostService.h"
#include <drogon/drogon.h>
#include "../dao/DiscussPostDAO.h"
#include "../util/CommnityUtil.h"
using namespace std;
using namespace drogon_model::nowcoder;

namespace service::discuss_post {

vector<DiscussPost> find_discuss_post(int user_id, int offset, int limit)
{
    return dao::discuss_post::select_discuss_post(user_id, offset, limit);
}

drogon_model::nowcoder::DiscussPost find_discuss_post_by_id(int discuss_post_id)
{
    return dao::discuss_post::select_discuss_post_by_id(discuss_post_id);
}

int find_discuss_post_rows(int user_id)
{
    return dao::discuss_post::select_discuss_post_rows(user_id);
}

int add_discuss_post(DiscussPost &post)
{
    post.setTitle(escape_html(post.getValueOfTitle()));
    post.setContent(escape_html(post.getValueOfContent()));
    
    return dao::discuss_post::insert_discuss_post(post);
}

int update_comment_count(int id, int comment_count)
{
    return dao::discuss_post::update_comment_count(id, comment_count);
}

}
