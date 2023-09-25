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

}
}
