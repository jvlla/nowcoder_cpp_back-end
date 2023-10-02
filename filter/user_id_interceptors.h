/*
 * 用户user_id相关拦截器
 */
#include <drogon/drogon.h>
#include <jwt-cpp/jwt.h>
#include "../util/CommnityUtil.h"
#include "../util/CommunityConstant.h"

/*
 * user_id获取Pre-Handling拦截器
 */
void get_user_id(const drogon::HttpRequestPtr & req)
{
    std::string jwt_cookie = req->getCookie("nowcoder_jwt");
    int user_id = 0;
    long long expire_seconds = 0;

    try 
    {
        // 验证jwt完整性
        auto decoded = jwt::decode(jwt_cookie);
        auto verifier = jwt::verify().allow_algorithm(jwt::algorithm::hs256{JWT_SECRET});
        verifier.verify(decoded);

        // 查找用户id
        user_id = stoi(decoded.get_subject());
        // 查找过期时间
        Json::Value tokens;
        Json::Reader reader;
        reader.parse(decoded.get_payload(), tokens);
        expire_seconds = std::stoll(tokens["tmo"].asString());
    }
    catch (std::exception e) 
    {
        // LOG_INFO << "jwt验证失败，token: " << jwt_cookie;  不老写日志了，这个不对太正常了，不登录都对不了
    }

    // 在过期时间之前才可以获得用户id
    if (trantor::Date::now().secondsSinceEpoch() < expire_seconds)
        drogon_thread_to_user_id[drogon::app().getCurrentThreadIndex()] = user_id;
}

/*
 * user_id清除Post-Handling拦截器
 */
void remove_user_id(const drogon::HttpRequestPtr &, const drogon::HttpResponsePtr &)
{
    drogon_thread_to_user_id.erase(drogon::app().getCurrentThreadIndex());
}