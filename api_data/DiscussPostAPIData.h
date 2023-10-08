#pragma once
#include <string>
#include <drogon/HttpController.h>
using namespace drogon;

namespace api_data::discuss_post {
// "api/user/captcha"接口post数据格式
struct AddDiscussPostData{
    std::string title;
    std::string content;
};
}

namespace drogon
{
template<> inline api_data::discuss_post::AddDiscussPostData fromRequest(const HttpRequest &req)
{
    auto json = req.getJsonObject();
    api_data::discuss_post::AddDiscussPostData data;
    if (json)
    {
        data.title = (*json)["title"].asString();
        data.content = (*json)["content"].asString();
    }
        
    return data;
}
}