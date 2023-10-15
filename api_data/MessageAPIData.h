#pragma once
#include <string>
#include <drogon/HttpController.h>
using namespace drogon;

namespace api_data::message {
// "api/user/captcha"接口post数据格式
struct AddMessageData{
    int to_id;
    std::string content;
};
}

namespace drogon
{
template<> inline api_data::message::AddMessageData fromRequest(const HttpRequest &req)
{
    auto json = req.getJsonObject();
    api_data::message::AddMessageData data;
    if (json)
    {
        data.to_id = (*json)["toId"].asInt();
        data.content = (*json)["content"].asString();
    }
        
    return data;
}
}
