#include "LoginTicketService.h"
#include "../dao/LoginTicketDAO.h"

namespace service::login_ticket {

int add_login_ticket(drogon_model::nowcoder::LoginTicket ticket)
{
    return dao::login_ticket::insert_login_ticket(ticket);
}

drogon_model::nowcoder::LoginTicket find_login_ticket_by_ticket(std::string ticket)
{
    return dao::login_ticket::select_login_ticket_by_ticket(ticket);
}

}