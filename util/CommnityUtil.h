/*
 * 辅助函数头文件
 */
#pragma once
#include <unordered_map>
#include <jsoncpp/json/json.h>
#include <drogon/drogon.h>

extern std::unordered_map<int, int> drogon_thread_to_user_id;

/*
 * 生成符合API格式的JSON数据
 * {
 *   "success": true/false,
 *   "message": "xxx",
 *   "xxx": 什么的
 * }
 */
Json::Value getAPIJSON(bool success, std::string message, Json::Value &data);

/*
 * 生成符合API格式的JSON数据
 * {
 *   "success": true/false,
 *   "message": "xxx"
 * }
 */
Json::Value getAPIJSON(bool success, std::string message);

/*
 * 生成符合API格式的JSON数据
 * {
 *   "success": true/false
 * }
 */
Json::Value getAPIJSON(bool success);

/*
 * 将数据库中的文件名转化为前端可以访问的URL地址
 * 额，虽然字段名叫header_url，但实际放文件名了，所以需要在转变一次，前面加上ip和路径
 * @param user表中header_url路径
 * @return ip/avatar/"filename"
 */
std::string avatar_file_to_url(const std::string &filename);

/*
 * 将<>"&进行html转义，避免sql注入
 * @param raw 原始内容
 * @return 转义后的内容
 */
std::string escape_html(const std::string &raw);

/*
 * 获得小写的md5散列值
 */
std::string get_md5_lower(const std::string &str);

/*
 * 获得小写的uuid
 */
std::string get_uuid_lower();
