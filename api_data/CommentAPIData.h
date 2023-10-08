#pragma once
#include <string>
#include <drogon/HttpController.h>
using namespace drogon;

namespace api_data::comment {
// "api/user/captcha"接口post数据格式
struct AddCommentData{
    std::string content;
    int entity_type;
    int entity_id;
    int target_id;
};
}

namespace drogon
{
template<> inline api_data::comment::AddCommentData fromRequest(const HttpRequest &req)
{
    auto json = req.getJsonObject();
    api_data::comment::AddCommentData data;
    if (json)
    {
        data.content = (*json)["content"].asString();
        data.entity_type = (*json)["entityType"].asInt();
        data.entity_id = (*json)["entityId"].asInt();
        data.target_id = (*json)["targetId"].asInt();
    }
        
    return data;
}
}