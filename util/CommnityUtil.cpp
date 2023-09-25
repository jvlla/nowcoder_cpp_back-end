#include "CommnityUtil.h"
using namespace std;

Json::Value getAPIJSON(bool success, std::string message, Json::Value &data)
{
    Json::Value ret;

    ret["success"] = success;
    ret["message"] = message;
    // 遍历传入json data，将其中的值放入API json中
    for (string const &id: data.getMemberNames()) {
        ret[id] = data.get(id, "");
    }

    return ret;
}

Json::Value getAPIJSON(bool success, std::string message)
{
    Json::Value ret;

    ret["success"] = success;
    ret["message"] = message;
    return ret;
}

Json::Value getAPIJSON(bool success)
{
    Json::Value ret;
    ret["success"] = success;
    return ret;
}
