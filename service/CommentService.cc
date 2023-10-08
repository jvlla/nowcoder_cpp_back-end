#include "CommentService.h"
#include "DiscussPostService.h"
#include "../dao/CommentDAO.h"
#include "../util/CommnityUtil.h"
#include "../util/CommunityConstant.h"
using namespace std;
using namespace drogon_model::nowcoder;

namespace service::comment{

vector<Comment> find_comments_by_entity(int entity_type, int entity_id, int offset, int limit) {
    return dao::comment::select_comments_by_entity(entity_type, entity_id, offset, limit);
}

int find_comment_count(int entity_type, int entity_id) {
    return dao::comment::select_count_by_entity(entity_type, entity_id);
}

int add_comment(Comment &comment) {
    int rows_affect;

    comment.setContent(escape_html(comment.getValueOfContent()));
    rows_affect = dao::comment::insert_comment(comment);

    // 更新帖子评论数量
    if (comment.getValueOfEntityType() == ENTITY_TYPE_POST) {
        int count = dao::comment::select_count_by_entity(ENTITY_TYPE_POST, comment.getValueOfEntityId());
        service::discuss_post::update_comment_count(comment.getValueOfEntityId(), count);
    }

    return rows_affect;
}

}