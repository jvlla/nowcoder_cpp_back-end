#pragma once
#include "../model/User.h"

namespace dao {

/*
 * select *
 * from user
 * where id = #{id}
 */
drogon_model::nowcoder::User select_by_id(int id);

}
