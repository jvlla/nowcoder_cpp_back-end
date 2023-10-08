#pragma once
#include <drogon/HttpController.h>
#include "../util/CommunityConstant.h"
#include "../api_data/CommentAPIData.h"
using namespace drogon;

class CommentController : public drogon::HttpController<CommentController>
{
  public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(CommentController::get_comments, API_PREFIX + "/comment/{1}?page={2}&lillmit={3}", Get);
    ADD_METHOD_TO(CommentController::add_comment, API_PREFIX + "/comment/add", Post, "LoginRequired");
    METHOD_LIST_END

    /*
     * 帖子详情页评论展示接口，url为"api/comment/{1}?page={2}&lillmit={3}"
     * @param post_id 评论所评论的帖子id
     * @param page 当前页号
     * @param limit 每页评论数
     * @return
     * {
     *   "success": true/false,
     *   "message": "xxx",
     *   "data": 评论数据
     *   {
     *     "xxx": xx,
     *     "replys": 回复数据
     *   }
     *   "total": 评论综述
     * }
     */
    void get_comments(const HttpRequestPtr& request, std::function<void (const HttpResponsePtr &)> &&callback
        , int post_id, int page, int limit);
    
    /*
     * 回复接口，url为"api/comment/add"
     * @param post_data
     * {
     *   "content": 回复内容,
     *   "entity_type": 所回复的评论的类型（帖子或评论）
     *   "entity_id": 所回复的对象的id
     *   "target_id": 所回复的评论的发表用户（如果是回复给post或comment而不是reply，为0）
     * }
     * @return
     * {
     *   "success": true/false,
     *   "message": "xxx",
     * }
     */
    void add_comment(const HttpRequestPtr& request, std::function<void (const HttpResponsePtr &)> &&callback
        , api_data::comment::AddCommentData post_data);
};
