/*
 * user表对应的数据访问对象
 */
#pragma once
#include "../model/User.h"

namespace dao {
namespace user {

/*
 * select *
 * from user
 * where id = #{id}
 * @return 成功: 查询到的user; 失败: User默认构造
 */
drogon_model::nowcoder::User select_by_id(int id);

/*
 * select *
 * from user
 * where username = #{username}
 * @return 成功: 查询到的user; 失败: User默认构造
 */
drogon_model::nowcoder::User select_by_username(std::string username);

/*
 * select *
 * from user
 * where email = #{email}
 * @return 成功: 查询到的user; 失败: User默认构造
 */
drogon_model::nowcoder::User select_by_email(std::string email);

/*
 * insert into user
 * values(#{user})
 * @return 成功: 1; 失败: -1
 */
int insert_user(drogon_model::nowcoder::User user);

/*
 * update user
 * set header_url = #{header_url}
 * where id = #{id}
 * @return 成功: 更新行数; 失败: -1
 */
int update_header(int user_id, std::string header_url);

/*
 * update user
 * set status = #{status}
 * where id = #{id}
 * @return 成功: 更新行数; 失败: -1
 */
int update_status(int user_id, int status);

}
}
