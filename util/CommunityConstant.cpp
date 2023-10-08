/*
 * 常量在.cpp文件中定义，使用通过extern const
 */
#include "CommunityConstant.h"

// 人机验证有效期时限
const int CAPTCHA_EXPIRED_SECONDS = 120;

// 默认状态的登录凭证的超时时间
const int DEFAULT_EXPIRED_SECONDS = 3600 * 12;
// 记住状态的登录凭证超时时间
const int REMEMBER_EXPIRED_SECONDS = 3600 * 24 * 100;

// JWT密钥
const std::string JWT_SECRET = "nowcoder_ht";

// captcha的cookie的key
const std::string COOKIE_KEY_CAPTCHA = "nowcoder_captcha";
// jwt的cookie的key
const std::string COOKIE_KEY_JWT = "nowcoder_jwt";

// 头像文件夹路径
const std::string AVATAR_PATH = "./avatar/";

// 实体类型，帖子
const int ENTITY_TYPE_POST = 1;
// 实体类型:，评论
const int ENTITY_TYPE_COMMENT = 2;
