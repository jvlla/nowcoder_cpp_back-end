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
