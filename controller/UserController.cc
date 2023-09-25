#include "UserController.h"
#include <jwt-cpp/jwt.h>
#include "../service/UserService.h"
#include "../model/User.h"
#include "../util/CommnityUtil.h"
using namespace std;
using namespace drogon_model::nowcoder;
using namespace trantor;

void UserController::getUser(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback)
{
    string jwt_cookie = req->getCookie("nowcoder_jwt");
    int user_id;
    Json::Value data_JSON, user_JSON;
    HttpResponsePtr response;

    try 
    {
        // 验证jwt完整性
        auto decoded = jwt::decode(jwt_cookie);
        auto verifier = jwt::verify().allow_algorithm(jwt::algorithm::hs256{JWT_SECRET});
        verifier.verify(decoded);

        // 查找用户id
        user_id = stoi(decoded.get_subject());
    }
    catch (exception e) 
    {
        // 额，不太好找这到底抛了个什么异常，不是提示的jwt::error::signature_verification_exception，全抓住好了
        LOG_INFO << "jwt验证失败，token: " << jwt_cookie;
    }

    // 生成返回响应
    if (user_id != 0)
    {
        User user = service::user::find_user_by_id(user_id);
        user_JSON["userId"] = user_id;
        user_JSON["username"] = user.getValueOfUsername();
        user_JSON["userHeaderURL"] = "defaultAvatar.jpeg";
        data_JSON["user"] = user_JSON;
        response = HttpResponse::newHttpJsonResponse(getAPIJSON(true, "已登录", data_JSON));
    }
    else
    {
        user_JSON["userId"] = 0;
        user_JSON["username"] = "";
        user_JSON["userHeaderURL"] = "defaultAvatar.jpeg";
        data_JSON["user"] = user_JSON;
        response = HttpResponse::newHttpJsonResponse(getAPIJSON(false, "未登录", data_JSON));
    }
    
    callback(response);
}
