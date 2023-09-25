/*
 * discuss_post相关控制器
 */
#pragma once
#include <drogon/HttpController.h>
#include "../util/CommunityConstant.h"
using namespace drogon;

class DiscussPostController : public drogon::HttpController<DiscussPostController>
{
  public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(DiscussPostController::get_discuss_post, API_PREFIX + "/post?page={1}&limit={2}", Get);
    METHOD_LIST_END
    
    /*
     * 主页数据展示接口, url为"api/post?page={1}&limit={2}"
     * @param page
     * @param limit
     * @return
     * {
     *   "success": true/false,
     *   "message": "",
     *   "data": 帖子数据,
     *   "total": 帖子总数
     * } 
     */
    void get_discuss_post(const HttpRequestPtr& request, std::function<void (const HttpResponsePtr &)> &&callback
      , int page, int limit);
};
