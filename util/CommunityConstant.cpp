/*
 * 常量在.cpp文件中定义，使用通过extern const
 */
#include "CommunityConstant.h"

// 默认状态的登录凭证的超时时间
const int DEFAULT_EXPIRED_SECONDS = 3600 * 12;
// 记住状态的登录凭证超时时间
const int REMEMBER_EXPIRED_SECONDS = 3600 * 24 * 100;

// 人机验证有效期时限
const int CAPTCHA_EXPIRED_SECONDS = 120;

// JWT密钥
const std::string JWT_SECRET = "nowcoder_ht";