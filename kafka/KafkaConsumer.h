/*
 * kafka消费者，主要来自https://github.com/confluentinc/librdkafka/blob/master/examples/consumer.c
 */
#include "Singleton.h"

class KafkaConsumer: public Singleton<KafkaConsumer> {
friend Singleton<KafkaConsumer>;

public:
    /*
     * 运行消费者
     * @param broker 服务器列表
     */
    void run(std::string broker);

private:
    static std::string broker_;  // Kafka服务器地址
};
