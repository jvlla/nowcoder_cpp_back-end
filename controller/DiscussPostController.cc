#include "DiscussPostController.h"
#include "../service/DiscussPostService.h"
#include "../service/UserService.h"
#include "../model/DiscussPost.h"
#include "../model/User.h"
#include "../util/CommnityUtil.h"
using namespace std;
using namespace drogon_model::nowcoder;

void DiscussPostController::get_discuss_post(const HttpRequestPtr& request
    , std::function<void (const HttpResponsePtr &)> &&callback, int page, int limit)
{
    // page和limit有默认限制
    page = page > 0 ? (page - 1) * 10 : 0;
    limit = limit < 10 || limit > 100 ? 10 : limit;
    vector<DiscussPost> posts = service::discuss_post::find_discuss_post(0, page, limit);
    Json::Value dataJSON, postsJSON;

    // 遍历查询discuss_post结果，获取更详细数据
    for (int i = 0; i < posts.size(); ++i)
    {
        // 关联查询获得user
        User user = service::user::find_user_by_id(stoi(posts[i].getValueOfUserId()));  // 不改变牛客提供sql中数据类型varchar(45)，类型转换
        
        Json::Value postJSON;
        postJSON["username"] = user.getValueOfUsername();
        postJSON["userHeaderURL"] = "http://" + drogon::app().getListeners()[0].toIpPort() + "/avatar/" + user.getValueOfHeaderUrl();
        postJSON["title"] = posts[i].getValueOfTitle();
        postJSON["content"] = posts[i].getValueOfContent();
        postJSON["postRecord"] = posts[i].getValueOfCreateTime().toDbStringLocal();
        postJSON["commentCount"] = posts[i].getValueOfCommentCount();
        postJSON["likeCount"] = i;  // 点赞用redis,之后再搞

        postsJSON[i] = postJSON;
    }
    // 帖子数据
    dataJSON["data"] = postsJSON;
    // 帖子总数
    dataJSON["total"] = service::discuss_post::find_discuss_post_rows(0);

    HttpResponsePtr response = HttpResponse::newHttpJsonResponse(getAPIJSON(true, "测试帖子", dataJSON));
    callback(response);
}
