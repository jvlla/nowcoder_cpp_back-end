#pragma once
#include <string>
#include <drogon/HttpController.h>
using namespace drogon;

namespace api_data::user {
// "api/user/captcha"接口post数据格式
struct HeaderImageData{
    std::string image_base64;
};
}

namespace drogon
{
template<> inline api_data::user::HeaderImageData fromRequest(const HttpRequest &req)
{
    auto json = req.getJsonObject();
    api_data::user::HeaderImageData data;
    if (json)
        data.image_base64 = (*json)["image"].asString();
    return data;
}
}