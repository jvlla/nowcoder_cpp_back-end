#include "LikeService.h"
#include <drogon/drogon.h>
#include "../util/RedisKeyUtil.h"
using namespace std;
using namespace drogon;
using namespace drogon::nosql;

namespace service::like {

// 点赞
void like(int user_id, int entity_type, int entity_id, int entity_user_id) {
    RedisClientPtr redis_client = app().getRedisClient();
    string entity_like_key = get_entity_like_key(entity_type, entity_id);
    string user_like_key = get_user_like_key(entity_user_id);
    bool has_liked = false;

    // 好像是因为事务一起执行，has_liked就不会改变。反正就是放在前面才正常
    try {
        has_liked = redis_client->execCommandSync<int>(
            [&has_liked](const RedisResult &r) {
                if (r.type() != RedisResultType::kNil)
                    return r.asInteger();
                else
                    return (long long) 0;
            }
            , "SISMEMBER " + entity_like_key + " %d", user_id);
    } catch (const exception &e) { LOG_ERROR << "error when like() in SISMEMBER" << e.what(); }
    
    redis_client->newTransactionAsync(
        [user_id, entity_type, entity_id, entity_user_id, entity_like_key, user_like_key, has_liked](const RedisTransactionPtr &trans_ptr) {
        
        try {
            if (has_liked)
            {
                // 不知道为什么指定模板类型为void或没有就会报错，弄个类型先用
                trans_ptr->execCommandSync<string>([](const RedisResult &r){ return ""; }
                    , "SREM " + entity_like_key + " %d", user_id);
                trans_ptr->execCommandSync<string>([](const RedisResult &r){ return ""; }
                    , "DECR " + user_like_key);
            }
            else
            {
                trans_ptr->execCommandSync<string>([](const RedisResult &r){ return ""; }
                    , "SADD " + entity_like_key + " %d", user_id);
                trans_ptr->execCommandSync<string>([](const RedisResult &r){ return ""; } 
                    , "INCR " + user_like_key);
            }
        } catch (const exception &e) { LOG_ERROR << "error when like() in SREM/SADD and DECR/INCR" << e.what(); }
        
        trans_ptr->execute(
            [](const drogon::nosql::RedisResult &r) { /* transaction worked */ },
            [](const std::exception &err) { /* transaction failed */ });
    });
}

// 查询某实体点赞的数量
int find_entity_like_count(int entity_type, int entity_id) {
    RedisClientPtr redis_client = app().getRedisClient();
    string entity_like_key = get_entity_like_key(entity_type, entity_id);
    int ret;

    // 同步接口，自己捕获异常
    try {
        ret = redis_client->execCommandSync<int>(
            [](const RedisResult &r){
                if (r.type() != RedisResultType::kNil)
                    return r.asInteger();
                else
                    return (long long) 0;
            },
            "SCARD " + entity_like_key
        );
    } catch (const exception &e) { LOG_ERROR << "error when find_entity_like_count()" << e.what(); }
    
    return ret;
}

// 查询某人对某实体的点赞状态
int find_entity_like_status(int user_id, int entity_type, int entity_id) {
    RedisClientPtr redis_client = app().getRedisClient();
    string entity_like_key = get_entity_like_key(entity_type, entity_id);
    int ret;

    try {
        ret = redis_client->execCommandSync<int>(
            [](const RedisResult &r){
                if (r.type() != RedisResultType::kNil)
                    return r.asInteger();
                else
                    return (long long) 0;
            },
            "SISMEMBER " + entity_like_key + " %d", user_id
        );
    } catch (const exception &e) { LOG_ERROR << "error when find_entity_like_count()" << e.what(); }
    
    return ret;
}

// 查询某个用户获得的赞
int find_user_like_count(int user_id) {
    RedisClientPtr redis_client = app().getRedisClient();
    string user_like_key = get_user_like_key(user_id);
    int ret;

    try {
        ret = stoi(redis_client->execCommandSync<string>(
            [](const RedisResult &r){
                if (r.type() != RedisResultType::kNil)
                    return r.asString();
                else
                    return to_string(0);
            },
            "GET " + user_like_key
        ));
    } catch (const exception &e) { LOG_ERROR << "error when find_entity_like_count()" << e.what(); }
    
    return ret;
}

}

