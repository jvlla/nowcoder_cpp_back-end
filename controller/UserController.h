/*
 * user相关控制器
 */
#pragma once
#include <drogon/HttpController.h>
#include "../util/CommunityConstant.h"
using namespace drogon;

class UserController : public drogon::HttpController<UserController>
{
  public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(UserController::getUser, API_PREFIX + "/user", Get);
    METHOD_LIST_END

    /*
     * 获取当前登录用户（如果有），url为"/api/user"
     * @return 
     * {
     *   "success": true/false,
     *   "message": "",
     *   "user":
     *   {
     *     "userId": "xxx"/"",
     *     "username": "xxx"/"",
     *     "userHeaderURL": "xxx"/""
     *   }
     * }
     */
    void getUser(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback);
};
