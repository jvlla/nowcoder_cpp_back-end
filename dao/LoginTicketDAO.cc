#include "LoginTicketDAO.h"
#include <drogon/drogon.h>
#include <trantor/utils/Logger.h>
#include "../model/LoginTicket.h"
using namespace std;
using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::nowcoder;

Mapper<LoginTicket> get_login_ticket_mapper();

namespace dao::login_ticket {

int insert_login_ticket(drogon_model::nowcoder::LoginTicket login_ticket)
{
    Mapper<LoginTicket> mapper = get_login_ticket_mapper();
    future<LoginTicket> insert_future = mapper.insertFuture(login_ticket);

    try
    {
        LoginTicket ticket = insert_future.get();
        return 1;
    }
    catch(const DrogonDbException &e)
    {
        LOG_ERROR << "error when call dao::insert_login_ticket(login_ticket): "<< e.base().what();
        return -1;
    }
}

drogon_model::nowcoder::LoginTicket select_login_ticket_by_ticket(std::string ticket)
{
    Mapper<LoginTicket> mapper = get_login_ticket_mapper();
    future<vector<LoginTicket>> select_future = mapper.findFutureBy(Criteria(LoginTicket::Cols::_ticket, CompareOperator::EQ, ticket));

    try
    {
        vector<LoginTicket> tickets = select_future.get();
        if (!tickets.empty())
            return tickets[0];
        else
            return LoginTicket();
    }
    catch(const DrogonDbException &e)
    {
        LOG_ERROR << "error when call dao::select_login_ticket_by_ticket(" << ticket << "): "<< e.base().what();
        LoginTicket ret;
        ret.setExpired(trantor::Date(0));  // 设置避免超时
        return LoginTicket();
    }
}

int update_status(std::string ticket, int status)
{
    Mapper<LoginTicket> mapper = get_login_ticket_mapper();
    // include/json/value.h:198:  using Members = std::vector<String>;
    future<size_t> update_future = mapper.updateFutureBy((Json::Value::Members) {"status"}
        , Criteria(LoginTicket::Cols::_ticket, CompareOperator::EQ, ticket), status);
    
    try
    {
        size_t count = update_future.get();
        return (int) count;
    }
    catch(const DrogonDbException &e)
    {
        LOG_ERROR << "error when call dao::select_login_ticket_by_ticket(" << ticket << "): "<< e.base().what();
        return -1;
    }
}

}

Mapper<LoginTicket> get_login_ticket_mapper()
{
    DbClientPtr client_ptr = app().getDbClient();
    Mapper<LoginTicket> mapper(client_ptr);
    return mapper;
}
