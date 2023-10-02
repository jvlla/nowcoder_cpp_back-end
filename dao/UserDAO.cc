#include "UserDAO.h"
#include <drogon/drogon.h>
#include <trantor/utils/Logger.h>
using namespace std;
using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::nowcoder;

Mapper<User> get_user_mapper();

namespace dao::user {

User select_by_id(int id)
{
    Mapper<User> mapper = get_user_mapper();
    future<User> select_future = mapper.findFutureByPrimaryKey(id);

    try
    {
        User user = select_future.get();
        return user;
    }
    catch(const DrogonDbException &e)
    {
        LOG_ERROR << "error when call dao::select_by_id(" << id << "): "<< e.base().what();
        return User();
    }
}

User select_by_username(std::string username)
{
    Mapper<User> mapper = get_user_mapper();
    future<vector<User>> select_future = mapper.findFutureBy(Criteria(User::Cols::_username, CompareOperator::EQ, username));

    try
    {
        vector<User> users = select_future.get();
        if (users.size() > 0)
            return users[0];
        else
            return User();
    }
    catch(const DrogonDbException &e)
    {
        LOG_ERROR << "error when call dao::select_by_username(" << username << "): "<< e.base().what();
        return User();
    }
}

User select_by_email(std::string email)
{
    Mapper<User> mapper = get_user_mapper();
    future<vector<User>> select_future = mapper.findFutureBy(Criteria(User::Cols::_email, CompareOperator::EQ, email));

    try
    {
        vector<User> users = select_future.get();
        if (users.size() > 0)
            return users[0];
        else
            return User();
    }
    catch(const DrogonDbException &e)
    {
        LOG_ERROR << "error when call dao::select_by_email(" << email << "): "<< e.base().what();
        return User();
    }
}

int insert_user(User user)
{
    Mapper<User> mapper = get_user_mapper();
    future<User> insert_future = mapper.insertFuture(user);

    try
    {
        User user = insert_future.get();
        return 1;
    }
    catch(const DrogonDbException &e)
    {
        LOG_ERROR << "error when call dao::insert_user(user): "<< e.base().what();
        return -1;
    }
}

int update_header(int user_id, std::string header_url)
{
    Mapper<User> mapper = get_user_mapper();
    future<size_t> update_future = mapper.updateFutureBy( (Json::Value::Members) {"header_url"}
        , Criteria(User::Cols::_id, CompareOperator::EQ, user_id), header_url);
    
    try
    {
        size_t count = update_future.get();
        return (int) count;
    }
    catch(const DrogonDbException &e)
    {
        LOG_ERROR << "error when call dao::update_header(" << user_id << ", " << header_url << "): "<< e.base().what();
        return -1;
    }
}

int update_status(int user_id, int status)
{
    Mapper<User> mapper = get_user_mapper();
    future<size_t> update_future = mapper.updateFutureBy( (Json::Value::Members) {"status"}
        , Criteria(User::Cols::_id, CompareOperator::EQ, user_id), status);
    
    try
    {
        size_t count = update_future.get();
        return (int) count;
    }
    catch(const DrogonDbException &e)
    {
        LOG_ERROR << "error when call dao::update_status(" << user_id << ", " << status << "): "<< e.base().what();
        return -1;
    }
}

}

Mapper<User> get_user_mapper()
{
    DbClientPtr client_ptr = app().getDbClient();
    Mapper<User> mapper(client_ptr);
    return mapper;
}
