#include "UserService.h"
#include <drogon/drogon.h>
#include "../dao/UserDAO.h"
#include "../dao/LoginTicketDAO.h"
#include "../model/User.h"
#include "../model/LoginTicket.h"
#include "../util/CommunityConstant.h"
#include "../util/CommnityUtil.h"
#include "../plugin/SMTPMail.h"
using namespace std;
using namespace drogon;
using namespace drogon_model::nowcoder;

namespace service::user {

User find_user_by_id(int id) 
{
    return dao::user::select_by_id(id);
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
        return true;
    } 
    else 
        return false;
}

int update_header(int user_id, std::string header_url)
{
    return dao::user::update_header(user_id, header_url);
}

}
