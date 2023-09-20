#include "DiscussPostService.h"
#include <drogon/drogon.h>
#include "../dao/DiscussPostDAO.h"
using namespace std;
using namespace drogon_model::nowcoder;
using namespace dao;

namespace service {

vector<DiscussPost> find_discuss_post(int userId, int offset, int limit)
{
    return select_discuss_post(userId, offset, limit);
}

int find_discuss_post_rows(int user_id)
{
    return select_discuss_post_rows(user_id);
}

}


