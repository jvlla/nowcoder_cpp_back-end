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
    ADD_METHOD_TO(LoginController::enroll, API_PREFIX + "/register", Post);
    ADD_METHOD_TO(LoginController::activation, API_PREFIX + "/activation/{1}/{2}", Get);
    ADD_METHOD_TO(LoginController::verify_captcha, API_PREFIX + "/login/captcha", Post);
    ADD_METHOD_TO(LoginController::login, API_PREFIX + "/login", Post);
    ADD_METHOD_TO(LoginController::logout, API_PREFIX + "/logout", Get);
    METHOD_LIST_END

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
    
    /*
     * 验证谷歌reCaptcha v2是否判断使用者为人接口，url为"api/user/captcha"
     * @param post_data
     * {
     *   "ticket": "xxx"
     * }
     * @return 
     * {
     *   "success": true/false,
     *   "message": "xxx"
     * }
     * 如果成功，同时设置Cookie，key为nowcoder_captcha
     */
    void verify_captcha(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback
        , api_data::login::CaptchaData post_data);
    
    /*
     * 登出，url为"api/logout"
     * @return 删除key为nowcoder_jwt的Cookie
     */
    void logout(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback);

    /*
     * 注册，url为"api/register"（名字叫register会出错，所以叫enroll）
     * @param post_data
     * {
     *   "username": "xxx",
     *   "password": "xxx",
     *   "rememberMe": true/false
     * }
     * @return 
     * {
     *   "success": true/false,
     *   "message": "xxx"
     * }
     * 如果成功，同时设置发送激活邮件
     */
    void enroll(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback
        , api_data::login::RegisterData post_data);

    /*
     * 激活账号，url为“/activation/{1}/{2}"
     * @param user_id 激活账号id
     * @param code 账号激活码
     * @return 直接返回网页，显示激活成功或失败
     */
    void activation(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback
        , int user_id, std::string code);
};
