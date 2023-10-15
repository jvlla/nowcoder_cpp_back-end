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

    void like(const HttpRequestPtr& request, std::function<void (const HttpResponsePtr &)> &&callback
        , api_data::like::LikeData post_data);
};
