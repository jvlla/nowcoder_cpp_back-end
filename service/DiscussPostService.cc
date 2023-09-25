#include "DiscussPostService.h"
#include <drogon/drogon.h>
#include "../dao/DiscussPostDAO.h"
using namespace std;
using namespace drogon_model::nowcoder;

namespace service::discuss_post {

vector<DiscussPost> find_discuss_post(int user_id, int offset, int limit)
{
    return dao::discuss_post::select_discuss_post(user_id, offset, limit);
}

int find_discuss_post_rows(int user_id)
{
    return dao::discuss_post::select_discuss_post_rows(user_id);
}

}
