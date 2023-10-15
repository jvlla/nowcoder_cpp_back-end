#pragma once
#include <string>
#include <drogon/HttpController.h>
using namespace drogon;

namespace api_data::follow {
// "api/user/captcha"接口post数据格式
struct followData{
    int entity_type;
    int entity_id;
};
}

namespace drogon
{
template<> inline api_data::follow::followData fromRequest(const HttpRequest &req)
{
    auto json = req.getJsonObject();
    api_data::follow::followData data;
    if (json)
    {
        data.entity_type = (*json)["entityType"].asInt();
        data.entity_id = (*json)["entityId"].asInt();
    }
        
    return data;
}
}