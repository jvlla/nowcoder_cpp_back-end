/*
 * Kafka生产者，主要来自https://github.com/confluentinc/librdkafka/blob/master/examples/producer.c
 */
#pragma once
#include <queue>
#include <mutex>
#include <condition_variable>
#include <assert.h>
#include <json/json.h>
#include "Singleton.h"

class KafkaProducer: public Singleton<KafkaProducer> {
friend Singleton<KafkaProducer>;

public:
    /*
     * 发送消息
     * @param key Kafka topic
     * @param value kafka消息内容
     */
    void post_message(std::string key, Json::Value value);

    /*
     * 运行生产者
     * @param broker 服务器列表
     */
    void run(std::string broker);

protected:
    KafkaProducer();
    virtual ~KafkaProducer();

private:
    static std::queue<std::pair<std::string, Json::Value>> message_queue_; // 任务队列
    static std::mutex mutex_;               // 用于互斥访问的锁 
    static std::condition_variable cond_;   // 用于互斥访问的条件变量
    static std::string broker_;             // Kafka服务器地址
};
