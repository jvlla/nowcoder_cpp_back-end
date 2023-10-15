#include "FollowController.h"
#include "../service/UserService.h"
#include "../service/FollowService.h"
#include "../dao/UserDAO.h"
#include "../util/CommnityUtil.h"
using namespace drogon;
using namespace std;
using namespace drogon_model::nowcoder;
using namespace trantor;

void FollowController::follow(const HttpRequestPtr& request, std::function<void (const HttpResponsePtr &)> &&callback
    , api_data::like::LikeData post_data)
{
    User user = service::user::find_user_by_id(drogon_thread_to_user_id[drogon::app().getCurrentThreadIndex()]);

    service::follow::follow(user.getValueOfId(), post_data.entity_type, post_data.entity_id);
    HttpResponsePtr response = HttpResponse::newHttpJsonResponse(getAPIJSON(true, "关注成功"));
    callback(response);
}

void FollowController::unfollow(const HttpRequestPtr& request, std::function<void (const HttpResponsePtr &)> &&callback
    , api_data::like::LikeData post_data)
{
    User user = service::user::find_user_by_id(drogon_thread_to_user_id[drogon::app().getCurrentThreadIndex()]);
    
    service::follow::unfollow(user.getValueOfId(), post_data.entity_type, post_data.entity_id);
    HttpResponsePtr response = HttpResponse::newHttpJsonResponse(getAPIJSON(true, "取关成功"));
    callback(response);
}

void FollowController::get_followees(const HttpRequestPtr& request, std::function<void (const HttpResponsePtr &)> &&callback
    , int user_id, int page, int limit)
{
    int offset = page > 0 ? (page - 1) * 10 : 0;
    limit = limit < 10 || limit > 100 ? 10 : limit;
    vector<pair<User, long long>> users_times = service::follow::find_followees(user_id, offset, limit);
    Json::Value data_JSON, followees_JSON;

    for (int i = 0; i < users_times.size(); i++)
    {
        Json::Value followee_JSON;

        followee_JSON["userId"] = users_times[i].first.getValueOfId();
        followee_JSON["username"] = users_times[i].first.getValueOfUsername();
        followee_JSON["userHeaderURL"] = avatar_file_to_url(users_times[i].first.getValueOfHeaderUrl());
        followee_JSON["followRecord"] = trantor::Date(users_times[i].second * 1'000'000).toDbString();
        followee_JSON["hasFollowed"] = service::follow::has_followed(
            drogon_thread_to_user_id[drogon::app().getCurrentThreadIndex()], ENTITY_TYPE_USER, users_times[i].first.getValueOfId());
        followees_JSON[i] = followee_JSON;
    }
    if (!followees_JSON.empty())
        data_JSON["data"] = followees_JSON;
    else
        data_JSON["data"] = Json::arrayValue;
    // 用户总数
    data_JSON["total"] = service::follow::find_followee_count(user_id, ENTITY_TYPE_USER);

    HttpResponsePtr response = HttpResponse::newHttpJsonResponse(getAPIJSON(true, "他关注的人", data_JSON));
    callback(response);
}

void FollowController::get_followers(const HttpRequestPtr& request, std::function<void (const HttpResponsePtr &)> &&callback
    , int user_id, int page, int limit)
{
    int offset = page > 0 ? (page - 1) * 10 : 0;
    limit = limit < 10 || limit > 100 ? 10 : limit;
    vector<pair<User, long long>> users_times = service::follow::find_followers(user_id, offset, limit);
    Json::Value data_JSON, followers_JSON;

    for (int i = 0; i < users_times.size(); i++)
    {
        Json::Value follower_JSON;

        follower_JSON["userId"] = users_times[i].first.getValueOfId();
        follower_JSON["username"] = users_times[i].first.getValueOfUsername();
        follower_JSON["userHeaderURL"] = avatar_file_to_url(users_times[i].first.getValueOfHeaderUrl());
        follower_JSON["followRecord"] = trantor::Date(users_times[i].second * 1'000'000).toDbString();
        follower_JSON["hasFollowed"] = service::follow::has_followed(
            drogon_thread_to_user_id[drogon::app().getCurrentThreadIndex()], ENTITY_TYPE_USER, users_times[i].first.getValueOfId());
        followers_JSON[i] = follower_JSON;
    }
    if (!followers_JSON.empty())
        data_JSON["data"] = followers_JSON;
    else
        data_JSON["data"] = Json::arrayValue;
    // 用户总数
    data_JSON["total"] = service::follow::find_follower_count(user_id, ENTITY_TYPE_USER);

    HttpResponsePtr response = HttpResponse::newHttpJsonResponse(getAPIJSON(true, "关注他的人", data_JSON));
    callback(response);
}