#pragma once
#include <drogon/HttpController.h>
using namespace drogon;

class DiscussPostController : public drogon::HttpController<DiscussPostController>
{
  public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(DiscussPostController::get_discuss_post, "/post?page={1}&limit={2}", Get);
    METHOD_LIST_END
    
    void get_discuss_post(const HttpRequestPtr& request, std::function<void (const HttpResponsePtr &)> &&callback
      , int page, int limit);
};
