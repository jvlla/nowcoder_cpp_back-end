#include "UserService.h"
#include <drogon/drogon.h>
#include "../dao/UserDAO.h"
#include "../dao/LoginTicketDAO.h"
#include "../model/User.h"
#include "../model/LoginTicket.h"
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
    string password_salt_md5 = utils::getMd5(password + user.getValueOfSalt());
    transform(password_salt_md5.begin(), password_salt_md5.end(), password_salt_md5.begin(), ::tolower); // 转小写，因为自带数据为小写
    if (user.getValueOfPassword() != password_salt_md5) {
        error_message = "密码错误";
        return false;
    }

    // 使用JWT技术，不需要服务端存储登录凭证，直接返回
    return true;
}

}
