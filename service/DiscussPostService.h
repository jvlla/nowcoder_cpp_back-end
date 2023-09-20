#pragma once
#include "../model/DiscussPost.h"

namespace service {

std::vector<drogon_model::nowcoder::DiscussPost> find_discuss_post(int userId, int offset, int limit);
int find_discuss_post_rows(int user_id);

};
