#include <drogon/drogon.h>
#include <drogon/HttpController.h>
#include "filter/user_id_interceptors.h"
#include "filter/jwt_update.h"
#include "kafka/KafkaProducer.h"
#include "kafka/KafkaConsumer.h"

int main() {
    KafkaProducer::get_instance().run("127.0.0.1:9092");  // 运行kafka生产者和消费者
    KafkaConsumer::get_instance().run("127.0.0.1:9092");

    drogon::app()
        .loadConfigFile("../config.json")                             // 读取配置文件
        .setThreadNum(2 * (std::thread::hardware_concurrency() + 1))  // io密集型，先设两倍核心数线程试试
        .registerPreHandlingAdvice(get_user_id)                       // Pre-Handling，获取请求对应user_id
        .registerPostHandlingAdvice(jwt_update)                       // Post-Handling，jwt续期或删除
        .registerPostHandlingAdvice(remove_user_id)                   // Post-Handling，清除请求对应user_id
        .run();
    
    return 0;
}
