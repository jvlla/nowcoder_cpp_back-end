#include "DiscussPostController.h"
#include "../service/DiscussPostService.h"
#include "../service/UserService.h"
#include "../model/DiscussPost.h"
#include "../model/User.h"
#include "../util/CommnityUtil.h"
using namespace std;
using namespace drogon_model::nowcoder;
using namespace service;

void DiscussPostController::get_discuss_post(const HttpRequestPtr& request
    , std::function<void (const HttpResponsePtr &)> &&callback, int page, int limit)
{
    printf("%d %d\n", page, limit);
    page = page > 0 ? (page - 1) * 10 : 0;
    limit = limit < 10 || limit > 100 ? 10 : limit;
    vector<DiscussPost> posts = find_discuss_post(0, page, limit);
    Json::Value dataJSON, postsJSON;

    for (int i = 0; i < posts.size(); ++i)
    {
        // 关联查询获得user
        User user = find_user_by_id(stoi(posts[i].getValueOfUserId()));  // 不改变牛客提供sql中数据类型varchar(45)，类型转换
        
        Json::Value postJSON;
        postJSON["username"] = user.getValueOfUsername();
        postJSON["userHeaderURL"] = "defaultAvatar.jpeg";
        postJSON["title"] = posts[i].getValueOfTitle();
        postJSON["content"] = posts[i].getValueOfContent();
        postJSON["postRecord"] = posts[i].getValueOfCreateTime().toDbStringLocal();
        postJSON["likeCount"] = i;
        postJSON["commentCount"] = (int)posts.size() - i;

        postsJSON[i] = postJSON;
    }
    dataJSON["posts"] = postsJSON;
    dataJSON["postsTotal"] = find_discuss_post_rows(0);

    HttpResponsePtr response = HttpResponse::newHttpJsonResponse(getAPIJSON(200, "测试帖子", dataJSON));
    addCORSHeader(response);
    callback(response);
}
