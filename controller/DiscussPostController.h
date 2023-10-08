/*
 * discuss_post相关控制器
 */
#pragma once
#include <drogon/HttpController.h>
#include "../util/CommunityConstant.h"
#include "../api_data/DiscussPostAPIData.h"
using namespace drogon;

class DiscussPostController : public drogon::HttpController<DiscussPostController>
{
  public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(DiscussPostController::get_discuss_posts, API_PREFIX + "/post?page={1}&limit={2}", Get);
    ADD_METHOD_TO(DiscussPostController::get_discuss_post, API_PREFIX + "/post/{1}", Get);
    ADD_METHOD_TO(DiscussPostController::add_discuss_post, API_PREFIX + "/post/add", Post, "LoginRequired");
    METHOD_LIST_END
    
    /*
     * 主页数据展示接口, url为"api/post?page={1}&limit={2}"
     * @param page 当前页号
     * @param limit 每页帖子数
     * @return
     * {
     *   "success": true/false,
     *   "message": "xxx",
     *   "data": 帖子数据,
     *   "total": 帖子总数
     * } 
     */
    void get_discuss_posts(const HttpRequestPtr& request, std::function<void (const HttpResponsePtr &)> &&callback
      , int page, int limit);

    /*
     * 获取一个帖子接口，url为"api/post/{1}"
     * @param post_id 帖子id
     * @return
     * {
     *   "success": true/false,
     *   "message": "xxx",
     *   "data": 帖子数据
     * }
     */
    void get_discuss_post(const HttpRequestPtr& request, std::function<void (const HttpResponsePtr &)> &&callback
      , int post_id);
    
    /*
     * 发帖接口，url为"api/post/add"
     * @param post_data
     * {
     *   "title": 帖子标题
     *   "content": 帖子内容
     * }
     * @return
     * {
     *   "success": true/false,
     *   "message": "xxx",
     * }
     */
    void add_discuss_post(const HttpRequestPtr& request, std::function<void (const HttpResponsePtr &)> &&callback
      , api_data::discuss_post::AddDiscussPostData post_data);
};
