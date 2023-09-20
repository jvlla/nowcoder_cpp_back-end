#pragma once
#include <json/json.h>
#include <drogon/drogon.h>

/*
 * 生成符合API格式的JSON数据
 * {
 *   "code": xxx,
 *   "message": "xxx",
 *   "data":{
 *      xxxx什么的
 *   }
 * }
 */
Json::Value getAPIJSON(int code, std::string message, Json::Value &data);

/*
 * 生成符合API格式的JSON数据
 * {
 *   "code": xxx,
 *   "message": "xxx"
 * }
 */
Json::Value getAPIJSON(int code, std::string message);

/*
 * 生成符合API格式的JSON数据
 * {
 *   "code": xxx,
 * }
 */
Json::Value getAPIJSON(int code);


/*
 * 解决跨源资源分享问题
 * 具体原理不很清除，但没有这个浏览器会有
 * Access to XMLHttpRequest at 'http://localhost:10086/post' from origin 'http://localhost:8080' 
 * has been blocked by CORS policy: No 'Access-Control-Allow-Origin' header is present on the requested resource.
 * 这种错误
 */
drogon::HttpResponsePtr addCORSHeader(drogon::HttpResponsePtr response);
