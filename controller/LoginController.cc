#include "LoginController.h"
#include <curl/curl.h>
#include <jwt-cpp/jwt.h>
#include <trantor/utils/Logger.h>
#include "../service/UserService.h"
#include "../service/LoginTicketService.h"
#include "../model/User.h"
#include "../model/LoginTicket.h"
#include "../util/CommnityUtil.h"
using namespace std;
using namespace drogon_model::nowcoder;
using namespace trantor;

/*
 * 向谷歌reCaptcha v2接口发送https post请求，来源见 https://blog.csdn.net/cjf_wei/article/details/79185310
 */
bool google_verify(string ticket, Json::Value &google_answer);

void LoginController::verifyCaptcha(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback
    , api_data::login::CaptchaData post_data)
{
    Json::Value google_result;
    bool is_human = google_verify(post_data.ticket, google_result);
    HttpResponsePtr response;

    if (is_human)
    {
        if (google_result.get("success", false).asBool() == true)
        {
            string captcha_ticket = drogon::utils::getUuid();
            // 写入数据库，不填全了，先凑合，因为之后要改redis
            LoginTicket captcha_database;
            captcha_database.setUserId(0);
            captcha_database.setTicket(captcha_ticket);
            captcha_database.setExpired(Date::now().after(CAPTCHA_EXPIRED_SECONDS));
            service::login_ticket::add_login_ticket(captcha_database);

            response = HttpResponse::newCustomHttpResponse(getAPIJSON(true
                , "谷歌reCAPTCHA验证通过，challenge_ts: " + google_result.get("challenge_ts", "").toStyledString()));
            response->addHeader("Set-Cookie", "nowcoder_captcha=" + captcha_ticket + "; Path=" + API_PREFIX + "/login"); 
        }
        else
            response = HttpResponse::newHttpJsonResponse(getAPIJSON(false, "谷歌reCAPTCHA说您不是人，抱歉"));
    }
    else
    {
        response = HttpResponse::newHttpJsonResponse(getAPIJSON(false, "谷歌reCAPTCHA后端请求失败，抱歉请重试"));
    }
    
    callback(response);
}

void LoginController::login(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback
    , api_data::login::LoginData post_data)
{
    User user;  // 登录用户，如果有
    string error_message;  // 错误信息，如果错
    bool success;  // 登录是否成功，调用UserService获得
    string captcha_cookie = req->getCookie("nowcoder_captcha");
    HttpResponsePtr response;

    // 检查人机验证
    LoginTicket captcha_ticket = service::login_ticket::find_login_ticket_by_ticket(captcha_cookie);
    if (captcha_ticket.getValueOfId() == 0 || captcha_ticket.getValueOfExpired() < trantor::Date::now()) {
        response = HttpResponse::newHttpJsonResponse(getAPIJSON(false, "请进行人机验证（可能需要刷新页面）"));
        callback(response);
        return;
    }

    // 检查账号
    success = service::user::login(post_data.username, post_data.password, user, error_message);
    if (success) 
    {
        // 生成jwt cookie
        string token = jwt::create()
            .set_subject(to_string(user.getValueOfId()))
            // 过期时间，不用jwt的.set_expires_at的是因为又是个不一样的Date类，不设成exp是因为也会报错
            .set_payload_claim("tmo", jwt::claim(to_string(Date::now().after(DEFAULT_EXPIRED_SECONDS).secondsSinceEpoch())))  
            // 在ext时间后延长过期时间
            .set_payload_claim("ext", jwt::claim(to_string(Date::now().after(DEFAULT_EXPIRED_SECONDS * 0.8).secondsSinceEpoch())))  
            .set_type("JWS")
            .sign(jwt::algorithm::hs256{JWT_SECRET});
        
        response = HttpResponse::newCustomHttpResponse(getAPIJSON(true, "登录成功"));
        response->addHeader("Set-Cookie", "nowcoder_jwt=" + token + "; Expires=Fri, 31 Dec 9999 23:59:59 GMT; Path=/");
    }
    else 
        response = HttpResponse::newHttpJsonResponse(getAPIJSON(false, error_message));

    callback(response);
}

