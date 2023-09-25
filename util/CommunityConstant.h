/*
 * 常量头文件
 */
#pragma once
#include <string>

// 这个用在ADD_METHOD_TO里面，应该是预处理就替换了，所以不能等链接的时候再找，就写成static凑合一下好了
static const std::string API_PREFIX = "/api";
extern const int DEFAULT_EXPIRED_SECONDS;
extern const int REMEMBER_EXPIRED_SECONDS;
extern const int CAPTCHA_EXPIRED_SECONDS;
extern const std::string JWT_SECRET;
