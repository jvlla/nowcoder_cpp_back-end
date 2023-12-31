/**
 *
 *  Message.cc
 *  DO NOT EDIT. This file is generated by drogon_ctl
 *
 */

#include "Message.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::nowcoder;

const std::string Message::Cols::_id = "id";
const std::string Message::Cols::_from_id = "from_id";
const std::string Message::Cols::_to_id = "to_id";
const std::string Message::Cols::_conversation_id = "conversation_id";
const std::string Message::Cols::_content = "content";
const std::string Message::Cols::_status = "status";
const std::string Message::Cols::_create_time = "create_time";
const std::string Message::primaryKeyName = "id";
const bool Message::hasPrimaryKey = true;
const std::string Message::tableName = "message";

const std::vector<typename Message::MetaData> Message::metaData_={
{"id","int32_t","int(11)",4,1,1,1},
{"from_id","int32_t","int(11)",4,0,0,0},
{"to_id","int32_t","int(11)",4,0,0,0},
{"conversation_id","std::string","varchar(45)",45,0,0,1},
{"content","std::string","text",0,0,0,0},
{"status","int32_t","int(11)",4,0,0,0},
{"create_time","::trantor::Date","timestamp",0,0,0,0}
};
const std::string &Message::getColumnName(size_t index) noexcept(false)
{
    assert(index < metaData_.size());
    return metaData_[index].colName_;
}
Message::Message(const Row &r, const ssize_t indexOffset) noexcept
{
    if(indexOffset < 0)
    {
        if(!r["id"].isNull())
        {
            id_=std::make_shared<int32_t>(r["id"].as<int32_t>());
        }
        if(!r["from_id"].isNull())
        {
            fromId_=std::make_shared<int32_t>(r["from_id"].as<int32_t>());
        }
        if(!r["to_id"].isNull())
        {
            toId_=std::make_shared<int32_t>(r["to_id"].as<int32_t>());
        }
        if(!r["conversation_id"].isNull())
        {
            conversationId_=std::make_shared<std::string>(r["conversation_id"].as<std::string>());
        }
        if(!r["content"].isNull())
        {
            content_=std::make_shared<std::string>(r["content"].as<std::string>());
        }
        if(!r["status"].isNull())
        {
            status_=std::make_shared<int32_t>(r["status"].as<int32_t>());
        }
        if(!r["create_time"].isNull())
        {
            auto timeStr = r["create_time"].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            auto p = strptime(timeStr.c_str(),"%Y-%m-%d %H:%M:%S",&stm);
            time_t t = mktime(&stm);
            size_t decimalNum = 0;
            if(p)
            {
                if(*p=='.')
                {
                    std::string decimals(p+1,&timeStr[timeStr.length()]);
                    while(decimals.length()<6)
                    {
                        decimals += "0";
                    }
                    decimalNum = (size_t)atol(decimals.c_str());
                }
                createTime_=std::make_shared<::trantor::Date>(t*1000000+decimalNum);
            }
        }
    }
    else
    {
        size_t offset = (size_t)indexOffset;
        if(offset + 7 > r.size())
        {
            LOG_FATAL << "Invalid SQL result for this model";
            return;
        }
        size_t index;
        index = offset + 0;
        if(!r[index].isNull())
        {
            id_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 1;
        if(!r[index].isNull())
        {
            fromId_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 2;
        if(!r[index].isNull())
        {
            toId_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 3;
        if(!r[index].isNull())
        {
            conversationId_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 4;
        if(!r[index].isNull())
        {
            content_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 5;
        if(!r[index].isNull())
        {
            status_=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 6;
        if(!r[index].isNull())
        {
            auto timeStr = r[index].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            auto p = strptime(timeStr.c_str(),"%Y-%m-%d %H:%M:%S",&stm);
            time_t t = mktime(&stm);
            size_t decimalNum = 0;
            if(p)
            {
                if(*p=='.')
                {
                    std::string decimals(p+1,&timeStr[timeStr.length()]);
                    while(decimals.length()<6)
                    {
                        decimals += "0";
                    }
                    decimalNum = (size_t)atol(decimals.c_str());
                }
                createTime_=std::make_shared<::trantor::Date>(t*1000000+decimalNum);
            }
        }
    }

}

Message::Message(const Json::Value &pJson, const std::vector<std::string> &pMasqueradingVector) noexcept(false)
{
    if(pMasqueradingVector.size() != 7)
    {
        LOG_ERROR << "Bad masquerading vector";
        return;
    }
    if(!pMasqueradingVector[0].empty() && pJson.isMember(pMasqueradingVector[0]))
    {
        dirtyFlag_[0] = true;
        if(!pJson[pMasqueradingVector[0]].isNull())
        {
            id_=std::make_shared<int32_t>((int32_t)pJson[pMasqueradingVector[0]].asInt64());
        }
    }
    if(!pMasqueradingVector[1].empty() && pJson.isMember(pMasqueradingVector[1]))
    {
        dirtyFlag_[1] = true;
        if(!pJson[pMasqueradingVector[1]].isNull())
        {
            fromId_=std::make_shared<int32_t>((int32_t)pJson[pMasqueradingVector[1]].asInt64());
        }
    }
    if(!pMasqueradingVector[2].empty() && pJson.isMember(pMasqueradingVector[2]))
    {
        dirtyFlag_[2] = true;
        if(!pJson[pMasqueradingVector[2]].isNull())
        {
            toId_=std::make_shared<int32_t>((int32_t)pJson[pMasqueradingVector[2]].asInt64());
        }
    }
    if(!pMasqueradingVector[3].empty() && pJson.isMember(pMasqueradingVector[3]))
    {
        dirtyFlag_[3] = true;
        if(!pJson[pMasqueradingVector[3]].isNull())
        {
            conversationId_=std::make_shared<std::string>(pJson[pMasqueradingVector[3]].asString());
        }
    }
    if(!pMasqueradingVector[4].empty() && pJson.isMember(pMasqueradingVector[4]))
    {
        dirtyFlag_[4] = true;
        if(!pJson[pMasqueradingVector[4]].isNull())
        {
            content_=std::make_shared<std::string>(pJson[pMasqueradingVector[4]].asString());
        }
    }
    if(!pMasqueradingVector[5].empty() && pJson.isMember(pMasqueradingVector[5]))
    {
        dirtyFlag_[5] = true;
        if(!pJson[pMasqueradingVector[5]].isNull())
        {
            status_=std::make_shared<int32_t>((int32_t)pJson[pMasqueradingVector[5]].asInt64());
        }
    }
    if(!pMasqueradingVector[6].empty() && pJson.isMember(pMasqueradingVector[6]))
    {
        dirtyFlag_[6] = true;
        if(!pJson[pMasqueradingVector[6]].isNull())
        {
            auto timeStr = pJson[pMasqueradingVector[6]].asString();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            auto p = strptime(timeStr.c_str(),"%Y-%m-%d %H:%M:%S",&stm);
            time_t t = mktime(&stm);
            size_t decimalNum = 0;
            if(p)
            {
                if(*p=='.')
                {
                    std::string decimals(p+1,&timeStr[timeStr.length()]);
                    while(decimals.length()<6)
                    {
                        decimals += "0";
                    }
                    decimalNum = (size_t)atol(decimals.c_str());
                }
                createTime_=std::make_shared<::trantor::Date>(t*1000000+decimalNum);
            }
        }
    }
}

Message::Message(const Json::Value &pJson) noexcept(false)
{
    if(pJson.isMember("id"))
    {
        dirtyFlag_[0]=true;
        if(!pJson["id"].isNull())
        {
            id_=std::make_shared<int32_t>((int32_t)pJson["id"].asInt64());
        }
    }
    if(pJson.isMember("from_id"))
    {
        dirtyFlag_[1]=true;
        if(!pJson["from_id"].isNull())
        {
            fromId_=std::make_shared<int32_t>((int32_t)pJson["from_id"].asInt64());
        }
    }
    if(pJson.isMember("to_id"))
    {
        dirtyFlag_[2]=true;
        if(!pJson["to_id"].isNull())
        {
            toId_=std::make_shared<int32_t>((int32_t)pJson["to_id"].asInt64());
        }
    }
    if(pJson.isMember("conversation_id"))
    {
        dirtyFlag_[3]=true;
        if(!pJson["conversation_id"].isNull())
        {
            conversationId_=std::make_shared<std::string>(pJson["conversation_id"].asString());
        }
    }
    if(pJson.isMember("content"))
    {
        dirtyFlag_[4]=true;
        if(!pJson["content"].isNull())
        {
            content_=std::make_shared<std::string>(pJson["content"].asString());
        }
    }
    if(pJson.isMember("status"))
    {
        dirtyFlag_[5]=true;
        if(!pJson["status"].isNull())
        {
            status_=std::make_shared<int32_t>((int32_t)pJson["status"].asInt64());
        }
    }
    if(pJson.isMember("create_time"))
    {
        dirtyFlag_[6]=true;
        if(!pJson["create_time"].isNull())
        {
            auto timeStr = pJson["create_time"].asString();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            auto p = strptime(timeStr.c_str(),"%Y-%m-%d %H:%M:%S",&stm);
            time_t t = mktime(&stm);
            size_t decimalNum = 0;
            if(p)
            {
                if(*p=='.')
                {
                    std::string decimals(p+1,&timeStr[timeStr.length()]);
                    while(decimals.length()<6)
                    {
                        decimals += "0";
                    }
                    decimalNum = (size_t)atol(decimals.c_str());
                }
                createTime_=std::make_shared<::trantor::Date>(t*1000000+decimalNum);
            }
        }
    }
}

void Message::updateByMasqueradedJson(const Json::Value &pJson,
                                            const std::vector<std::string> &pMasqueradingVector) noexcept(false)
{
    if(pMasqueradingVector.size() != 7)
    {
        LOG_ERROR << "Bad masquerading vector";
        return;
    }
    if(!pMasqueradingVector[0].empty() && pJson.isMember(pMasqueradingVector[0]))
    {
        if(!pJson[pMasqueradingVector[0]].isNull())
        {
            id_=std::make_shared<int32_t>((int32_t)pJson[pMasqueradingVector[0]].asInt64());
        }
    }
    if(!pMasqueradingVector[1].empty() && pJson.isMember(pMasqueradingVector[1]))
    {
        dirtyFlag_[1] = true;
        if(!pJson[pMasqueradingVector[1]].isNull())
        {
            fromId_=std::make_shared<int32_t>((int32_t)pJson[pMasqueradingVector[1]].asInt64());
        }
    }
    if(!pMasqueradingVector[2].empty() && pJson.isMember(pMasqueradingVector[2]))
    {
        dirtyFlag_[2] = true;
        if(!pJson[pMasqueradingVector[2]].isNull())
        {
            toId_=std::make_shared<int32_t>((int32_t)pJson[pMasqueradingVector[2]].asInt64());
        }
    }
    if(!pMasqueradingVector[3].empty() && pJson.isMember(pMasqueradingVector[3]))
    {
        dirtyFlag_[3] = true;
        if(!pJson[pMasqueradingVector[3]].isNull())
        {
            conversationId_=std::make_shared<std::string>(pJson[pMasqueradingVector[3]].asString());
        }
    }
    if(!pMasqueradingVector[4].empty() && pJson.isMember(pMasqueradingVector[4]))
    {
        dirtyFlag_[4] = true;
        if(!pJson[pMasqueradingVector[4]].isNull())
        {
            content_=std::make_shared<std::string>(pJson[pMasqueradingVector[4]].asString());
        }
    }
    if(!pMasqueradingVector[5].empty() && pJson.isMember(pMasqueradingVector[5]))
    {
        dirtyFlag_[5] = true;
        if(!pJson[pMasqueradingVector[5]].isNull())
        {
            status_=std::make_shared<int32_t>((int32_t)pJson[pMasqueradingVector[5]].asInt64());
        }
    }
    if(!pMasqueradingVector[6].empty() && pJson.isMember(pMasqueradingVector[6]))
    {
        dirtyFlag_[6] = true;
        if(!pJson[pMasqueradingVector[6]].isNull())
        {
            auto timeStr = pJson[pMasqueradingVector[6]].asString();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            auto p = strptime(timeStr.c_str(),"%Y-%m-%d %H:%M:%S",&stm);
            time_t t = mktime(&stm);
            size_t decimalNum = 0;
            if(p)
            {
                if(*p=='.')
                {
                    std::string decimals(p+1,&timeStr[timeStr.length()]);
                    while(decimals.length()<6)
                    {
                        decimals += "0";
                    }
                    decimalNum = (size_t)atol(decimals.c_str());
                }
                createTime_=std::make_shared<::trantor::Date>(t*1000000+decimalNum);
            }
        }
    }
}

void Message::updateByJson(const Json::Value &pJson) noexcept(false)
{
    if(pJson.isMember("id"))
    {
        if(!pJson["id"].isNull())
        {
            id_=std::make_shared<int32_t>((int32_t)pJson["id"].asInt64());
        }
    }
    if(pJson.isMember("from_id"))
    {
        dirtyFlag_[1] = true;
        if(!pJson["from_id"].isNull())
        {
            fromId_=std::make_shared<int32_t>((int32_t)pJson["from_id"].asInt64());
        }
    }
    if(pJson.isMember("to_id"))
    {
        dirtyFlag_[2] = true;
        if(!pJson["to_id"].isNull())
        {
            toId_=std::make_shared<int32_t>((int32_t)pJson["to_id"].asInt64());
        }
    }
    if(pJson.isMember("conversation_id"))
    {
        dirtyFlag_[3] = true;
        if(!pJson["conversation_id"].isNull())
        {
            conversationId_=std::make_shared<std::string>(pJson["conversation_id"].asString());
        }
    }
    if(pJson.isMember("content"))
    {
        dirtyFlag_[4] = true;
        if(!pJson["content"].isNull())
        {
            content_=std::make_shared<std::string>(pJson["content"].asString());
        }
    }
    if(pJson.isMember("status"))
    {
        dirtyFlag_[5] = true;
        if(!pJson["status"].isNull())
        {
            status_=std::make_shared<int32_t>((int32_t)pJson["status"].asInt64());
        }
    }
    if(pJson.isMember("create_time"))
    {
        dirtyFlag_[6] = true;
        if(!pJson["create_time"].isNull())
        {
            auto timeStr = pJson["create_time"].asString();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            auto p = strptime(timeStr.c_str(),"%Y-%m-%d %H:%M:%S",&stm);
            time_t t = mktime(&stm);
            size_t decimalNum = 0;
            if(p)
            {
                if(*p=='.')
                {
                    std::string decimals(p+1,&timeStr[timeStr.length()]);
                    while(decimals.length()<6)
                    {
                        decimals += "0";
                    }
                    decimalNum = (size_t)atol(decimals.c_str());
                }
                createTime_=std::make_shared<::trantor::Date>(t*1000000+decimalNum);
            }
        }
    }
}

const int32_t &Message::getValueOfId() const noexcept
{
    const static int32_t defaultValue = int32_t();
    if(id_)
        return *id_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &Message::getId() const noexcept
{
    return id_;
}
void Message::setId(const int32_t &pId) noexcept
{
    id_ = std::make_shared<int32_t>(pId);
    dirtyFlag_[0] = true;
}
const typename Message::PrimaryKeyType & Message::getPrimaryKey() const
{
    assert(id_);
    return *id_;
}

const int32_t &Message::getValueOfFromId() const noexcept
{
    const static int32_t defaultValue = int32_t();
    if(fromId_)
        return *fromId_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &Message::getFromId() const noexcept
{
    return fromId_;
}
void Message::setFromId(const int32_t &pFromId) noexcept
{
    fromId_ = std::make_shared<int32_t>(pFromId);
    dirtyFlag_[1] = true;
}
void Message::setFromIdToNull() noexcept
{
    fromId_.reset();
    dirtyFlag_[1] = true;
}

const int32_t &Message::getValueOfToId() const noexcept
{
    const static int32_t defaultValue = int32_t();
    if(toId_)
        return *toId_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &Message::getToId() const noexcept
{
    return toId_;
}
void Message::setToId(const int32_t &pToId) noexcept
{
    toId_ = std::make_shared<int32_t>(pToId);
    dirtyFlag_[2] = true;
}
void Message::setToIdToNull() noexcept
{
    toId_.reset();
    dirtyFlag_[2] = true;
}

const std::string &Message::getValueOfConversationId() const noexcept
{
    const static std::string defaultValue = std::string();
    if(conversationId_)
        return *conversationId_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Message::getConversationId() const noexcept
{
    return conversationId_;
}
void Message::setConversationId(const std::string &pConversationId) noexcept
{
    conversationId_ = std::make_shared<std::string>(pConversationId);
    dirtyFlag_[3] = true;
}
void Message::setConversationId(std::string &&pConversationId) noexcept
{
    conversationId_ = std::make_shared<std::string>(std::move(pConversationId));
    dirtyFlag_[3] = true;
}

const std::string &Message::getValueOfContent() const noexcept
{
    const static std::string defaultValue = std::string();
    if(content_)
        return *content_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Message::getContent() const noexcept
{
    return content_;
}
void Message::setContent(const std::string &pContent) noexcept
{
    content_ = std::make_shared<std::string>(pContent);
    dirtyFlag_[4] = true;
}
void Message::setContent(std::string &&pContent) noexcept
{
    content_ = std::make_shared<std::string>(std::move(pContent));
    dirtyFlag_[4] = true;
}
void Message::setContentToNull() noexcept
{
    content_.reset();
    dirtyFlag_[4] = true;
}

const int32_t &Message::getValueOfStatus() const noexcept
{
    const static int32_t defaultValue = int32_t();
    if(status_)
        return *status_;
    return defaultValue;
}
const std::shared_ptr<int32_t> &Message::getStatus() const noexcept
{
    return status_;
}
void Message::setStatus(const int32_t &pStatus) noexcept
{
    status_ = std::make_shared<int32_t>(pStatus);
    dirtyFlag_[5] = true;
}
void Message::setStatusToNull() noexcept
{
    status_.reset();
    dirtyFlag_[5] = true;
}

const ::trantor::Date &Message::getValueOfCreateTime() const noexcept
{
    const static ::trantor::Date defaultValue = ::trantor::Date();
    if(createTime_)
        return *createTime_;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &Message::getCreateTime() const noexcept
{
    return createTime_;
}
void Message::setCreateTime(const ::trantor::Date &pCreateTime) noexcept
{
    createTime_ = std::make_shared<::trantor::Date>(pCreateTime);
    dirtyFlag_[6] = true;
}
void Message::setCreateTimeToNull() noexcept
{
    createTime_.reset();
    dirtyFlag_[6] = true;
}

void Message::updateId(const uint64_t id)
{
    id_ = std::make_shared<int32_t>(static_cast<int32_t>(id));
}

const std::vector<std::string> &Message::insertColumns() noexcept
{
    static const std::vector<std::string> inCols={
        "from_id",
        "to_id",
        "conversation_id",
        "content",
        "status",
        "create_time"
    };
    return inCols;
}

void Message::outputArgs(drogon::orm::internal::SqlBinder &binder) const
{
    if(dirtyFlag_[1])
    {
        if(getFromId())
        {
            binder << getValueOfFromId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getToId())
        {
            binder << getValueOfToId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getConversationId())
        {
            binder << getValueOfConversationId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
    {
        if(getContent())
        {
            binder << getValueOfContent();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[5])
    {
        if(getStatus())
        {
            binder << getValueOfStatus();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[6])
    {
        if(getCreateTime())
        {
            binder << getValueOfCreateTime();
        }
        else
        {
            binder << nullptr;
        }
    }
}

const std::vector<std::string> Message::updateColumns() const
{
    std::vector<std::string> ret;
    if(dirtyFlag_[1])
    {
        ret.push_back(getColumnName(1));
    }
    if(dirtyFlag_[2])
    {
        ret.push_back(getColumnName(2));
    }
    if(dirtyFlag_[3])
    {
        ret.push_back(getColumnName(3));
    }
    if(dirtyFlag_[4])
    {
        ret.push_back(getColumnName(4));
    }
    if(dirtyFlag_[5])
    {
        ret.push_back(getColumnName(5));
    }
    if(dirtyFlag_[6])
    {
        ret.push_back(getColumnName(6));
    }
    return ret;
}

void Message::updateArgs(drogon::orm::internal::SqlBinder &binder) const
{
    if(dirtyFlag_[1])
    {
        if(getFromId())
        {
            binder << getValueOfFromId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getToId())
        {
            binder << getValueOfToId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getConversationId())
        {
            binder << getValueOfConversationId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
    {
        if(getContent())
        {
            binder << getValueOfContent();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[5])
    {
        if(getStatus())
        {
            binder << getValueOfStatus();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[6])
    {
        if(getCreateTime())
        {
            binder << getValueOfCreateTime();
        }
        else
        {
            binder << nullptr;
        }
    }
}
Json::Value Message::toJson() const
{
    Json::Value ret;
    if(getId())
    {
        ret["id"]=getValueOfId();
    }
    else
    {
        ret["id"]=Json::Value();
    }
    if(getFromId())
    {
        ret["from_id"]=getValueOfFromId();
    }
    else
    {
        ret["from_id"]=Json::Value();
    }
    if(getToId())
    {
        ret["to_id"]=getValueOfToId();
    }
    else
    {
        ret["to_id"]=Json::Value();
    }
    if(getConversationId())
    {
        ret["conversation_id"]=getValueOfConversationId();
    }
    else
    {
        ret["conversation_id"]=Json::Value();
    }
    if(getContent())
    {
        ret["content"]=getValueOfContent();
    }
    else
    {
        ret["content"]=Json::Value();
    }
    if(getStatus())
    {
        ret["status"]=getValueOfStatus();
    }
    else
    {
        ret["status"]=Json::Value();
    }
    if(getCreateTime())
    {
        ret["create_time"]=getCreateTime()->toDbStringLocal();
    }
    else
    {
        ret["create_time"]=Json::Value();
    }
    return ret;
}

Json::Value Message::toMasqueradedJson(
    const std::vector<std::string> &pMasqueradingVector) const
{
    Json::Value ret;
    if(pMasqueradingVector.size() == 7)
    {
        if(!pMasqueradingVector[0].empty())
        {
            if(getId())
            {
                ret[pMasqueradingVector[0]]=getValueOfId();
            }
            else
            {
                ret[pMasqueradingVector[0]]=Json::Value();
            }
        }
        if(!pMasqueradingVector[1].empty())
        {
            if(getFromId())
            {
                ret[pMasqueradingVector[1]]=getValueOfFromId();
            }
            else
            {
                ret[pMasqueradingVector[1]]=Json::Value();
            }
        }
        if(!pMasqueradingVector[2].empty())
        {
            if(getToId())
            {
                ret[pMasqueradingVector[2]]=getValueOfToId();
            }
            else
            {
                ret[pMasqueradingVector[2]]=Json::Value();
            }
        }
        if(!pMasqueradingVector[3].empty())
        {
            if(getConversationId())
            {
                ret[pMasqueradingVector[3]]=getValueOfConversationId();
            }
            else
            {
                ret[pMasqueradingVector[3]]=Json::Value();
            }
        }
        if(!pMasqueradingVector[4].empty())
        {
            if(getContent())
            {
                ret[pMasqueradingVector[4]]=getValueOfContent();
            }
            else
            {
                ret[pMasqueradingVector[4]]=Json::Value();
            }
        }
        if(!pMasqueradingVector[5].empty())
        {
            if(getStatus())
            {
                ret[pMasqueradingVector[5]]=getValueOfStatus();
            }
            else
            {
                ret[pMasqueradingVector[5]]=Json::Value();
            }
        }
        if(!pMasqueradingVector[6].empty())
        {
            if(getCreateTime())
            {
                ret[pMasqueradingVector[6]]=getCreateTime()->toDbStringLocal();
            }
            else
            {
                ret[pMasqueradingVector[6]]=Json::Value();
            }
        }
        return ret;
    }
    LOG_ERROR << "Masquerade failed";
    if(getId())
    {
        ret["id"]=getValueOfId();
    }
    else
    {
        ret["id"]=Json::Value();
    }
    if(getFromId())
    {
        ret["from_id"]=getValueOfFromId();
    }
    else
    {
        ret["from_id"]=Json::Value();
    }
    if(getToId())
    {
        ret["to_id"]=getValueOfToId();
    }
    else
    {
        ret["to_id"]=Json::Value();
    }
    if(getConversationId())
    {
        ret["conversation_id"]=getValueOfConversationId();
    }
    else
    {
        ret["conversation_id"]=Json::Value();
    }
    if(getContent())
    {
        ret["content"]=getValueOfContent();
    }
    else
    {
        ret["content"]=Json::Value();
    }
    if(getStatus())
    {
        ret["status"]=getValueOfStatus();
    }
    else
    {
        ret["status"]=Json::Value();
    }
    if(getCreateTime())
    {
        ret["create_time"]=getCreateTime()->toDbStringLocal();
    }
    else
    {
        ret["create_time"]=Json::Value();
    }
    return ret;
}

bool Message::validateJsonForCreation(const Json::Value &pJson, std::string &err)
{
    if(pJson.isMember("id"))
    {
        if(!validJsonOfField(0, "id", pJson["id"], err, true))
            return false;
    }
    if(pJson.isMember("from_id"))
    {
        if(!validJsonOfField(1, "from_id", pJson["from_id"], err, true))
            return false;
    }
    if(pJson.isMember("to_id"))
    {
        if(!validJsonOfField(2, "to_id", pJson["to_id"], err, true))
            return false;
    }
    if(pJson.isMember("conversation_id"))
    {
        if(!validJsonOfField(3, "conversation_id", pJson["conversation_id"], err, true))
            return false;
    }
    else
    {
        err="The conversation_id column cannot be null";
        return false;
    }
    if(pJson.isMember("content"))
    {
        if(!validJsonOfField(4, "content", pJson["content"], err, true))
            return false;
    }
    if(pJson.isMember("status"))
    {
        if(!validJsonOfField(5, "status", pJson["status"], err, true))
            return false;
    }
    if(pJson.isMember("create_time"))
    {
        if(!validJsonOfField(6, "create_time", pJson["create_time"], err, true))
            return false;
    }
    return true;
}
bool Message::validateMasqueradedJsonForCreation(const Json::Value &pJson,
                                                 const std::vector<std::string> &pMasqueradingVector,
                                                 std::string &err)
{
    if(pMasqueradingVector.size() != 7)
    {
        err = "Bad masquerading vector";
        return false;
    }
    try {
      if(!pMasqueradingVector[0].empty())
      {
          if(pJson.isMember(pMasqueradingVector[0]))
          {
              if(!validJsonOfField(0, pMasqueradingVector[0], pJson[pMasqueradingVector[0]], err, true))
                  return false;
          }
      }
      if(!pMasqueradingVector[1].empty())
      {
          if(pJson.isMember(pMasqueradingVector[1]))
          {
              if(!validJsonOfField(1, pMasqueradingVector[1], pJson[pMasqueradingVector[1]], err, true))
                  return false;
          }
      }
      if(!pMasqueradingVector[2].empty())
      {
          if(pJson.isMember(pMasqueradingVector[2]))
          {
              if(!validJsonOfField(2, pMasqueradingVector[2], pJson[pMasqueradingVector[2]], err, true))
                  return false;
          }
      }
      if(!pMasqueradingVector[3].empty())
      {
          if(pJson.isMember(pMasqueradingVector[3]))
          {
              if(!validJsonOfField(3, pMasqueradingVector[3], pJson[pMasqueradingVector[3]], err, true))
                  return false;
          }
        else
        {
            err="The " + pMasqueradingVector[3] + " column cannot be null";
            return false;
        }
      }
      if(!pMasqueradingVector[4].empty())
      {
          if(pJson.isMember(pMasqueradingVector[4]))
          {
              if(!validJsonOfField(4, pMasqueradingVector[4], pJson[pMasqueradingVector[4]], err, true))
                  return false;
          }
      }
      if(!pMasqueradingVector[5].empty())
      {
          if(pJson.isMember(pMasqueradingVector[5]))
          {
              if(!validJsonOfField(5, pMasqueradingVector[5], pJson[pMasqueradingVector[5]], err, true))
                  return false;
          }
      }
      if(!pMasqueradingVector[6].empty())
      {
          if(pJson.isMember(pMasqueradingVector[6]))
          {
              if(!validJsonOfField(6, pMasqueradingVector[6], pJson[pMasqueradingVector[6]], err, true))
                  return false;
          }
      }
    }
    catch(const Json::LogicError &e)
    {
      err = e.what();
      return false;
    }
    return true;
}
bool Message::validateJsonForUpdate(const Json::Value &pJson, std::string &err)
{
    if(pJson.isMember("id"))
    {
        if(!validJsonOfField(0, "id", pJson["id"], err, false))
            return false;
    }
    else
    {
        err = "The value of primary key must be set in the json object for update";
        return false;
    }
    if(pJson.isMember("from_id"))
    {
        if(!validJsonOfField(1, "from_id", pJson["from_id"], err, false))
            return false;
    }
    if(pJson.isMember("to_id"))
    {
        if(!validJsonOfField(2, "to_id", pJson["to_id"], err, false))
            return false;
    }
    if(pJson.isMember("conversation_id"))
    {
        if(!validJsonOfField(3, "conversation_id", pJson["conversation_id"], err, false))
            return false;
    }
    if(pJson.isMember("content"))
    {
        if(!validJsonOfField(4, "content", pJson["content"], err, false))
            return false;
    }
    if(pJson.isMember("status"))
    {
        if(!validJsonOfField(5, "status", pJson["status"], err, false))
            return false;
    }
    if(pJson.isMember("create_time"))
    {
        if(!validJsonOfField(6, "create_time", pJson["create_time"], err, false))
            return false;
    }
    return true;
}
bool Message::validateMasqueradedJsonForUpdate(const Json::Value &pJson,
                                               const std::vector<std::string> &pMasqueradingVector,
                                               std::string &err)
{
    if(pMasqueradingVector.size() != 7)
    {
        err = "Bad masquerading vector";
        return false;
    }
    try {
      if(!pMasqueradingVector[0].empty() && pJson.isMember(pMasqueradingVector[0]))
      {
          if(!validJsonOfField(0, pMasqueradingVector[0], pJson[pMasqueradingVector[0]], err, false))
              return false;
      }
    else
    {
        err = "The value of primary key must be set in the json object for update";
        return false;
    }
      if(!pMasqueradingVector[1].empty() && pJson.isMember(pMasqueradingVector[1]))
      {
          if(!validJsonOfField(1, pMasqueradingVector[1], pJson[pMasqueradingVector[1]], err, false))
              return false;
      }
      if(!pMasqueradingVector[2].empty() && pJson.isMember(pMasqueradingVector[2]))
      {
          if(!validJsonOfField(2, pMasqueradingVector[2], pJson[pMasqueradingVector[2]], err, false))
              return false;
      }
      if(!pMasqueradingVector[3].empty() && pJson.isMember(pMasqueradingVector[3]))
      {
          if(!validJsonOfField(3, pMasqueradingVector[3], pJson[pMasqueradingVector[3]], err, false))
              return false;
      }
      if(!pMasqueradingVector[4].empty() && pJson.isMember(pMasqueradingVector[4]))
      {
          if(!validJsonOfField(4, pMasqueradingVector[4], pJson[pMasqueradingVector[4]], err, false))
              return false;
      }
      if(!pMasqueradingVector[5].empty() && pJson.isMember(pMasqueradingVector[5]))
      {
          if(!validJsonOfField(5, pMasqueradingVector[5], pJson[pMasqueradingVector[5]], err, false))
              return false;
      }
      if(!pMasqueradingVector[6].empty() && pJson.isMember(pMasqueradingVector[6]))
      {
          if(!validJsonOfField(6, pMasqueradingVector[6], pJson[pMasqueradingVector[6]], err, false))
              return false;
      }
    }
    catch(const Json::LogicError &e)
    {
      err = e.what();
      return false;
    }
    return true;
}
bool Message::validJsonOfField(size_t index,
                               const std::string &fieldName,
                               const Json::Value &pJson,
                               std::string &err,
                               bool isForCreation)
{
    switch(index)
    {
        case 0:
            if(pJson.isNull())
            {
                err="The " + fieldName + " column cannot be null";
                return false;
            }
            if(isForCreation)
            {
                err="The automatic primary key cannot be set";
                return false;
            }
            if(!pJson.isInt())
            {
                err="Type error in the "+fieldName+" field";
                return false;
            }
            break;
        case 1:
            if(pJson.isNull())
            {
                return true;
            }
            if(!pJson.isInt())
            {
                err="Type error in the "+fieldName+" field";
                return false;
            }
            break;
        case 2:
            if(pJson.isNull())
            {
                return true;
            }
            if(!pJson.isInt())
            {
                err="Type error in the "+fieldName+" field";
                return false;
            }
            break;
        case 3:
            if(pJson.isNull())
            {
                err="The " + fieldName + " column cannot be null";
                return false;
            }
            if(!pJson.isString())
            {
                err="Type error in the "+fieldName+" field";
                return false;
            }
            // asString().length() creates a string object, is there any better way to validate the length?
            if(pJson.isString() && pJson.asString().length() > 45)
            {
                err="String length exceeds limit for the " +
                    fieldName +
                    " field (the maximum value is 45)";
                return false;
            }

            break;
        case 4:
            if(pJson.isNull())
            {
                return true;
            }
            if(!pJson.isString())
            {
                err="Type error in the "+fieldName+" field";
                return false;
            }
            break;
        case 5:
            if(pJson.isNull())
            {
                return true;
            }
            if(!pJson.isInt())
            {
                err="Type error in the "+fieldName+" field";
                return false;
            }
            break;
        case 6:
            if(pJson.isNull())
            {
                return true;
            }
            if(!pJson.isString())
            {
                err="Type error in the "+fieldName+" field";
                return false;
            }
            break;
        default:
            err="Internal error in the server";
            return false;
    }
    return true;
}
