/*
 * jwt更新拦截器
 */
#include <drogon/drogon.h>
#include <jwt-cpp/jwt.h>
#include "../util/CommnityUtil.h"
#include "../util/CommunityConstant.h"

/*
 * jwt cookie更新Post-Handling拦截器
 */
void jwt_update(const drogon::HttpRequestPtr &req, const drogon::HttpResponsePtr &res)
{
    std::string jwt_cookie = req->getCookie("nowcoder_jwt");
    long long renew_seconds = 0, expire_seconds = 0;  // jwt 中更新时间和过期时间秒数
    long long curr_secondes;  // 当前时间秒数

    // 重新解码，确实不好利用之前的解码结果
    try 
    {
        // 验证jwt完整性
        auto decoded = jwt::decode(jwt_cookie);
        auto verifier = jwt::verify().allow_algorithm(jwt::algorithm::hs256{JWT_SECRET});
        verifier.verify(decoded);

        Json::Value tokens;
        Json::Reader reader;
        reader.parse(decoded.get_payload(), tokens);
        expire_seconds = std::stoll(tokens["tmo"].asString());  // jwt cookie存的时候就没找到函数直接存数字，字符串再变数字好了
        renew_seconds = std::stoll(tokens["ext"].asString());
    }
    catch (std::exception e) 
    {
        // LOG_INFO << "jwt验证失败，token: " << jwt_cookie;  不老写日志了，这个不对太正常了，不登录都对不了
    }
    curr_secondes = trantor::Date::now().secondsSinceEpoch();

    if (renew_seconds == 0) {
        // 如果更新秒数为0，即jwt cookie不存在或解析出错
        if (jwt_cookie == "")
        {
            // 如果jwt_cookie为空，即没有，可以直接返回
        }
        else
        {
            // 如果jwt_cookie不为空，即cookie内容出错，清空cookie
            LOG_INFO << "错误的jwt cookie: " + jwt_cookie;
            res->addHeader("Set-Cookie", COOKIE_KEY_JWT + "=; Path=/; Max-Age=0"); 
        }
    }
    else if (curr_secondes >= renew_seconds && curr_secondes < expire_seconds) 
    {
        // 如果当前时间处于续期和过期时间中间，对jwt续期重写
        LOG_INFO << "对jwt续期重写，原续期时间为" + trantor::Date(renew_seconds * 1'000'000).toDbString()
            + "，到期时间为" + trantor::Date(expire_seconds * 1'000'000).toDbString();
        
        std::string token = jwt::create()
            .set_subject(std::to_string(drogon_thread_to_user_id[drogon::app().getCurrentThreadIndex()]))
            .set_payload_claim("tmo", jwt::claim(std::to_string(trantor::Date::now().after(REMEMBER_EXPIRED_SECONDS).secondsSinceEpoch())))  
            // 在ext时间后延长过期时间
            .set_payload_claim("ext", jwt::claim(std::to_string(trantor::Date::now().after(REMEMBER_EXPIRED_SECONDS * 0.8).secondsSinceEpoch())))  
            .set_type("JWS")
            .sign(jwt::algorithm::hs256{JWT_SECRET});
        res->addHeader("Set-Cookie", COOKIE_KEY_JWT + "=" + token + "; Expires=Fri, 31 Dec 9999 23:59:59 GMT; Path=/");    
    } 
    else if (curr_secondes >= expire_seconds)
    {
        // 当前时间大于jwt过期时间，删除
        LOG_INFO << "jwt过期删除，原到期时间为" + trantor::Date(expire_seconds * 1'000'000).toDbString();
        res->addHeader("Set-Cookie", COOKIE_KEY_JWT + "=; Path=/; Max-Age=0"); 
    }
}
