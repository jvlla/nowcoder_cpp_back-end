#include "FollowService.h"
#include <drogon/drogon.h>
#include <trantor/utils/Logger.h>
#include "UserService.h"
#include "../model/User.h"
#include "../util/RedisKeyUtil.h"
#include "../util/CommunityConstant.h"
using namespace std;
using namespace drogon;
using namespace drogon::nosql;
using namespace drogon_model::nowcoder;

// followee是被关注的，是东西（或人）；followee:user_id:类型 里面存的是用户关注了这一类型的什么
// follower是关注者，是人；follower:类型:id 存的是这个东西被谁关注了
namespace service::follow {

void follow(int user_id, int entity_type, int entity_id) {
    RedisClientPtr redis_client = app().getRedisClient();
    string followee_key = get_followee_key(user_id, entity_type);
    string follower_key = get_follower_key(entity_type, entity_id);

    redis_client->newTransactionAsync(
        [user_id, entity_type, entity_id, followee_key, follower_key](const RedisTransactionPtr &trans_ptr) {
        
        try {
            // 不知道为什么指定模板类型为void或没有就会报错，弄个类型先用
            trans_ptr->execCommandSync<string>([](const RedisResult &r){ return ""; }
                , "ZADD " + followee_key + " %lld %d", trantor::Date::now().secondsSinceEpoch(), entity_id);
            trans_ptr->execCommandSync<string>([](const RedisResult &r){ return ""; }
                , "ZADD " + follower_key + " %lld %d", trantor::Date::now().secondsSinceEpoch(), user_id);
        } catch (const exception &e) { LOG_ERROR << "error when follow() in ZADD" << e.what(); }
        
        trans_ptr->execute(
            [](const drogon::nosql::RedisResult &r) { /* transaction worked */ },
            [](const std::exception &err) { /* transaction failed */ });
    });
}

void unfollow(int user_id, int entity_type, int entity_id) {
    RedisClientPtr redis_client = app().getRedisClient();
    string followee_key = get_followee_key(user_id, entity_type);
    string follower_key = get_follower_key(entity_type, entity_id);

    redis_client->newTransactionAsync(
        [user_id, entity_type, entity_id, followee_key, follower_key](const RedisTransactionPtr &trans_ptr) {
        
        try {
            // 不知道为什么指定模板类型为void或没有就会报错，弄个类型先用
            trans_ptr->execCommandSync<string>([](const RedisResult &r){ return ""; }
                , "ZREM " + followee_key + " %d", entity_id);
            trans_ptr->execCommandSync<string>([](const RedisResult &r){ return ""; }
                , "ZREM " + follower_key + " %d", user_id);
        } catch (const exception &e) { LOG_ERROR << "error when unfollow() in ZREM" << e.what(); }
        
        trans_ptr->execute(
            [](const drogon::nosql::RedisResult &r) { /* transaction worked */ },
            [](const std::exception &err) { /* transaction failed */ });
    });
}

int find_followee_count(int user_id, int entity_type) {
    RedisClientPtr redis_client = app().getRedisClient();
    string followee_key = get_followee_key(user_id, entity_type);
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
            "ZCARD " + followee_key
        );
    } catch (const exception &e) { LOG_ERROR << "error when find_followee_count()" << e.what(); }
    
    return ret;
}

int find_follower_count(int entity_type, int entity_id) {
    RedisClientPtr redis_client = app().getRedisClient();
    string follower_key = get_follower_key(entity_type, entity_id);
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
            "ZCARD " + follower_key
        );
    } catch (const exception &e) { LOG_ERROR << "error when find_follower_count()" << e.what(); }

    return ret;
}

bool has_followed(int user_id, int entity_type, int entity_id) {
    RedisClientPtr redis_client = app().getRedisClient();
    string followee_key = get_followee_key(user_id, entity_type);
    string ret;

    // 同步接口，自己捕获异常
    try {
        ret = redis_client->execCommandSync<string>(
            [](const RedisResult &r){
                if (r.type() != RedisResultType::kNil)
                    return r.asString();
                else
                    return string("");
            },
            "ZSCORE " + followee_key + " %d", entity_id
        );
    } catch (const exception &e) { LOG_ERROR << "error when has_followed()" << e.what(); }
    
    return ret != "";
}

vector<pair<User, long long>> find_followees(int user_id, int offset, int limit) {
    RedisClientPtr redis_client = app().getRedisClient();
    string followee_key = get_followee_key(user_id, ENTITY_TYPE_USER);
    vector<int> ids;
    vector<pair<User, long long>> ret;

    // 同步接口，自己捕获异常
    try {
        ids = redis_client->execCommandSync<vector<int>>(
            [](const RedisResult &r){
                vector<int> ids;

                if (r.type() != RedisResultType::kNil)
                {
                    vector<RedisResult> rids = r.asArray();
                    for (RedisResult rid: rids)
                        ids.push_back(stoi(rid.asString()));
                }
                return ids;
            },
            "ZREVRANGE " + followee_key + " %d %d", offset, offset + limit - 1
        );
    } catch (const exception &e) { LOG_ERROR << "error when has_followed()" << e.what(); }

    // 再通过id到数据库去详细用户信息，到redis去关注时间
    for (int id: ids)
    {
        User user = service::user::find_user_by_id(id);
        long long follow_second;

        try {
            follow_second = redis_client->execCommandSync<int>(
                [](const RedisResult &r){
                    if (r.type() != RedisResultType::kNil)
                        return stoi(r.asString());
                    else
                        return 0;
                },
                "ZSCORE " + followee_key + " %d", id
            );
        } catch (const exception &e) { LOG_ERROR << "error when has_followed()" << e.what(); }
        ret.push_back(make_pair(user, follow_second));
    }
    
    return ret;
}

vector<pair<User, long long>> find_followers(int user_id, int offset, int limit) {
    RedisClientPtr redis_client = app().getRedisClient();
    string follower_key = get_follower_key(ENTITY_TYPE_USER, user_id);
    vector<int> ids;
    vector<pair<User, long long>> ret;

    // 同步接口，自己捕获异常
    try {
        ids = redis_client->execCommandSync<vector<int>>(
            [](const RedisResult &r){
                vector<int> ids;

                if (r.type() != RedisResultType::kNil)
                {
                    vector<RedisResult> rids = r.asArray();
                    for (RedisResult rid: rids)
                        ids.push_back(stoi(rid.asString()));
                }
                return ids;
            },
            "ZREVRANGE " + follower_key + " %d %d", offset, offset + limit - 1
        );
    } catch (const exception &e) { LOG_ERROR << "error when has_followed()" << e.what(); }

    for (int id: ids)
    {
        User user = service::user::find_user_by_id(id);
        long long follow_second;

        try {
            follow_second = redis_client->execCommandSync<int>(
                [](const RedisResult &r){
                    if (r.type() != RedisResultType::kNil)
                        return stoi(r.asString());
                    else
                        return 0;
                },
                "ZSCORE " + follower_key + " %d", id
            );
        } catch (const exception &e) { LOG_ERROR << "error when has_followed()" << e.what(); }
        ret.push_back(make_pair(user, follow_second));
    }
    
    return ret;
}

}