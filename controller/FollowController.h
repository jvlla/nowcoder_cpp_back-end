#pragma once
#include <drogon/HttpController.h>
#include "../api_data/LikeAPIData.h"
#include "../util/CommunityConstant.h"
using namespace drogon;

class FollowController : public drogon::HttpController<FollowController>
{
  public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(FollowController::follow, API_PREFIX + "/follow", Post, "LoginRequired");
    ADD_METHOD_TO(FollowController::unfollow, API_PREFIX + "/unfollow", Post, "LoginRequired");
    ADD_METHOD_TO(FollowController::get_followees, API_PREFIX + "/followees/{1}?page={2}&limit={3}", Get);
    ADD_METHOD_TO(FollowController::get_followers, API_PREFIX + "/followers/{1}?page={2}&limit={3}", Get);
    METHOD_LIST_END

    void follow(const HttpRequestPtr& request, std::function<void (const HttpResponsePtr &)> &&callback
        , api_data::like::LikeData post_data);
    
    void unfollow(const HttpRequestPtr& request, std::function<void (const HttpResponsePtr &)> &&callback
        , api_data::like::LikeData post_data);
    
    void get_followees(const HttpRequestPtr& request, std::function<void (const HttpResponsePtr &)> &&callback
      , int user_id, int page, int limit);

    void get_followers(const HttpRequestPtr& request, std::function<void (const HttpResponsePtr &)> &&callback
      , int user_id, int page, int limit);
};
