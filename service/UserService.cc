#include "UserService.h"
#include <drogon/drogon.h>
#include "../dao/UserDAO.h"
using namespace std;
using namespace drogon_model::nowcoder;
using namespace dao;

namespace service {

User find_user_by_id(int id) 
{
    return select_by_id(id);
}

}
