/**
 *
 *  User.h
 *  DO NOT EDIT. This file is generated by drogon_ctl
 *
 */

#pragma once
#include <drogon/orm/Result.h>
#include <drogon/orm/Row.h>
#include <drogon/orm/Field.h>
#include <drogon/orm/SqlBinder.h>
#include <drogon/orm/Mapper.h>
#include <drogon/orm/BaseBuilder.h>
#ifdef __cpp_impl_coroutine
#include <drogon/orm/CoroMapper.h>
#endif
#include <trantor/utils/Date.h>
#include <trantor/utils/Logger.h>
#include <json/json.h>
#include <string>
#include <string_view>
#include <memory>
#include <vector>
#include <tuple>
#include <stdint.h>
#include <iostream>

namespace drogon
{
namespace orm
{
class DbClient;
using DbClientPtr = std::shared_ptr<DbClient>;
}
}
namespace drogon_model
{
namespace nowcoder
{

class User
{
  public:
    struct Cols
    {
        static const std::string _id;
        static const std::string _username;
        static const std::string _password;
        static const std::string _salt;
        static const std::string _email;
        static const std::string _type;
        static const std::string _status;
        static const std::string _activation_code;
        static const std::string _header_url;
        static const std::string _create_time;
    };

    const static int primaryKeyNumber;
    const static std::string tableName;
    const static bool hasPrimaryKey;
    const static std::string primaryKeyName;
    using PrimaryKeyType = int32_t;
    const PrimaryKeyType &getPrimaryKey() const;

    /**
     * @brief constructor
     * @param r One row of records in the SQL query result.
     * @param indexOffset Set the offset to -1 to access all columns by column names,
     * otherwise access all columns by offsets.
     * @note If the SQL is not a style of 'select * from table_name ...' (select all
     * columns by an asterisk), please set the offset to -1.
     */
    explicit User(const drogon::orm::Row &r, const ssize_t indexOffset = 0) noexcept;

    /**
     * @brief constructor
     * @param pJson The json object to construct a new instance.
     */
    explicit User(const Json::Value &pJson) noexcept(false);

    /**
     * @brief constructor
     * @param pJson The json object to construct a new instance.
     * @param pMasqueradingVector The aliases of table columns.
     */
    User(const Json::Value &pJson, const std::vector<std::string> &pMasqueradingVector) noexcept(false);

    User() = default;

    void updateByJson(const Json::Value &pJson) noexcept(false);
    void updateByMasqueradedJson(const Json::Value &pJson,
                                 const std::vector<std::string> &pMasqueradingVector) noexcept(false);
    static bool validateJsonForCreation(const Json::Value &pJson, std::string &err);
    static bool validateMasqueradedJsonForCreation(const Json::Value &,
                                                const std::vector<std::string> &pMasqueradingVector,
                                                    std::string &err);
    static bool validateJsonForUpdate(const Json::Value &pJson, std::string &err);
    static bool validateMasqueradedJsonForUpdate(const Json::Value &,
                                          const std::vector<std::string> &pMasqueradingVector,
                                          std::string &err);
    static bool validJsonOfField(size_t index,
                          const std::string &fieldName,
                          const Json::Value &pJson,
                          std::string &err,
                          bool isForCreation);

    /**  For column id  */
    ///Get the value of the column id, returns the default value if the column is null
    const int32_t &getValueOfId() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<int32_t> &getId() const noexcept;
    ///Set the value of the column id
    void setId(const int32_t &pId) noexcept;

    /**  For column username  */
    ///Get the value of the column username, returns the default value if the column is null
    const std::string &getValueOfUsername() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<std::string> &getUsername() const noexcept;
    ///Set the value of the column username
    void setUsername(const std::string &pUsername) noexcept;
    void setUsername(std::string &&pUsername) noexcept;
    void setUsernameToNull() noexcept;

    /**  For column password  */
    ///Get the value of the column password, returns the default value if the column is null
    const std::string &getValueOfPassword() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<std::string> &getPassword() const noexcept;
    ///Set the value of the column password
    void setPassword(const std::string &pPassword) noexcept;
    void setPassword(std::string &&pPassword) noexcept;
    void setPasswordToNull() noexcept;

    /**  For column salt  */
    ///Get the value of the column salt, returns the default value if the column is null
    const std::string &getValueOfSalt() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<std::string> &getSalt() const noexcept;
    ///Set the value of the column salt
    void setSalt(const std::string &pSalt) noexcept;
    void setSalt(std::string &&pSalt) noexcept;
    void setSaltToNull() noexcept;

    /**  For column email  */
    ///Get the value of the column email, returns the default value if the column is null
    const std::string &getValueOfEmail() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<std::string> &getEmail() const noexcept;
    ///Set the value of the column email
    void setEmail(const std::string &pEmail) noexcept;
    void setEmail(std::string &&pEmail) noexcept;
    void setEmailToNull() noexcept;

    /**  For column type  */
    ///Get the value of the column type, returns the default value if the column is null
    const int32_t &getValueOfType() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<int32_t> &getType() const noexcept;
    ///Set the value of the column type
    void setType(const int32_t &pType) noexcept;
    void setTypeToNull() noexcept;

    /**  For column status  */
    ///Get the value of the column status, returns the default value if the column is null
    const int32_t &getValueOfStatus() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<int32_t> &getStatus() const noexcept;
    ///Set the value of the column status
    void setStatus(const int32_t &pStatus) noexcept;
    void setStatusToNull() noexcept;

