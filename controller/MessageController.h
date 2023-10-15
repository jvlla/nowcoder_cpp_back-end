#pragma once
#include <drogon/HttpController.h>
#include "../api_data/MessageAPIData.h"
#include "../util/CommunityConstant.h"
using namespace drogon;

class MessageController : public drogon::HttpController<MessageController>
{
  public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(MessageController::get_letters, API_PREFIX + "/letter", Get, "LoginRequired");
    ADD_METHOD_TO(MessageController::get_letters_detail, API_PREFIX + "/letter/detail/{1}?page={2}&limit={3}", Get, "LoginRequired");
    ADD_METHOD_TO(MessageController::add_letter, API_PREFIX + "/letter/add", Post, "LoginRequired");
    ADD_METHOD_TO(MessageController::get_notices, API_PREFIX + "/notice", Get, "LoginRequired");
    ADD_METHOD_TO(MessageController::get_notices_detail, API_PREFIX + "/notice/detail/{1}?page={2}&limit={3}", Get, "LoginRequired");
    METHOD_LIST_END

    /*
     * 私信会话页展示接口，url为"api/letter"
     */
    void get_letters(const HttpRequestPtr& request, std::function<void (const HttpResponsePtr &)> &&callback);

    /*
     * 私信详情页展示接口，url为"api/letter/detail/{1}?page={2}&limit={3}"
     * @param conversation_id 会话号
     * @param page 当前页号
     * @param limit 每页私信数
     */
    void get_letters_detail(const HttpRequestPtr& request, std::function<void (const HttpResponsePtr &)> &&callback
      , std::string conversation_id, int page, int limit);
    
    /*
     * @param post_data
     * {
     *   "to_id": 私信发送目标用户id,
     *   "content": 私信内容
     * }
     * @return
     * {
     *   "success": true/false,
     *   "message": "xxx",
     * }
     */
    void add_letter(const HttpRequestPtr& request, std::function<void (const HttpResponsePtr &)> &&callback
      , api_data::message::AddMessageData post_data);
    
    /*
     * 系统通知页展示接口，url为"api/notice"
     */
    void get_notices(const HttpRequestPtr& request, std::function<void (const HttpResponsePtr &)> &&callback);

    /*
     * 系统通知详情页展示接口，url为"api/notice/detail/{1}?page={2}&limit={3}"
     * @param topic 通知类型
     * @param page 当前页号
     * @param limit 每页私信数
     */
    void get_notices_detail(const HttpRequestPtr& request, std::function<void (const HttpResponsePtr &)> &&callback
      , std::string topic, int page, int limit);
};
