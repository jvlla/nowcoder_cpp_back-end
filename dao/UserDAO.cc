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

}

Mapper<User> get_user_mapper()
{
    DbClientPtr client_ptr = app().getDbClient();
    Mapper<User> mapper(client_ptr);
    return mapper;
}
