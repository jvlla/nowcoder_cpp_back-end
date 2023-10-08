#include "CommentDAO.h"
#include <drogon/drogon.h>
#include <trantor/utils/Logger.h>
using namespace std;
using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::nowcoder;

Mapper<Comment> get_comment_mapper();

namespace dao::comment {

vector<Comment> select_comments_by_entity(int entity_type, int entity_id, int offset, int limit)
{
    Mapper<Comment> mapper = get_comment_mapper();
    future<vector<Comment>> select_future = mapper.orderBy(Comment::Cols::_create_time, SortOrder::ASC).offset(offset).limit(limit)
            .findFutureBy(Criteria(Comment::Cols::_status, CompareOperator::EQ, 0)
                && Criteria(Comment::Cols::_entity_type, CompareOperator::EQ, entity_type) 
                && Criteria(Comment::Cols::_entity_id, CompareOperator::EQ, entity_id));

    try
    {
        vector<Comment> comments = select_future.get();
        return comments;
    }
    catch(const DrogonDbException &e)
    {
        LOG_ERROR << "error when call dao::select_comments_by_entity(" << entity_type << ", " << entity_id 
            << ", " << offset << ", " << limit << "): "<< e.base().what();
        return {};
    }
}

int select_count_by_entity(int entity_type, int entity_id)
{
    Mapper<Comment> mapper = get_comment_mapper();
    future<size_t> count_future;

    count_future = mapper.countFuture(Criteria(Comment::Cols::_status, CompareOperator::EQ, 0)
                && Criteria(Comment::Cols::_entity_type, CompareOperator::EQ, entity_type) 
                && Criteria(Comment::Cols::_entity_id, CompareOperator::EQ, entity_id));
    
    try
    {
        int count = count_future.get();
        return count;
    }
    catch(const DrogonDbException &e)
    {
        LOG_ERROR << "error when call dao::select_count_by_entity(" << entity_type << ", " << entity_id << "): "<< e.base().what();
        return -1;
    }
}

int insert_comment(Comment comment)
{
    Mapper<Comment> mapper = get_comment_mapper();
    future<Comment> insert_future = mapper.insertFuture(comment);

    try
    {
        Comment comment = insert_future.get();
        return 1;
    }
    catch(const DrogonDbException &e)
    {
        LOG_ERROR << "error when call dao::insert_comment(comment): "<< e.base().what();
        return -1;
    }
}

}

Mapper<Comment> get_comment_mapper()
{
    DbClientPtr client_ptr = app().getDbClient();
    Mapper<Comment> mapper(client_ptr);
    return mapper;
}