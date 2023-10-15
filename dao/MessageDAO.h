#pragma once
#include "../model/Message.h"

namespace dao {
namespace message {
/*
 * 查询当前用户的会话列表,针对每个会话只返回一条最新的私信
 * select *
 * from message
 * where id in (
 *     select max(id) from message
 *     where status != 2
 *     and from_id != 1
 *     and (from_id = #{userId} or to_id = #{user_id})
 *     group by conversation_id
 * )
 * order by id desc
 * limit #{offset}, #{limit}
 * @return 成功: Message vector; 失败: 空vector
 */
std::vector<drogon_model::nowcoder::Message> select_conversations(int user_id, int offset, int limit);

/*
 * 查询当前用户的会话数量
 * select count(*) from (
 *     select max(id) as maxid from message
 *     where status != 2
 *     and from_id != 1
 *     and (from_id = #{userId} or to_id = #{user_id})
 *     group by conversation_id
 * ) as m
 * @return 成功: 会话数量; 失败: -1
 */
int select_conversation_count(int user_id);

/*
 * 查询某个会话所包含的私信列表
 * select *
 * from message
 * where status != 2
 * and from_id != 1
 * and conversation_id = #{conversation_id}
 * order by id desc
 * limit #{offset}, #{limit}
 * @return 成功: Message vector; 失败: 空vector
 */
std::vector<drogon_model::nowcoder::Message> select_letters(std::string conversation_id, int offset, int limit);

/*
 * 查询某个会话所包含的私信数量
 * select count(id)
 * from message
 * where status != 2
 * and from_id != 1
 * and conversation_id = #{conversation_id}
 * @return 成功: 私信数量; 失败: -1
 */
int select_letter_count(std::string conversation_id);

/*
 * 查询未读私信的数量
 * select count(*)
 * from message
 * where status = 0
 * and from_id != 1
 * and to_id = #{userId}
 * and conversation_id = #{conversation_id}
 * @param conversation 为0不作为查询条件
 * @return 成功: 未读私信行数; 失败: -1
 */
int select_letter_unread_count(int user_id, std::string conversation_id);

/*
 * insert into message
 * values(#{message)
 * @return 成功: 1; 失败: -1
 */
int insert_message(drogon_model::nowcoder::Message message);

/*
 * update message set status = #{status}
 * where id in #{ids}
 * @return 成功: 更新行数; 失败: -1
 */
int update_status(std::vector<int> ids, int status);

/*
 * select *
 * from message
 * where id in (
 *     select max(id) from message
 *     where status != 2
 *     and from_id = 1
 *     and to_id = #{user_id}
 *     and conversation_id = #{topic}
 * )
 * @return 成功: Message vector; 失败: 空vector
 */
drogon_model::nowcoder::Message select_latest_notice(int user_id, std::string topic);

/*
 * select count(*) from messag
 * where status != 2
 * and from_id = 1
 * and to_id = #{user_id}
 * and conversation_id = #{topic}
 * @return 成功: 系统通知行数; 失败: -1
 */
int select_notice_count(int user_id, std::string topic);

/*
 * select count(id) from message
 * where status = 0
 * and from_id = 1
 * and to_id = #{userId}
 * <if test="topic!=null">
 *     and conversation_id = #{topic}
 * </if>
 * @param topic 为""不作为查询条件
 * @return @return 成功: 未读系统通知行数; 失败: -1
 */
int select_notice_unread_count(int user_id, std::string topic);

/*
 * select *
 * from message
 * where status != 2
 * and from_id = 1
 * and to_id = #{userId}
 * and conversation_id = #{topic}
 * order by create_time desc
 * limit #{offset}, #{limit}
 * @return 成功: Message vector; 失败: 空vector
 */
std::vector<drogon_model::nowcoder::Message> select_notices(int user_id, std::string topic, int offset, int limit);

}
}