#include <climits>
#include "CommentController.h"
#include "../service/CommentService.h"
#include "../service/UserService.h"
#include "../service/LikeService.h"
#include "../model/Comment.h"
#include "../util/CommnityUtil.h"
#include "../util/CommunityConstant.h"
using namespace std;
using namespace drogon_model::nowcoder;

void CommentController::get_comments(const HttpRequestPtr& request
    , std::function<void (const HttpResponsePtr &)> &&callback, int post_id, int page, int limit)
{
    // offset和limit有默认限制
    int offset = page > 0 ? (page - 1) * 10 : 0;
    limit = limit < 10 || limit > 100 ? 10 : limit;
    vector<Comment> comments = service::comment::find_comments_by_entity(ENTITY_TYPE_POST, post_id, offset, limit);
    Json::Value data_JSON, comments_JSON;

    // 遍历查询commet结果，获取更详细数据
    for (int i = 0; i < comments.size(); ++i)
    {
        Json::Value comment_JSON, replys_JSON;
        User comment_user = service::user::find_user_by_id(comments[i].getValueOfUserId());
        vector<Comment> replys = service::comment::find_comments_by_entity(ENTITY_TYPE_COMMENT, comments[i].getValueOfId(), 0, INT_MAX);
        
        // 遍历添加replay回复相关内容
        for (int j = 0; j < replys.size(); ++j) 
        {
            Json::Value reply_JSON;
            User reply_user = service::user::find_user_by_id(replys[j].getValueOfUserId());

            reply_JSON["replyId"] = replys[j].getValueOfId();  // reply本身的id
            reply_JSON["commentId"] = comments[i].getValueOfId();  // reply回复的comment的id，因为回复reply的reply的entity_id还是comment的id
            reply_JSON["userId"] = reply_user.getValueOfId();  // 发表reply的用户id,因为回复reply的reply的target_id是这个
            reply_JSON["username"] = reply_user.getValueOfUsername();  // 发表reply的用户名
            reply_JSON["replyUsername"] = replys[j].getValueOfTargetId() == 0   // reply回复的用户名（如果有）
                ? "" : service::user::find_user_by_id(replys[j].getValueOfTargetId()).getValueOfUsername();
            reply_JSON["content"] = replys[j].getValueOfContent();
            reply_JSON["replyRecord"] = replys[j].getValueOfCreateTime().toDbStringLocal();
            reply_JSON["likeRawStatus"] = service::like::find_entity_like_status(
                drogon_thread_to_user_id[drogon::app().getCurrentThreadIndex()], ENTITY_TYPE_COMMENT, replys[j].getValueOfId());
            reply_JSON["likeRawCount"] = service::like::find_entity_like_count(ENTITY_TYPE_COMMENT, replys[j].getValueOfId());

            replys_JSON[j] = reply_JSON;
        }
        // 当回复json非空时将其插入评论json中
        if (!replys_JSON.empty())
            comment_JSON["replys"] = replys_JSON;
        else
            comment_JSON["replys"] = Json::arrayValue;

        // 添加comment评论相关内容
        comment_JSON["commentId"] = comments[i].getValueOfId();
        comment_JSON["userId"] = comments[i].getValueOfUserId();
        comment_JSON["username"] = comment_user.getValueOfUsername();
        comment_JSON["userHeaderURL"] = avatar_file_to_url(comment_user.getValueOfHeaderUrl());
        comment_JSON["content"] = comments[i].getValueOfContent();
        comment_JSON["commentRecord"] = comments[i].getValueOfCreateTime().toDbStringLocal();
        comment_JSON["likeRawStatus"] = service::like::find_entity_like_status(
            drogon_thread_to_user_id[drogon::app().getCurrentThreadIndex()], ENTITY_TYPE_COMMENT, comments[i].getValueOfId());
        comment_JSON["likeRawCount"] = service::like::find_entity_like_count(ENTITY_TYPE_COMMENT, comments[i].getValueOfId());
        comments_JSON[i] = comment_JSON;
    }
    // 评论数据
    if (!comments_JSON.empty())
        data_JSON["data"] = comments_JSON;
    else
        data_JSON["data"] = Json::arrayValue;
    
    // 评论总数
    data_JSON["total"] = service::comment::find_comment_count(ENTITY_TYPE_POST, post_id);

    HttpResponsePtr response = HttpResponse::newHttpJsonResponse(getAPIJSON(true, "帖子回复详情", data_JSON));
    callback(response);    
}

void CommentController::add_comment(const HttpRequestPtr& request, std::function<void (const HttpResponsePtr &)> &&callback
    , api_data::comment::AddCommentData post_data)
{
    Comment comment;
    HttpResponsePtr response;

    comment.setUserId(drogon_thread_to_user_id[drogon::app().getCurrentThreadIndex()]);
    comment.setEntityType(post_data.entity_type);
    comment.setEntityId(post_data.entity_id);
    comment.setTargetId(post_data.target_id);
    comment.setContent(post_data.content);
    comment.setStatus(0);
    comment.setCreateTime(trantor::Date::now());

    int ret = service::comment::add_comment(comment);
    if (ret == 1)
        response = HttpResponse::newHttpJsonResponse(getAPIJSON(true, "发帖成功"));
    else
        response = HttpResponse::newHttpJsonResponse(getAPIJSON(false, "发帖失败"));
    
    callback(response);
}
