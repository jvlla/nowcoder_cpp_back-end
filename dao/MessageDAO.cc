#include "DiscussPostDAO.h"
#include <drogon/drogon.h>
#include <trantor/utils/Logger.h>
#include "../model/Message.h"
using namespace std;
using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::nowcoder;

Mapper<Message> get_message_mapper();

namespace dao::message {

std::vector<drogon_model::nowcoder::Message> select_conversations(int user_id, int offset, int limit)
{
    Mapper<Message> mapper = get_message_mapper();
    future<vector<Message>> select_future = mapper.orderBy(Message::Cols::_id, SortOrder::DESC).offset(offset).limit(limit)
        .findFutureBy(Criteria(
            "id in ( "
                "select max(id) from message "
                "where status != 2 "
                "and from_id != 1 "
                "and (from_id = $? or to_id = $?) "
                "group by conversation_id "
            ")"_sql
        , user_id, user_id)
    );

    try
    {
        vector<Message> messages = select_future.get();
        return messages;
    }
    catch(const DrogonDbException &e)
    {
        LOG_ERROR << "error when call dao::select_conversations(" << user_id << ", " << offset << ", " << limit << "): "
            << e.base().what();
        return {};
    }
}

int select_conversation_count(int user_id)
{
    DbClientPtr client_ptr = app().getDbClient();
    string sql = "select count(m.maxid) from ( "
            "select max(id) as maxid from message "
            "where status != 2 "
            "and from_id != 1 "
            "and (from_id = " + to_string(user_id) + " or to_id = " + to_string(user_id) + ") "
            "group by conversation_id "
        ") as m ";
    future<Result> count_future = client_ptr->execSqlAsyncFuture(sql);

    try
    {
        Result result = count_future.get();
        int count = stoi(result[0][0].c_str());
        return count;
    }
    catch(const DrogonDbException &e)
    {
        LOG_ERROR << "error when call dao::select_conversation_count(" << user_id << "): "<< e.base().what();
        return -1;
    }
}

vector<Message> select_letters(string conversation_id, int offset, int limit)
{
    Mapper<Message> mapper = get_message_mapper();
    future<vector<Message>> select_future = mapper.orderBy(Message::Cols::_id, SortOrder::DESC).offset(offset).limit(limit)
        .findFutureBy(Criteria(Message::Cols::_status, CompareOperator::NE, 2) 
            && Criteria(Message::Cols::_from_id, CompareOperator::NE, 1)
            && Criteria(Message::Cols::_conversation_id, CompareOperator::EQ, conversation_id));
    
    try
    {
        vector<Message> messages = select_future.get();
        return messages;
    }
    catch(const DrogonDbException &e)
    {
        LOG_ERROR << "error when call dao::select_letters(" << conversation_id << ", " << offset << ", " << limit << "): "
            << e.base().what();
        return {};
    }
}

int select_letter_count(string conversation_id)
{
    Mapper<Message> mapper = get_message_mapper();
    future<size_t> count_future = mapper.countFuture(Criteria(Message::Cols::_status, CompareOperator::NE, 2) 
            && Criteria(Message::Cols::_from_id, CompareOperator::NE, 1)
            && Criteria(Message::Cols::_conversation_id, CompareOperator::EQ, conversation_id));
    
    try
    {
        int count = count_future.get();
        return count;
    }
    catch(const DrogonDbException &e)
    {
        LOG_ERROR << "error when call dao::select_letter_count(" << conversation_id << "): "<< e.base().what();
        return -1;
    }
}

int select_letter_unread_count(int user_id, string conversation_id)
{
    Mapper<Message> mapper = get_message_mapper();
    future<size_t> count_future;
    
    if (conversation_id != "")
        count_future= mapper.countFuture(Criteria(Message::Cols::_status, CompareOperator::EQ, 0) 
            && Criteria(Message::Cols::_from_id, CompareOperator::NE, 1)
            && Criteria(Message::Cols::_to_id, CompareOperator::EQ, user_id)
            && Criteria(Message::Cols::_conversation_id, CompareOperator::EQ, conversation_id));
    else
        count_future= mapper.countFuture(Criteria(Message::Cols::_status, CompareOperator::EQ, 0) 
            && Criteria(Message::Cols::_from_id, CompareOperator::NE, 1)
            && Criteria(Message::Cols::_to_id, CompareOperator::EQ, user_id));
    
    try
    {
        int count = count_future.get();
        return count;
    }
    catch(const DrogonDbException &e)
    {
        LOG_ERROR << "error when call dao::select_letter_unread_count(" << user_id << ", " << conversation_id << "): "
            << e.base().what();
        return -1;
    }
}

int insert_message(Message message)
{
    Mapper<Message> mapper = get_message_mapper();
    future<Message> insert_future = mapper.insertFuture(message);

    try
    {
        Message message = insert_future.get();
        return 1;
    }
    catch(const DrogonDbException &e)
    {
        LOG_ERROR << "error when call dao::insert_discuss_postinsert_message(message): "<< e.base().what();
        return -1;
    }
}

int update_status(std::vector<int> ids, int status)
{
    Mapper<Message> mapper = get_message_mapper();
    future<size_t> update_future;
    string ids_sql;

    ids_sql = "id in (";
    for (int i = 0; i < ids.size() - 1; i++) 
        ids_sql += to_string(ids[i]) + ", ";
    ids_sql += to_string(ids[ids.size() - 1]) + ")";
    update_future = mapper.updateFutureBy( (Json::Value::Members) {"status"}
        , Criteria(CustomSql(ids_sql)), status);
    try
    {
        size_t count = update_future.get();
        return (int) count;
    }
    catch(const DrogonDbException &e)
    {
        LOG_ERROR << "error when call dao::update_status(ids, " << status << "): "<< e.base().what();
        return -1;
    }
}

drogon_model::nowcoder::Message select_latest_notice(int user_id, std::string topic)
{
    Mapper<Message> mapper = get_message_mapper();
    future<vector<Message>> select_future = mapper.orderBy(Message::Cols::_id, SortOrder::DESC)
        .findFutureBy(Criteria(
            "id in ( "
                "select max(id) from message "
                "where status != 2 "
                "and from_id = 1 "
                "and to_id = $? "
                "and conversation_id = $?"
                "group by conversation_id "
            ")"_sql
        , user_id, topic)
    );

    try
    {
        vector<Message> messages = select_future.get();
        if (!messages.empty())
            return messages[0];
        else
            return Message();
    }
    catch(const DrogonDbException &e)
    {
        LOG_ERROR << "error when call dao::select_latest_notice(" << user_id << ", " << topic << "): "
            << e.base().what();
        return Message();
    }
}

int select_notice_count(int user_id, std::string topic)
{
    Mapper<Message> mapper = get_message_mapper();
    future<size_t> count_future = mapper.countFuture(Criteria(Message::Cols::_status, CompareOperator::NE, 2) 
        && Criteria(Message::Cols::_from_id, CompareOperator::EQ, 1)
        && Criteria(Message::Cols::_to_id, CompareOperator::EQ, user_id)
        && Criteria(Message::Cols::_conversation_id, CompareOperator::EQ, topic));
    
    try
    {
        int count = count_future.get();
        return count;
    }
    catch(const DrogonDbException &e)
    {
        LOG_ERROR << "error when call dao::select_notice_count(" << user_id << ", " << topic << "): "<< e.base().what();
        return -1;
    }
}

int select_notice_unread_count(int user_id, std::string topic)
{
    Mapper<Message> mapper = get_message_mapper();
    future<size_t> count_future;

    if (topic != "")
        count_future = mapper.countFuture(Criteria(Message::Cols::_status, CompareOperator::EQ, 0) 
            && Criteria(Message::Cols::_from_id, CompareOperator::EQ, 1)
            && Criteria(Message::Cols::_to_id, CompareOperator::EQ, user_id)
            && Criteria(Message::Cols::_conversation_id, CompareOperator::EQ, topic));
    else
        count_future = mapper.countFuture(Criteria(Message::Cols::_status, CompareOperator::EQ, 0) 
            && Criteria(Message::Cols::_from_id, CompareOperator::EQ, 1)
            && Criteria(Message::Cols::_to_id, CompareOperator::EQ, user_id));

    try
    {
        int count = count_future.get();
        return count;
    }
    catch(const DrogonDbException &e)
    {
        LOG_ERROR << "error when call dao::select_notice_unread_count(" << user_id << ", " << topic << "): "<< e.base().what();
        return -1;
    }
}

std::vector<drogon_model::nowcoder::Message> select_notices(int user_id, std::string topic, int offset, int limit)
{
    Mapper<Message> mapper = get_message_mapper();
    future<vector<Message>> select_future = mapper.orderBy(Message::Cols::_id, SortOrder::DESC).offset(offset).limit(limit)
        .findFutureBy(Criteria(Message::Cols::_status, CompareOperator::NE, 2) 
            && Criteria(Message::Cols::_from_id, CompareOperator::EQ, 1)
            && Criteria(Message::Cols::_to_id, CompareOperator::EQ, user_id)
            && Criteria(Message::Cols::_conversation_id, CompareOperator::EQ, topic));
    
    try
    {
        vector<Message> messages = select_future.get();
        return messages;
    }
    catch(const DrogonDbException &e)
    {
        LOG_ERROR << "error when call dao::select_notices(" << user_id << ", " << topic << ", " << offset << ", " 
            << limit << "): " << e.base().what();
        return {};
    }
}

}

Mapper<Message> get_message_mapper()
{
    DbClientPtr client_ptr = app().getDbClient();
    Mapper<Message> mapper(client_ptr);
    return mapper;
}
