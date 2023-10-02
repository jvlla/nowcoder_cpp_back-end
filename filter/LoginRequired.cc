/**
 *
 *  login_required.cc
 *
 */
#include "LoginRequired.h"
#include <drogon/drogon.h>
#include <jwt-cpp/jwt.h>
#include "../util/CommnityUtil.h"
#include "../util/CommunityConstant.h"
using namespace drogon;

void LoginRequired::doFilter(const HttpRequestPtr &req,
                         FilterCallback &&fcb,
                         FilterChainCallback &&fccb)
{
    std::string jwt_cookie = req->getCookie("nowcoder_jwt");
    int user_id = 0;

    // 这个和get_user_id的拦截器重复了，但是也不好把拦截器放到Post-Routing。重复就重复吧，反正禁止访问的少
    try 
    {
        // 验证jwt完整性
        auto decoded = jwt::decode(jwt_cookie);
        auto verifier = jwt::verify().allow_algorithm(jwt::algorithm::hs256{JWT_SECRET});
        verifier.verify(decoded);

        // 查找用户id
        user_id = stoi(decoded.get_subject());
    }
    catch (std::exception e) 
    {
        LOG_INFO << "访问需要登录页面被拦截，jwt验证失败，token: " << jwt_cookie;
    }

    // 处理是否拦截
    if (user_id != 0)
    {
        //Passed
        fccb();
        return;
    }

    //Check failed
    auto res = drogon::HttpResponse::newHttpResponse();
    res->setStatusCode(k403Forbidden);
    fcb(res);
}
