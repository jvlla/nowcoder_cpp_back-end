#pragma once
#include <string>
#include <drogon/HttpController.h>
using namespace drogon;

namespace api_data::like {
// "api/user/captcha"接口post数据格式
struct LikeData{
    int entity_type;
    int entity_id;
    int entity_user_id;
};
}

namespace drogon
{
template<> inline api_data::like::LikeData fromRequest(const HttpRequest &req)
{
    auto json = req.getJsonObject();
    api_data::like::LikeData data;
    if (json)
    {
        data.entity_type = (*json)["entityType"].asInt();
        data.entity_id = (*json)["entityId"].asInt();
        data.entity_user_id = (*json)["entityUserId"].asInt();
    }
        
    return data;
}
}