#include <climits>
#include "DiscussPostController.h"
#include "../service/DiscussPostService.h"
#include "../service/UserService.h"
#include "../model/User.h"
#include "../model/DiscussPost.h"
#include "../util/CommnityUtil.h"
using namespace std;
using namespace drogon_model::nowcoder;

void DiscussPostController::get_discuss_posts(const HttpRequestPtr& request
    , std::function<void (const HttpResponsePtr &)> &&callback, int page, int limit)
{
    // offset和limit有默认限制
    int offset = page > 0 ? (page - 1) * 10 : 0;
    limit = limit < 10 || limit > 100 ? 10 : limit;
    vector<DiscussPost> posts = service::discuss_post::find_discuss_post(0, offset, limit);
    Json::Value data_JSON, posts_JSON;

    // 遍历查询discuss_post结果，获取更详细数据
    for (int i = 0; i < posts.size(); ++i)
    {
        // 关联查询获得user
        User user = service::user::find_user_by_id(stoi(posts[i].getValueOfUserId()));  // 不改变牛客提供sql中数据类型varchar(45)，类型转换
        
        Json::Value post_JSON;
        post_JSON["username"] = user.getValueOfUsername();
        post_JSON["userHeaderURL"] = avatar_file_to_url(user.getValueOfHeaderUrl());
        post_JSON["postId"] = posts[i].getValueOfId();
        post_JSON["title"] = posts[i].getValueOfTitle();
        post_JSON["content"] = posts[i].getValueOfContent();
        post_JSON["postRecord"] = posts[i].getValueOfCreateTime().toDbStringLocal();
        post_JSON["commentCount"] = posts[i].getValueOfCommentCount();
        post_JSON["likeCount"] = i;  // 点赞用redis,之后再搞

        posts_JSON[i] = post_JSON;
    }
    // 帖子数据
    data_JSON["data"] = posts_JSON;
    // 帖子总数
    data_JSON["total"] = service::discuss_post::find_discuss_post_rows(0);

    HttpResponsePtr response = HttpResponse::newHttpJsonResponse(getAPIJSON(true, "主页帖子", data_JSON));
    callback(response);
}

void DiscussPostController::get_discuss_post(const HttpRequestPtr& request, std::function<void (const HttpResponsePtr &)> &&callback
    , int post_id)
{
    DiscussPost post = service::discuss_post::find_discuss_post_by_id(post_id);
    User user = service::user::find_user_by_id(stoi(post.getValueOfUserId()));  // 不改变牛客提供sql中数据类型varchar(45)，类型转换
    Json::Value data_JSON, post_JSON;

    // 添加discuss_post帖子相关内容
    post_JSON["postId"] = post.getValueOfId();
    post_JSON["username"] = user.getValueOfUsername();
    post_JSON["userHeaderURL"] = avatar_file_to_url(user.getValueOfHeaderUrl());
    post_JSON["title"] = post.getValueOfTitle();
    post_JSON["content"] = post.getValueOfContent();
    post_JSON["postRecord"] = post.getValueOfCreateTime().toDbStringLocal();
    post_JSON["commentCount"] = post.getValueOfCommentCount();
    post_JSON["likeCount"] = 10;  // 点赞用redis,之后再搞
    data_JSON["data"] = post_JSON;

    HttpResponsePtr response = HttpResponse::newHttpJsonResponse(getAPIJSON(true, "帖子详情", data_JSON));
    callback(response);
}

void DiscussPostController::add_discuss_post(const HttpRequestPtr& request, std::function<void (const HttpResponsePtr &)> &&callback
      , api_data::discuss_post::AddDiscussPostData post_data)
{
    DiscussPost post;
    HttpResponsePtr response;
    
    // 不用验证用户了，签名保证了jwt提供的id是正确的
    post.setUserId(to_string(drogon_thread_to_user_id[drogon::app().getCurrentThreadIndex()]));
    post.setTitle(post_data.title);
    post.setContent(post_data.content);
    post.setCreateTime(trantor::Date::now());
    post.setType(0);
    post.setStatus(0);
    post.setCommentCount(0);
    post.setScore(0);

    int ret = service::discuss_post::add_discuss_post(post);
    if (ret == 1)
        response = HttpResponse::newHttpJsonResponse(getAPIJSON(true, "回复成功"));
    else
        response = HttpResponse::newHttpJsonResponse(getAPIJSON(false, "回复失败"));
    
    callback(response);
}
