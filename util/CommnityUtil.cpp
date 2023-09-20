#include "CommnityUtil.h"

Json::Value getAPIJSON(int code, std::string message, Json::Value &data)
{
    Json::Value ret;

    ret["code"] = code;
    ret["message"] = message;
    ret["data"] = data;
    return ret;
}

Json::Value getAPIJSON(int code, std::string message)
{
    Json::Value ret;

    ret["code"] = code;
    ret["message"] = message;
    return ret;
}

Json::Value getAPIJSON(int code)
{
    Json::Value ret;
    ret["code"] = code;
    return ret;
}

drogon::HttpResponsePtr addCORSHeader(drogon::HttpResponsePtr response)
{
    response->addHeader("Access-Control-Allow-Origin", "http://localhost:8080");
    response->addHeader("Access-Control-Allow-Credentials", "true");
    return response;
}
