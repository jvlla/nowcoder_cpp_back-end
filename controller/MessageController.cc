#include <climits>
#include "MessageController.h"
#include "../service/MessageService.h"
#include "../service/UserService.h"
#include "../model/Message.h"
#include "../model/User.h"
#include "../util/CommnityUtil.h"
#include "../util/CommunityConstant.h"
using namespace std;
using namespace drogon_model::nowcoder;

int get_letter_to_id(string conversation_id);
vector<int> get_letter_unread_ids(const vector<Message> messages);

void MessageController::get_letters(const HttpRequestPtr& request, std::function<void (const HttpResponsePtr &)> &&callback)
{
    User user = service::user::find_user_by_id(drogon_thread_to_user_id[drogon::app().getCurrentThreadIndex()]);
    vector<Message> letters = service::message::find_conversations(user.getValueOfId(), 0, INT_MAX);  // 每组会话最后一个私信
    Json::Value data_JSON, letters_JSON;

    for (int i = 0; i < letters.size(); ++i)
    {
        int unread_count = service::message::find_letter_unread_count(
            user.getValueOfId(), letters[i].getValueOfConversationId());
        int target_id = user.getValueOfId() == letters[i].getValueOfFromId() 
            ? letters[i].getValueOfToId() : letters[i].getValueOfFromId();
        User target_user = service::user::find_user_by_id(target_id);
        
        Json::Value letter_JSON;
        letter_JSON["conversationId"] = letters[i].getValueOfConversationId();
        letter_JSON["content"] = letters[i].getValueOfContent();
        letter_JSON["targetName"] = target_user.getValueOfUsername();
        letter_JSON["targetHeaderUrl"] = avatar_file_to_url(target_user.getValueOfHeaderUrl());
        letter_JSON["letterRecord"] = letters[i].getValueOfCreateTime().toDbStringLocal();
        letter_JSON["unreadCount"] = unread_count;
        letter_JSON["total"] = service::message::find_letter_count(letters[i].getValueOfConversationId());

        letters_JSON[i] = letter_JSON;
    }
    if (!letters_JSON.empty())
        data_JSON["data"] = letters_JSON;
    else
        data_JSON["data"] = Json::arrayValue;
    data_JSON["total"] = service::message::find_conversation_count(user.getValueOfId());

    HttpResponsePtr response = HttpResponse::newHttpJsonResponse(getAPIJSON(true, "私信列表", data_JSON));
    callback(response);
}

void MessageController::get_letters_detail(const HttpRequestPtr& request, std::function<void (const HttpResponsePtr &)> &&callback
    , string conversation_id, int page, int limit)
{
    int offset = page > 0 ? (page - 1) * 10 : 0;
    limit = limit < 10 || limit > 100 ? 10 : limit;
    vector<Message> letters = service::message::find_letters(conversation_id, offset, limit);
    User user = service::user::find_user_by_id(drogon_thread_to_user_id[drogon::app().getCurrentThreadIndex()]);
    Json::Value data_JSON, letters_JSON;

    for (int i = 0; i < letters.size(); ++i)
    {
        User from_user = service::user::find_user_by_id(letters[i].getValueOfFromId());
        
        Json::Value letter_JSON;
        letter_JSON["isMe"] = from_user.getValueOfId() == user.getValueOfId();
        letter_JSON["content"] = letters[i].getValueOfContent();
        letter_JSON["userName"] = from_user.getValueOfUsername();
        letter_JSON["userHeaderUrl"] = avatar_file_to_url(from_user.getValueOfHeaderUrl());
        letter_JSON["letterRecord"] = letters[i].getValueOfCreateTime().toDbStringLocal();

        letters_JSON[i] = letter_JSON;
    }
    if (!letters_JSON.empty())
    {
        data_JSON["data"] = letters_JSON;
        data_JSON["toId"] = get_letter_to_id(letters[0].getValueOfConversationId());
    }
    else
    {
        data_JSON["data"] = Json::arrayValue;
        data_JSON["toId"] = -1;
    }
    data_JSON["total"] = service::message::find_letter_count(conversation_id);

    vector<int> unread_ids = get_letter_unread_ids(letters);
    if (!unread_ids.empty())
        service::message::read_message(unread_ids);

    HttpResponsePtr response = HttpResponse::newHttpJsonResponse(getAPIJSON(true, "私信详情", data_JSON));
    callback(response);
}

void MessageController::add_letter(const HttpRequestPtr& request, std::function<void (const HttpResponsePtr &)> &&callback
      , api_data::message::AddMessageData post_data)
{
    Message message;
    HttpResponsePtr response;

    message.setFromId(drogon_thread_to_user_id[drogon::app().getCurrentThreadIndex()]);
    message.setToId(post_data.to_id);
    if (message.getValueOfFromId() < message.getValueOfToId())
        message.setConversationId(to_string(message.getValueOfFromId()) + "_" + to_string(message.getValueOfToId()));
    else
        message.setConversationId(to_string(message.getValueOfToId()) + "_" + to_string(message.getValueOfFromId()));
    message.setContent(post_data.content);
    message.setStatus(0);
    message.setCreateTime(trantor::Date::now());

    int ret = service::message::add_message(message);
    if (ret == 1)
        response = HttpResponse::newHttpJsonResponse(getAPIJSON(true, "消息发送成功"));
    else
        response = HttpResponse::newHttpJsonResponse(getAPIJSON(false, "消息发送失败"));
    
    callback(response);
}

