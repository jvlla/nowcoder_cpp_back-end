#include "UserService.h"
#include <drogon/drogon.h>
#include "../dao/UserDAO.h"
#include "../dao/LoginTicketDAO.h"
#include "../model/User.h"
#include "../model/LoginTicket.h"
#include "../util/CommunityConstant.h"
#include "../util/CommnityUtil.h"
#include "../util/RedisKeyUtil.h"
#include "../plugin/SMTPMail.h"
using namespace std;
using namespace drogon;
using namespace drogon::nosql;
using namespace drogon_model::nowcoder;

// 1.优先从缓存中取值
User get_cache(int user_id);
// 2.取不到时初始化缓存数据
User init_cache(int user_id);
// 3.数据变更时清除缓存数据
void clear_cache(int user_id);

namespace service::user {

User find_user_by_id(int id) 
{
    User user = get_cache(id);
    if (user.getValueOfId() == 0) {
        user = init_cache(id);
    }

    return user;
}

drogon_model::nowcoder::User find_user_by_name(std::string username)
{
    return dao::user::select_by_username(username);
}

bool login(string username, string password, User &user, string &error_message)
{
    user = service::user::find_user_by_name(username);

    // 空值处理
    if (username.empty()) {
        error_message = "用户名不能为空";
        return false;
    }
    if (password.empty()) {
        error_message = "密码不能为空";
        return false;
    }

    // 验证账号
    if (user.getValueOfId() == 0) {
        error_message = "用户不存在";
        return false;
    }
    // 验证状态
    if (user.getValueOfStatus() == 0) {
        error_message = "账号未激活";
        return false;
    }
    // 验证密码
    if (user.getValueOfPassword() != get_md5_lower(password + user.getValueOfSalt())) {
        error_message = "密码错误";
        return false;
    }

    // 使用JWT技术，不需要服务端存储登录凭证，直接返回
    return true;
}

bool enroll(std::string username, std::string password, std::string email, std::string &error_message)
{
    // 空值处理
    if (username.empty()) 
    {
        error_message = "用户名不能为空";
        return false;
    }
    if (password.empty()) 
    {
        error_message = "密码不能为空";
        return false;
    }
    if (email.empty()) 
    {
        error_message = "邮箱不能为空";
        return false;
    }

    // 验证账号
    if (dao::user::select_by_username(username).getValueOfId() != 0) 
    {
        error_message = "用户名已存在";
        return false;
    }
    // 验证邮箱
    if (dao::user::select_by_email(username).getValueOfId() != 0) 
    {
        error_message = "邮箱已被注册";
        return false;
    }

    // 注册用户
    User user;
    user.setUsername(username);
    user.setSalt(get_uuid_lower().substr(0, 5));
    user.setPassword(get_md5_lower(password + user.getValueOfSalt()));
    user.setEmail(email);
    user.setType(0);
    user.setStatus(0);
    user.setActivationCode(utils::getUuid());
    user.setHeaderUrl("defaultAvatar.jpg");
    user.setCreateTime(trantor::Date::now());
    dao::user::insert_user(user);
    user = dao::user::select_by_username(username);

    // 发送激活邮件
    string site = "http://" + drogon::app().getListeners()[0].toIpPort();
    string url = site + API_PREFIX + "/activation/" + to_string(user.getValueOfId()) + "/" + user.getValueOfActivationCode();
    string content = "<p>您正在注册牛客网, 这是一封激活邮件, 请点击" \
        "<a href=\"" + url + "\">链接</a>激活您的牛客账号</p>";

    auto *smtpmailPtr = app().getPlugin<SMTPMail>();
    auto id = smtpmailPtr->sendEmail(
        "smtp.126.com",               //The server IP/DNS
        25,                           //The port
        "naitoahel@126.com",          //Who send the email
        email,                        //Send to whom
        "C++版牛客注册邮件",          //Email Subject/Title
        content,                      //Content
        "naitoahel@126.com",          //Login user
        "SSHPCWJSBYAIKCIX",           //User password
        true                          //Is HTML content
    );

    return true;
}

bool activation(int user_id, std::string code, std::string &error_message)
{
    User user = dao::user::select_by_id(user_id);
    
    if (user.getValueOfStatus() == 1) 
    {
        error_message = "重复激活";
        return false;
    }
    if (user.getValueOfActivationCode() == code) 
    {
        dao::user::update_status(user.getValueOfId(), 1);
        clear_cache(user_id);
        return true;
    } 
    else 
        return false;
}

int update_header(int user_id, std::string header_url)
{
    int rows = dao::user::update_header(user_id, header_url);
    clear_cache(user_id);
    
    return rows;
}

}

// 1.优先从缓存中取值
User get_cache(int user_id)
{
    RedisClientPtr redis_client = app().getRedisClient();
    string user_key = get_user_key(user_id);
    string user_json_str;
    User user;

    try {
        user_json_str = redis_client->execCommandSync<string>(
            [](const RedisResult &r){
                if (r.type() != RedisResultType::kNil)
                    return r.asString();
                else
                    return string("");
            },
            "GET " + user_key
        );
    } catch (const exception &e) { LOG_ERROR << "error when get_cache()" << e.what(); }
    
    // 从redis内容中base64解码得到user信息
    user_json_str = utils::base64Decode(user_json_str);
    try 
    {
        // 解析user信息到user对象
        Json::Value user_json;
        Json::Reader reader;
        reader.parse(user_json_str, user_json);
        user = User(user_json);
    }
    catch (std::exception e) {}

    return user;
}

// 2.取不到时初始化缓存数据
User init_cache(int user_id) 
{
    RedisClientPtr redis_client = app().getRedisClient();
    User user = dao::user::select_by_id(user_id);
    string user_key = get_user_key(user_id);
    string user_json_str = utils::base64Encode(user.toJson().toStyledString());  // base64编码后才能符合redis的要求

    try {
        redis_client->execCommandSync<string>(
            [](const RedisResult &r) { return ""; }
            , "SET " + user_key + " " + user_json_str + " EX 3600"
        );
    } catch (const exception &e) { LOG_ERROR << "error when init_cache()" << e.what(); }

    return user;
}

// 3.数据变更时清除缓存数据
void clear_cache(int user_id) 
{
    RedisClientPtr redis_client = app().getRedisClient();
    string user_key = get_user_key(user_id);

    try {
        redis_client->execCommandSync<string>(
            [](const RedisResult &r) { return ""; }
            , "DEL " + user_key
        );
    } catch (const exception &e) { LOG_ERROR << "clear_cache()" << e.what(); }
}
