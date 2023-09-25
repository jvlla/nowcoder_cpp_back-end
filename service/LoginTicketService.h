/*
 * login_ticket相关业务
 */
#pragma once
#include "../model/LoginTicket.h"

namespace service {
namespace login_ticket {

/*
 * 添加登录凭证（尽管实际只用于captcha凭证，且之后会被redis替代）
 * @param ticket 要添加的login_ticket
 * @return 成功: 添加行数(1); 失败: -1
 */
int add_login_ticket(drogon_model::nowcoder::LoginTicket ticket);

/*
 * 根据ticket查找登录凭证
 * @param ticket login_ticket表中ticket字段
 * @return 成功: 查询到的login_ticket; 失败: LoginTicket默认构造
 */
drogon_model::nowcoder::LoginTicket find_login_ticket_by_ticket(std::string ticket);

}
}