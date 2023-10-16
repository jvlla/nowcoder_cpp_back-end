#pragma once
#include <drogon/HttpController.h>
#include "../api_data/LikeAPIData.h"
#include "../util/CommunityConstant.h"
using namespace drogon;

class LikeController : public drogon::HttpController<LikeController>
{
  public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(LikeController::like, API_PREFIX + "/like", Post, "LoginRequired");
    METHOD_LIST_END

    /*
     * 点赞接口，url为"api/like"
     * @param post_data
     * {
     *   "entity_type": 被点赞实体类型
     *   "entity_id": 被点赞实体id
     *   "entity_user_id": 被点赞的实体是由哪个用户发布的，将会通知他
     *   "post_id": 实体所在帖子id
     * }
     * @return
     * {
     *   "success": true/false,
     *   "message": "xxx",
     * }
     */
    void like(const HttpRequestPtr& request, std::function<void (const HttpResponsePtr &)> &&callback
        , api_data::like::LikeData post_data);
};
