/*
 * message相关业务
 */
#pragma once
#include "../model/Message.h"

namespace service {
namespace message{

/*
 * 查找当前用户的会话列表，每个会话只返回一条最新的私信
 * @param 用户id
 * @param offset sql查询偏移量
 * @param limit sql查询行数限制
 * @return 会话查询结果，多个
 */
std::vector<drogon_model::nowcoder::Message> find_conversations(int user_id, int offset, int limit);

/*
 * 查询当前用户总会话数量
 * @param user_id 用户id
 * @return 总会话数
 */
int find_conversation_count(int user_id);

/*
 * 根据会话号查询会话所包含的私信列表
 * @param conversation_id 会话号
 * @param offset sql查询偏移量
 * @param limit sql查询行数限制
 * @return 会话查询结果，多个
 */
std::vector<drogon_model::nowcoder::Message> find_letters(std::string conversation_id, int offset, int limit);

/*
 * 根据会话号查询会话所包含的私信数量
 * @param conversation_id 会话号
 * @return 私信数量
 */
int find_letter_count(std::string conversation_id);

/*
 * 查询用户未读私信数量
 * @param conversation_id 会话号（为空字符串查找所有会话总未读私信数量）
 * @return 未读私信数量
 */
int find_letter_unread_count(int user_id, std::string conversation_id);

/*
 * 插入私信
 * @param post 要添加的私信
 * @return 成功: 添加行数(1); 失败: -1
 */
int add_message(drogon_model::nowcoder::Message message);

/*
 * 将私信设为已读
 * @param ids 私信号（多个）
 * @return 更新行数
 */
int read_message(std::vector<int> ids);

/*
 * 查询最新系统通知
 * @param user_id 用户id
 * @param topic 通知类型
 */
drogon_model::nowcoder::Message find_latest_notice(int user_id, std::string topic);

/*
 * 查询系统通知数量
 * @param user_id 用户id
 * @param topic 通知类型
 */
int find_notice_count(int user_id, std::string topic);

/*
 * 查询未读系统通知数量
 * @param user_id 用户id
 * @param topic 通知类型(为空字符串查询全部类型)
 */
int find_notice_unread_count(int user_id, std::string topic);

/*
 * 查询系统通知
 * @param user_id 用户id
 * @param topic 通知类型
 * @param offset 偏移量
 * @param limit 数量限制
 */
std::vector<drogon_model::nowcoder::Message> find_notices(int user_id, std::string topic, int offset, int limit);

}
}