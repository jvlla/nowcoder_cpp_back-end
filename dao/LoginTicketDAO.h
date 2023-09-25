/*
 * login_ticket表对应的数据访问对象
 */
#pragma once
#include "../model/LoginTicket.h"

namespace dao {
namespace login_ticket {
/*
 * insert into login_ticket
 * values(#{login_ticket})
 * @return 成功: 1; 失败: -1
 */
int insert_login_ticket(drogon_model::nowcoder::LoginTicket login_ticket);

/*
 * select *
 * from login_ticket 
 * where ticket = #{ticket}
 * @return 成功: 查询到的login_ticket; 失败: LoginTicket默认构造
 */
drogon_model::nowcoder::LoginTicket select_login_ticket_by_ticket(std::string ticket);

/*
 * update login_ticket 
 * set status = #{status} 
 * where ticket = #{ticket}
 * @return 成功: 更新行数; 失败: -1
 */
int update_status(std::string ticket, int status);

}
}