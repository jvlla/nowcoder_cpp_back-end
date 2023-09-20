#pragma once
#include "../model/User.h"

namespace service {

/*
 * 根据id查找用户
 * @param id user表中id
 */
drogon_model::nowcoder::User find_user_by_id(int id);

}