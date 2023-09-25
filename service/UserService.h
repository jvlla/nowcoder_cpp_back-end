/*
 * user相关业务
 */
#pragma once
#include "../model/User.h"

namespace service {
namespace user{

/*
 * 根据id查找用户
 * @param id user表中id
 * @return 成功: 查询到的user; 失败: User默认构造
 */
drogon_model::nowcoder::User find_user_by_id(int id);

/*
 * 根据username查找用户
 * @param username user表中username字段
 * @return 成功: 查询到的user; 失败: User默认构造
 */
drogon_model::nowcoder::User find_user_by_name(std::string username);

/*
 * 登录，验证username和password是否正确
 * @param username 用户名
 * @param password 密码
 * @param user 所登录的用户（如果验证成功），引用传递
 * @param error_message 错误信息（如果验证失败）
 * @return 是否验证成功
 */
bool login(std::string username, std::string password, drogon_model::nowcoder::User &user, std::string &error_message);

}
}