struct MemoryStruct 
{
    char *memory;
    size_t size;
    MemoryStruct()
    {
        memory = (char *)malloc(1);  
        size = 0;
    }
    ~MemoryStruct()
    {
        free(memory);
        memory = NULL;
        size = 0;
    }
};

size_t WriteMemoryCallback(void *ptr, size_t size, size_t nmemb, void *data)
{
    size_t realsize = size * nmemb;
    struct MemoryStruct *mem = (struct MemoryStruct *)data;

    mem->memory = (char *)realloc(mem->memory, mem->size + realsize + 1);
    if (mem->memory) 
    {
        memcpy(&(mem->memory[mem->size]), ptr, realsize);
        mem->size += realsize;
        mem->memory[mem->size] = 0;
    }
    return realsize;
}

bool google_verify(string ticket, Json::Value &google_answer)
{
    string url = "https://www.google.com/recaptcha/api/siteverify";
    string filename = "result.json";

    CURLcode res = curl_global_init(CURL_GLOBAL_ALL);
    if(CURLE_OK != res)
    {
        LOG_ERROR << "failed when call curl_global_init() in google_verify()";
        return false;
    }

    CURL * pCurl;
    pCurl = curl_easy_init();
    if(NULL == pCurl)
    {
        LOG_ERROR << "failed when call curl_easy_init() in google_verify()";
        return false;
    }

    curl_slist * pList = NULL;
    pList = curl_slist_append(pList,"Content-Type:application/x-www-form-urlencoded; charset=UTF-8"); 
    pList = curl_slist_append(pList,"Accept:application/json, text/javascript, */*; q=0.01"); 
    pList = curl_slist_append(pList,"Accept-Language:zh-CN,zh;q=0.8"); 
    curl_easy_setopt(pCurl, CURLOPT_HTTPHEADER, pList); 
    
    curl_easy_setopt(pCurl, CURLOPT_URL, url.c_str() );  //提交表单的URL地址

    curl_easy_setopt(pCurl, CURLOPT_HEADER, 0L);  // 启用时会将头文件的信息作为数据流输
    curl_easy_setopt(pCurl, CURLOPT_FOLLOWLOCATION, 1L);  // 允许重定向
    curl_easy_setopt(pCurl, CURLOPT_NOSIGNAL, 1L);

    //将返回结果通过回调函数写到自定义的对象中
    MemoryStruct oDataChunk;
    curl_easy_setopt(pCurl, CURLOPT_WRITEDATA, &oDataChunk);
    curl_easy_setopt(pCurl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback); 

    curl_easy_setopt(pCurl, CURLOPT_VERBOSE, 1L);  // 启用时会汇报所有的信息  这还真不能注释掉了，提醒可能连不上网
    // post表单参数
    string strJsonData;
    strJsonData = "secret=6LfY_0EoAAAAALEG4CxCI9qqgfPrIVl7pdtXuFU2&";
    strJsonData += "response=" + ticket;
    // libcur的相关POST配置项
    curl_easy_setopt(pCurl, CURLOPT_POST, 1L);
    curl_easy_setopt(pCurl, CURLOPT_POSTFIELDS, strJsonData.c_str());  
    curl_easy_setopt(pCurl, CURLOPT_POSTFIELDSIZE, strJsonData.size());
    
    res = curl_easy_perform(pCurl);

    long res_code = 0;
    res = curl_easy_getinfo(pCurl, CURLINFO_RESPONSE_CODE, &res_code);

    curl_slist_free_all(pList); 
    curl_easy_cleanup(pCurl);
    curl_global_cleanup();

    if(( res == CURLE_OK ) && (res_code == 200 || res_code == 201))
    {
        string result = string(oDataChunk.memory, oDataChunk.size);
        Json::Reader reader;
        reader.parse(result, google_answer);
        return true;
    }
    else
        return false;
}
