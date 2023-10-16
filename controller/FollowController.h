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

    /*
     * 关注接口，url为"api/follow"
     * @param post_data
     * {
     *   "entity_type": 被关注实体类型
     *   "entity_id": 被关注实体id
     * }
     * @return
     * {
     *   "success": true/false,
     *   "message": "xxx",
     * }
     */
    void follow(const HttpRequestPtr& request, std::function<void (const HttpResponsePtr &)> &&callback
        , api_data::like::LikeData post_data);
    
    /*
     * 取关接口，url为"api/unfollow"
     * @param post_data
     * {
     *   "entity_type": 被关注实体类型
     *   "entity_id": 被关注实体id
     * }
     * @return
     * {
     *   "success": true/false,
     *   "message": "xxx",
     * }
     */
    void unfollow(const HttpRequestPtr& request, std::function<void (const HttpResponsePtr &)> &&callback
        , api_data::like::LikeData post_data);
    
    /*
     * 用户所关注的用户展示接口，url为"api/followees/{1}?page={2}&limit={3}"
     * @param user_id 用户id
     * @param page 当前页号
     * @param limit 每页数量限制
     */
    void get_followees(const HttpRequestPtr& request, std::function<void (const HttpResponsePtr &)> &&callback
      , int user_id, int page, int limit);

    /*
     * 用户粉丝展示接口，url为"api/followers/{1}?page={2}&limit={3}"
     * @param user_id 用户id
     * @param page 当前页号
     * @param limit 每页数量限制
     */
    void get_followers(const HttpRequestPtr& request, std::function<void (const HttpResponsePtr &)> &&callback
      , int user_id, int page, int limit);
};
