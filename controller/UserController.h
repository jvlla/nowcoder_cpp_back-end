/*
 * user相关控制器
 */
#pragma once
#include <drogon/HttpController.h>
#include "../api_data/UserAPIData.h"
#include "../util/CommunityConstant.h"
using namespace drogon;

class UserController : public drogon::HttpController<UserController>
{
  public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(UserController::get_user, API_PREFIX + "/user", Get);
    ADD_METHOD_TO(UserController::change_header, API_PREFIX + "/user/changeHeader", Post, "LoginRequired");
    METHOD_LIST_END

    /*
     * 获取当前登录用户（如果有），url为"/api/user"
     * @return 
     * {
     *   "success": true/false,
     *   "message": "xxx",
     *   "user":
     *   {
     *     "userId": "xxx"/"",
     *     "username": "xxx"/"",
     *     "userHeaderURL": "xxx"/""
     *   }
     * }
     */
    void get_user(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback);

    /*
     * 更新当前登录用户头像，url为"/api/user/changeHeader"
     * @param post_data
     * {
     *   "image": base64后的图片  // 额，主要是前端没弄明白，还是转base发过来吧……
     * }
     * @return 
     * {
     *   "success": true/false,
     *   "message": "xxx"
     * }
     */
    void change_header(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback
      , api_data::user::HeaderImageData post_data);
};
