#include "LikeController.h"
#include "../service/LikeService.h"
#include "../kafka/KafkaProducer.h"
#include "../util/CommnityUtil.h"

void LikeController::like(const HttpRequestPtr& request, std::function<void (const HttpResponsePtr &)> &&callback
        , api_data::like::LikeData post_data)
{
    int user_id = drogon_thread_to_user_id[drogon::app().getCurrentThreadIndex()];
    Json::Value data_JSON, like_JSON;

    service::like::like(user_id, post_data.entity_type, post_data.entity_id, post_data.entity_user_id);
    like_JSON["likeCount"] = service::like::find_entity_like_count(post_data.entity_type, post_data.entity_id);
    like_JSON["likeStatus"] = service::like::find_entity_like_status(user_id, post_data.entity_type, post_data.entity_id);
    data_JSON["data"] = like_JSON;

    // 通过kafka生产者发送点赞系统通知
    if (like_JSON["likeStatus"].asInt() == 1)
    {
        Json::Value content;
        content["entityType"] = post_data.entity_type;
        content["entityId"] = post_data.entity_id;
        content["entityUserId"] = post_data.entity_user_id;
        content["userId"] = user_id;
        content["postId"] = post_data.post_id;
        KafkaProducer::get_instance().post_message(TOPIC_LIKE, content);
    }

    HttpResponsePtr response = HttpResponse::newHttpJsonResponse(getAPIJSON(true, "点赞结果", data_JSON));
    callback(response);
}
