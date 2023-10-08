#include "CommnityUtil.h"
using namespace std;

std::unordered_map<int, int> drogon_thread_to_user_id;

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

std::string avatar_file_to_url(const std::string &filename)
{
    return "http://" + drogon::app().getListeners()[0].toIpPort() + "/avatar/" + filename;
}

string escape_html(const string &raw) {
    string result = "";
    for (char c : raw) {
        switch (c) {
            case '<':
                result += "&lt;";
                break;
            case '>':
                result += "&gt;";
                break;
            case '"':
                result += "&quot;";
                break;
            case '&':
                result += "&amp;";
                break;
            default:
                result += c;
                break;
        }
    }
    return result;
}

std::string get_md5_lower(const std::string &str)
{
    string md5 = drogon::utils::getMd5(str);
    transform(md5.begin(), md5.end(), md5.begin(), ::tolower);
    
    return md5;
}

std::string get_uuid_lower()
{
    string uuid = drogon::utils::getUuid();
    transform(uuid.begin(), uuid.end(), uuid.begin(), ::tolower);

    return uuid;
}