    /**  For column activation_code  */
    ///Get the value of the column activation_code, returns the default value if the column is null
    const std::string &getValueOfActivationCode() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<std::string> &getActivationCode() const noexcept;
    ///Set the value of the column activation_code
    void setActivationCode(const std::string &pActivationCode) noexcept;
    void setActivationCode(std::string &&pActivationCode) noexcept;
    void setActivationCodeToNull() noexcept;

    /**  For column header_url  */
    ///Get the value of the column header_url, returns the default value if the column is null
    const std::string &getValueOfHeaderUrl() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<std::string> &getHeaderUrl() const noexcept;
    ///Set the value of the column header_url
    void setHeaderUrl(const std::string &pHeaderUrl) noexcept;
    void setHeaderUrl(std::string &&pHeaderUrl) noexcept;
    void setHeaderUrlToNull() noexcept;

    /**  For column create_time  */
    ///Get the value of the column create_time, returns the default value if the column is null
    const ::trantor::Date &getValueOfCreateTime() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<::trantor::Date> &getCreateTime() const noexcept;
    ///Set the value of the column create_time
    void setCreateTime(const ::trantor::Date &pCreateTime) noexcept;
    void setCreateTimeToNull() noexcept;


    static size_t getColumnNumber() noexcept {  return 10;  }
    static const std::string &getColumnName(size_t index) noexcept(false);

    Json::Value toJson() const;
    Json::Value toMasqueradedJson(const std::vector<std::string> &pMasqueradingVector) const;
    /// Relationship interfaces
  private:
    friend drogon::orm::Mapper<User>;
    friend drogon::orm::BaseBuilder<User, true, true>;
    friend drogon::orm::BaseBuilder<User, true, false>;
    friend drogon::orm::BaseBuilder<User, false, true>;
    friend drogon::orm::BaseBuilder<User, false, false>;
#ifdef __cpp_impl_coroutine
    friend drogon::orm::CoroMapper<User>;
#endif
    static const std::vector<std::string> &insertColumns() noexcept;
    void outputArgs(drogon::orm::internal::SqlBinder &binder) const;
    const std::vector<std::string> updateColumns() const;
    void updateArgs(drogon::orm::internal::SqlBinder &binder) const;
    ///For mysql or sqlite3
    void updateId(const uint64_t id);
    std::shared_ptr<int32_t> id_;
    std::shared_ptr<std::string> username_;
    std::shared_ptr<std::string> password_;
    std::shared_ptr<std::string> salt_;
    std::shared_ptr<std::string> email_;
    std::shared_ptr<int32_t> type_;
    std::shared_ptr<int32_t> status_;
    std::shared_ptr<std::string> activationCode_;
    std::shared_ptr<std::string> headerUrl_;
    std::shared_ptr<::trantor::Date> createTime_;
    struct MetaData
    {
        const std::string colName_;
        const std::string colType_;
        const std::string colDatabaseType_;
        const ssize_t colLength_;
        const bool isAutoVal_;
        const bool isPrimaryKey_;
        const bool notNull_;
    };
    static const std::vector<MetaData> metaData_;
    bool dirtyFlag_[10]={ false };
  public:
    static const std::string &sqlForFindingByPrimaryKey()
    {
        static const std::string sql="select * from " + tableName + " where id = ?";
        return sql;
    }

    static const std::string &sqlForDeletingByPrimaryKey()
    {
        static const std::string sql="delete from " + tableName + " where id = ?";
        return sql;
    }
    std::string sqlForInserting(bool &needSelection) const
    {
        std::string sql="insert into " + tableName + " (";
        size_t parametersCount = 0;
        needSelection = false;
            sql += "id,";
            ++parametersCount;
        if(dirtyFlag_[1])
        {
            sql += "username,";
            ++parametersCount;
        }
        if(dirtyFlag_[2])
        {
            sql += "password,";
            ++parametersCount;
        }
        if(dirtyFlag_[3])
        {
            sql += "salt,";
            ++parametersCount;
        }
        if(dirtyFlag_[4])
        {
            sql += "email,";
            ++parametersCount;
        }
        if(dirtyFlag_[5])
        {
            sql += "type,";
            ++parametersCount;
        }
        if(dirtyFlag_[6])
        {
            sql += "status,";
            ++parametersCount;
        }
        if(dirtyFlag_[7])
        {
            sql += "activation_code,";
            ++parametersCount;
        }
        if(dirtyFlag_[8])
        {
            sql += "header_url,";
            ++parametersCount;
        }
        if(dirtyFlag_[9])
        {
            sql += "create_time,";
            ++parametersCount;
        }
        needSelection=true;
        if(parametersCount > 0)
        {
            sql[sql.length()-1]=')';
            sql += " values (";
        }
        else
            sql += ") values (";

        sql +="default,";
        if(dirtyFlag_[1])
        {
            sql.append("?,");

        }
        if(dirtyFlag_[2])
        {
            sql.append("?,");

        }
        if(dirtyFlag_[3])
        {
            sql.append("?,");

        }
        if(dirtyFlag_[4])
        {
            sql.append("?,");

        }
        if(dirtyFlag_[5])
        {
            sql.append("?,");

        }
        if(dirtyFlag_[6])
        {
            sql.append("?,");

        }
        if(dirtyFlag_[7])
        {
            sql.append("?,");

        }
        if(dirtyFlag_[8])
        {
            sql.append("?,");

        }
        if(dirtyFlag_[9])
        {
            sql.append("?,");

        }
        if(parametersCount > 0)
        {
            sql.resize(sql.length() - 1);
        }
        sql.append(1, ')');
        LOG_TRACE << sql;
        return sql;
    }
};
} // namespace nowcoder
} // namespace drogon_model