#pragma once
#include <string>
#include <drogon/HttpController.h>
using namespace drogon;

namespace api_data::login {
// "api/user/captcha"接口post数据格式
struct CaptchaData{
    std::string ticket;
};

// "api/login"接口post数据格式
struct LoginData {
    std::string username;
    std::string password;
    bool remember;
};

struct RegisterData {
    std::string username;
    std::string password;
    std::string rePassword;
    std::string email;
};
}

namespace drogon
{
template<> inline api_data::login::CaptchaData fromRequest(const HttpRequest &req)
{
    auto json = req.getJsonObject();
    api_data::login::CaptchaData data;
    if (json)
        data.ticket = (*json)["ticket"].asString();
    return data;
}

template<> inline api_data::login::LoginData fromRequest(const HttpRequest &req)
{
    auto json = req.getJsonObject();
    api_data::login::LoginData data;
    if (json) 
    {
        data.username = (*json)["username"].asString();
        data.password = (*json)["password"].asString();
        data.remember = (*json)["rememberMe"].asBool();
    }

    return data;
}

template<> inline api_data::login::RegisterData fromRequest(const HttpRequest &req)
{
    auto json = req.getJsonObject();
    api_data::login::RegisterData data;
    if (json) 
    {
        data.username = (*json)["username"].asString();
        data.password = (*json)["password"].asString();
        data.rePassword = (*json)["rePassword"].asString();
        data.email = (*json)["email"].asString();
    }

    return data;
}

}
