#include "MessageService.h"
#include "../dao/MessageDAO.h"
#include "../util/CommnityUtil.h"
using namespace std;
using namespace drogon_model::nowcoder;

namespace service::message {

vector<Message> find_conversations(int user_id, int offset, int limit) {
    return dao::message::select_conversations(user_id, offset, limit);
}

int find_conversation_count(int user_id) {
    return dao::message::select_conversation_count(user_id);
}

vector<Message> find_letters(string conversation_id, int offset, int limit) {
    return dao::message::select_letters(conversation_id, offset, limit);
}

int find_letter_count(string conversation_id) {
    return dao::message::select_letter_count(conversation_id);
}

int find_letter_unread_count(int user_id, string conversation_id) {
    return dao::message::select_letter_unread_count(user_id, conversation_id);
}

int add_message(Message message) {
    message.setContent(escape_html(message.getValueOfContent()));
    return dao::message::insert_message(message);
}

int read_message(vector<int> ids) {
    return dao::message::update_status(ids, 1);
}

}