/*
 * login相关控制器
 */
#pragma once
#include <drogon/HttpController.h>
#include "../api_data/LoginAPIData.h"
#include "../util/CommunityConstant.h"
using namespace drogon;

class LoginController : public drogon::HttpController<LoginController>
{
public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(LoginController::verifyCaptcha, API_PREFIX + "/login/captcha", Post);
    ADD_METHOD_TO(LoginController::login, API_PREFIX + "/login", Post);
    METHOD_LIST_END

    /*
     * 验证谷歌reCaptcha v2是否判断使用者为人接口，url为"api/user/captcha"
     * @param post_data 格式为
     * {
     *   "ticket": "xxx"
     * }
     * @return 
     * {
     *   "success": true/false,
     *   "message": ""
     * }
     * 如果成功，同时设置Cookie，key为nowcoder_captcha
     */
    void verifyCaptcha(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback
        , api_data::login::CaptchaData post_data);

    /*
     * 登录，url为"api/login"
     * @param post_data 格式为
     * {
     *   "username": "xxx",
     *   "password": "xxx"
     * }
     * @return
     * {
     *   "status": true/false,
     *   "message": "xxx"
     * }
     * 如果成功，同时设置Cookie，key为nowcoder_jwt
     */
    void login(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback
        , api_data::login::LoginData post_data);
};
