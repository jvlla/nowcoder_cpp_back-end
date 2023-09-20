#include "DiscussPostDAO.h"
#include <drogon/drogon.h>
#include <trantor/utils/Logger.h>
#include "../model/DiscussPost.h"
using namespace std;
using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::nowcoder;

Mapper<DiscussPost> get_discuss_post_mapper();

namespace dao {

vector<DiscussPost> select_discuss_post(int user_id, int offset, int limit)
{
    Mapper<DiscussPost> mapper = get_discuss_post_mapper();
    future<vector<DiscussPost>> select_future;

    if (user_id == 0)
        select_future = mapper.orderBy(DiscussPost::Cols::_type, SortOrder::DESC).orderBy(DiscussPost::Cols::_create_time, SortOrder::DESC).offset(offset).limit(limit)
            .findFutureBy(Criteria(DiscussPost::Cols::_status, CompareOperator::NE, 2));
    else
        select_future = mapper.orderBy(DiscussPost::Cols::_type, SortOrder::DESC).orderBy(DiscussPost::Cols::_create_time, SortOrder::DESC).offset(offset).limit(limit)
            .findFutureBy(Criteria(DiscussPost::Cols::_status, CompareOperator::NE, 2) 
                && Criteria(DiscussPost::Cols::_user_id, CompareOperator::EQ, user_id));
    try
    {
        vector<DiscussPost> posts = select_future.get();
        for (int i = 0; i < posts.size(); ++i) {
            cout << posts[i].getValueOfId() << " " << posts[i].getValueOfTitle() << endl;
        }
        return posts;
    }
    catch(const DrogonDbException &e)
    {
        LOG_ERROR << "error when call dao::find_discuss_post(" << user_id << ", " << offset << ", " << limit << "): "
            << e.base().what();
        return {};
    }
}

int select_discuss_post_rows(int user_id)
{
    Mapper<DiscussPost> mapper = get_discuss_post_mapper();
    future<size_t> count_future;

    if (user_id == 0)
        count_future = mapper.countFuture(Criteria(DiscussPost::Cols::_status, CompareOperator::NE, 2));
    else
        count_future = mapper.countFuture(Criteria(DiscussPost::Cols::_status, CompareOperator::NE, 2)
            && Criteria(DiscussPost::Cols::_user_id, CompareOperator::EQ, user_id));
    
    try
    {
        int count = count_future.get();
        return count;
    }
    catch(const DrogonDbException &e)
    {
        LOG_ERROR << "error when call dao::select_discuss_post_rows(" << user_id << "): "<< e.base().what();
        return -1;
    }
}

int insert_discuss_post(DiscussPost discuss_post)
{
    Mapper<DiscussPost> mapper = get_discuss_post_mapper();
    future<DiscussPost> insert_future = mapper.insertFuture(discuss_post);

    try
    {
        DiscussPost discuss_post = insert_future.get();
        return 1;
    }
    catch(const DrogonDbException &e)
    {
        LOG_ERROR << "error when call dao::insert_discuss_post(discuss_post): "<< e.base().what();
        return -1;
    }
}

DiscussPost select_discuss_post_by_id(int id)
{
    Mapper<DiscussPost> mapper = get_discuss_post_mapper();
    future<DiscussPost> select_future = mapper.findFutureByPrimaryKey(id);

    try
    {
        DiscussPost discuss_post = select_future.get();
        return discuss_post;
    }
    catch(const DrogonDbException &e)
    {
        LOG_ERROR << "error when call dao::select_discuss_post_by_id(" << id << "): "<< e.base().what();
        return DiscussPost();
    }
}

// 不知道传什么参数，先不弄呢
// int update_comment_count(int id, int comment_count)
// {
//     Mapper<DiscussPost> mapper = get_discuss_post_mapper();
//     Json::Value
//     future<DiscussPost> update_future = mapper.updateFutureBy( json()
//         , Criteria(DiscussPost::Cols::_id, CompareOperator::EQ, id), comment_count);

// }



}

Mapper<DiscussPost> get_discuss_post_mapper()
{
    DbClientPtr client_ptr = app().getDbClient();
    Mapper<DiscussPost> mapper(client_ptr);
    return mapper;
}