void MessageController::get_notices(const HttpRequestPtr& request, std::function<void (const HttpResponsePtr &)> &&callback)
{
    User user = service::user::find_user_by_id(drogon_thread_to_user_id[drogon::app().getCurrentThreadIndex()]);
    Message notice;
    Json::Value data_JSON, notices_JSON;

    notice = service::message::find_latest_notice(user.getValueOfId(), TOPIC_COMMENT);
    if (notice.getValueOfId() != 0)
    {
        Json::Value comment_JSON, content_JSON;
        Json::Reader reader;

        reader.parse(notice.getValueOfContent(), content_JSON);

        comment_JSON["type"] = TOPIC_COMMENT;
        comment_JSON["noticeRecord"] = notice.getValueOfCreateTime().toDbStringLocal();
        comment_JSON["username"] = service::user::find_user_by_id(content_JSON["userId"].asInt()).getValueOfUsername();
        comment_JSON["count"] = service::message::find_notice_count(user.getValueOfId(), TOPIC_COMMENT);
        comment_JSON["unreadCount"] = service::message::find_notice_unread_count(user.getValueOfId(), TOPIC_COMMENT);

        notices_JSON[0] = comment_JSON;
    }

    notice = service::message::find_latest_notice(user.getValueOfId(), TOPIC_LIKE);
    if (notice.getValueOfId() != 0)
    {
        Json::Value like_JSON, content_JSON;
        Json::Reader reader;

        reader.parse(notice.getValueOfContent(), content_JSON);

        like_JSON["type"] = TOPIC_LIKE;
        like_JSON["noticeRecord"] = notice.getValueOfCreateTime().toDbStringLocal();;
        like_JSON["username"] = service::user::find_user_by_id(content_JSON["userId"].asInt()).getValueOfUsername();
        like_JSON["count"] = service::message::find_notice_count(user.getValueOfId(), TOPIC_COMMENT);
        like_JSON["unreadCount"] = service::message::find_notice_unread_count(user.getValueOfId(), TOPIC_LIKE);

        notices_JSON[1] = like_JSON;
    }

    notice = service::message::find_latest_notice(user.getValueOfId(), TOPIC_FOLLOW);
    if (notice.getValueOfId() != 0)
    {
        Json::Value follow_JSON, content_JSON;
        Json::Reader reader;

        reader.parse(notice.getValueOfContent(), content_JSON);

        follow_JSON["type"] = TOPIC_FOLLOW;
        follow_JSON["noticeRecord"] = notice.getValueOfCreateTime().toDbStringLocal();;
        follow_JSON["username"] = service::user::find_user_by_id(content_JSON["userId"].asInt()).getValueOfUsername();
        follow_JSON["count"] = service::message::find_notice_count(user.getValueOfId(), TOPIC_COMMENT);
        follow_JSON["unreadCount"] = service::message::find_notice_unread_count(user.getValueOfId(), TOPIC_FOLLOW);

        notices_JSON[2] = follow_JSON;
    }

    if (!notices_JSON.empty())
        data_JSON["data"] = notices_JSON;
    else
        data_JSON["data"] = Json::arrayValue;

    HttpResponsePtr response = HttpResponse::newHttpJsonResponse(getAPIJSON(true, "通知列表", data_JSON));
    callback(response);
}

void MessageController::get_notices_detail(const HttpRequestPtr& request, std::function<void (const HttpResponsePtr &)> &&callback
    , std::string topic, int page, int limit)
{
    int offset = page > 0 ? (page - 1) * 10 : 0;
    limit = limit < 10 || limit > 100 ? 10 : limit;
    User user = service::user::find_user_by_id(drogon_thread_to_user_id[drogon::app().getCurrentThreadIndex()]);
    vector<Message> notices = service::message::find_notices(user.getValueOfId(), topic, offset, limit);
    Json::Value data_JSON, notices_JSON;

    for (int i = 0; i < notices.size(); ++i)
    {
        Json::Value notice_JSON, content_JSON;
        Json::Reader reader;

        reader.parse(notices[i].getValueOfContent(), content_JSON);

        notice_JSON["type"] = topic;
        notice_JSON["noticeRecord"] = notices[i].getValueOfCreateTime().toDbStringLocal();;
        notice_JSON["userId"] = content_JSON["userId"].asInt();
        notice_JSON["username"] = service::user::find_user_by_id(content_JSON["userId"].asInt()).getValueOfUsername();
        notice_JSON["postId"] = content_JSON["postId"];

        notices_JSON[i] = notice_JSON;
    }
    if (!notices_JSON.empty())
    {
        data_JSON["data"] = notices_JSON;
    }
    else
    {
        data_JSON["data"] = Json::arrayValue;
    }
    data_JSON["total"] = service::message::find_notice_count(user.getValueOfId(), topic);

    vector<int> unread_ids = get_letter_unread_ids(notices);
    if (!unread_ids.empty())
        service::message::read_message(unread_ids);

    HttpResponsePtr response = HttpResponse::newHttpJsonResponse(getAPIJSON(true, "私信详情", data_JSON));
    callback(response);
}


int get_letter_to_id(string conversation_id) {
    int splitPos = conversation_id.find("_", 0);
    int id_1 = stoi(conversation_id.substr(0, splitPos));
    int id_2 = stoi(conversation_id.substr(splitPos + 1));
    int user_id = drogon_thread_to_user_id[drogon::app().getCurrentThreadIndex()];

    return id_1 == user_id ? id_2 : id_1;
}

vector<int> get_letter_unread_ids(const vector<Message> messages)
{
    vector<int> ret;

    for (Message message: messages)
        if (message.getValueOfToId() == drogon_thread_to_user_id[drogon::app().getCurrentThreadIndex()] 
            && message.getValueOfStatus() == 0)
            ret.push_back(message.getValueOfId());
    return ret;
}