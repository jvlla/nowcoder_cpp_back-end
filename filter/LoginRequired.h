/**
 *
 *  login_required.h
 *
 */
#pragma once
#include <drogon/HttpFilter.h>
using namespace drogon;

class LoginRequired : public HttpFilter<LoginRequired>
{
  public:
    LoginRequired() {}
    void doFilter(const HttpRequestPtr &req,
                  FilterCallback &&fcb,
                  FilterChainCallback &&fccb) override;
};

