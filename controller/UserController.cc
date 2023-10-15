#include "UserController.h"
#include <fstream>
#include <jwt-cpp/jwt.h>
#include "../service/UserService.h"
#include "../service/LikeService.h"
#include "../service/FollowService.h"
#include "../dao/UserDAO.h"
#include "../model/User.h"
#include "../util/CommnityUtil.h"
using namespace std;
using namespace drogon_model::nowcoder;
using namespace trantor;

void UserController::get_user(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback)
{
    int user_id = drogon_thread_to_user_id[drogon::app().getCurrentThreadIndex()];
    Json::Value data_JSON, user_JSON;
    HttpResponsePtr response;

    // 生成返回响应
    if (user_id != 0)
    {
        User user = service::user::find_user_by_id(user_id);
        user_JSON["userId"] = user_id;
        user_JSON["username"] = user.getValueOfUsername();
        user_JSON["userHeaderURL"] = avatar_file_to_url(user.getValueOfHeaderUrl());
        data_JSON["user"] = user_JSON;
        response = HttpResponse::newHttpJsonResponse(getAPIJSON(true, "已登录", data_JSON));
    }
    else
    {
        user_JSON["userId"] = 0;
        user_JSON["username"] = "";
        user_JSON["userHeaderURL"] = avatar_file_to_url("defaultAvatar.jpg");
        data_JSON["user"] = user_JSON;
        response = HttpResponse::newHttpJsonResponse(getAPIJSON(false, "未登录", data_JSON));
    }
    
    callback(response);
}

void UserController::change_header(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback
    , api_data::user::HeaderImageData post_data)
{
    string filename, type_suffix;  // 预计写出文件名; .xxx，文件类型
    string image_decoded;  // base64解码后的图片
    ofstream image_of;  // 图片写出流
    ifstream test_if;  // 测试文件是否存在的文件输入流
    HttpResponsePtr response;

    // 通过base64编码判断文件类型
    if (post_data.image_base64.compare(0, 23, "data:image/jpeg;base64,") == 0)
    {
        type_suffix = ".jpg";
        image_decoded = drogon::utils::base64Decode(post_data.image_base64.substr(23));
    }
    else if (post_data.image_base64.compare(0, 22, "data:image/png;base64,") == 0)
    {
        type_suffix = ".png";
        image_decoded = drogon::utils::base64Decode(post_data.image_base64.substr(22));
    }
    else
    {
        // 非jpg和png图片或base64有误，返回错误
        response = HttpResponse::newHttpJsonResponse(getAPIJSON(false, "图片类型错误，仅允许jpeg和png"));
        callback(response);
        return;
    }

    // 通过打开ifstream流的方式测试文件是否凑在，并生成不存在的文件名
    do {
        filename = get_uuid_lower();
        try
        { test_if.open(AVATAR_PATH + filename + type_suffix); }
        catch (exception e) {}
    } while (test_if.good());
    test_if.close();

    // 写出图片到文件
    // 这里不太严谨，要是并发写同一个文件了怎么办？凑合了。
    try 
    {
        image_of.open(AVATAR_PATH + filename + type_suffix);
        image_of << image_decoded;
        image_of.close();
    } 
    catch (exception e)
    {
        LOG_ERROR << "failed when call change_header(), file write failed";
        response = HttpResponse::newHttpJsonResponse(getAPIJSON(false, "图片写出失败"));
        callback(response);
        return;
    }

    // 更新数据库中头像
    service::user::update_header(drogon_thread_to_user_id[app().getCurrentThreadIndex()], filename + type_suffix);
    
    response = HttpResponse::newHttpJsonResponse(getAPIJSON(true, "头像更新成功"));
    callback(response);
}

void UserController::get_profile(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback
    , int user_id)
{
    User user = service::user::find_user_by_id(user_id);
    Json::Value data_JSON, user_JSON;
    HttpResponsePtr response;

    // 生成返回响应
    if (user.getValueOfId() != 0)
    {
        user_JSON["userId"] = user_id;
        user_JSON["username"] = user.getValueOfUsername();
        user_JSON["userHeaderURL"] = avatar_file_to_url(user.getValueOfHeaderUrl());
        user_JSON["registerRecord"] = user.getValueOfCreateTime().toDbString();
        user_JSON["likeCount"] = service::like::find_user_like_count(user_id);
        user_JSON["followeeCount"] = service::follow::find_followee_count(user_id, ENTITY_TYPE_USER);
        user_JSON["followerCount"] = service::follow::find_follower_count(ENTITY_TYPE_USER, user_id);
        if (drogon_thread_to_user_id[drogon::app().getCurrentThreadIndex()] != 0)
            user_JSON["hasFollowed"] = service::follow::has_followed(drogon_thread_to_user_id[drogon::app().getCurrentThreadIndex()]
                , ENTITY_TYPE_USER, user_id);
        else
            user_JSON["hasFollowed"] = false;
        data_JSON["data"] = user_JSON;
        response = HttpResponse::newHttpJsonResponse(getAPIJSON(true, "已登录", data_JSON));
    }
    else
    {
        user_JSON["userId"] = 0;
        user_JSON["username"] = "";
        user_JSON["userHeaderURL"] = avatar_file_to_url("defaultAvatar.jpg");
        user_JSON["registerRecord"] = "";
        user_JSON["likeCount"] = 0;
        user_JSON["followeeCount"] = 0;
        user_JSON["followerCount"] = 0;
        user_JSON["hasFollowed"] = false;
        data_JSON["data"] = user_JSON;
        response = HttpResponse::newHttpJsonResponse(getAPIJSON(false, "未登录", data_JSON));
    }
    
    callback(response);
}
