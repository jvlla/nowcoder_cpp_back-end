#include "KafkaConsumer.h"

#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <ctype.h>

#include <thread>
#include <vector>
#include <json/json.h>
#include "../service/MessageService.h"
#include "../util/CommunityConstant.h"
using namespace std;
using namespace drogon_model::nowcoder;

/* Typical include path would be <librdkafka/rdkafka.h>, but this program
 * is builtin from within the librdkafka source tree and thus differs. */
#include <librdkafka/rdkafka.h>
// #include "rdkafka.h"

static volatile sig_atomic_t run = 1;

/**
 * @brief Signal termination of program
 */
static void stop(int sig) {
    run = 0;
}

/**
 * @returns 1 if all bytes are printable, else 0.
 */
static int is_printable(const char *buf, size_t size) {
    size_t i;

    for (i = 0; i < size; i++)
        if (!isprint((int)buf[i]))
            return 0;

    return 1;
}

string KafkaConsumer::broker_;

void KafkaConsumer::run(std::string broker)
{
    broker_ = broker;

    std::thread thread([]() {
        rd_kafka_t *rk;          /* Consumer instance handle */
        rd_kafka_conf_t *conf;   /* Temporary configuration object */
        rd_kafka_resp_err_t err; /* librdkafka API error code */
        char errstr[512];        /* librdkafka API error reporting buffer */
        const char *brokers;     /* Argument: broker list */
        const char *groupid;     /* Argument: Consumer group id */
        // char **topics;           /* Argument: list of topics to subscribe to */
        vector<string> topics;
        int topic_cnt;           /* Number of topics to subscribe to */
        rd_kafka_topic_partition_list_t *subscription; /* Subscribed topics */
        int i;

        brokers   = broker_.c_str();
        groupid   = "0";
        topics    = {TOPIC_COMMENT, TOPIC_FOLLOW, TOPIC_LIKE};
        topic_cnt = 3;

        /*
         * Create Kafka client configuration place-holder
         */
        conf = rd_kafka_conf_new();

        /* Set bootstrap broker(s) as a comma-separated list of
         * host or host:port (default port 9092).
         * librdkafka will use the bootstrap brokers to acquire the full
         * set of brokers from the cluster. 
         */
        if (rd_kafka_conf_set(conf, "bootstrap.servers", brokers, errstr, sizeof(errstr)) != RD_KAFKA_CONF_OK) {
            fprintf(stderr, "%s\n", errstr);
            rd_kafka_conf_destroy(conf);
            exit(-1);
        }

        /* Set the consumer group id.
         * All consumers sharing the same group id will join the same
         * group, and the subscribed topic' partitions will be assigned
         * according to the partition.assignment.strategy
         * (consumer config property) to the consumers in the group. */
        if (rd_kafka_conf_set(conf, "group.id", groupid, errstr, sizeof(errstr)) != RD_KAFKA_CONF_OK) {
            fprintf(stderr, "%s\n", errstr);
            rd_kafka_conf_destroy(conf);
            exit(-1);
        }

        /* If there is no previously committed offset for a partition
         * the auto.offset.reset strategy will be used to decide where
         * in the partition to start fetching messages.
         * By setting this to earliest the consumer will read all messages
         * in the partition if there was no previously committed offset. 
         */
        if (rd_kafka_conf_set(conf, "auto.offset.reset", "earliest", errstr, sizeof(errstr)) != RD_KAFKA_CONF_OK) {
            fprintf(stderr, "%s\n", errstr);
            rd_kafka_conf_destroy(conf);
            return 1;
        }

        /*
         * Create consumer instance.
         *
         * NOTE: rd_kafka_new() takes ownership of the conf object
         *       and the application must not reference it again after
         *       this call.
         */
        rk = rd_kafka_new(RD_KAFKA_CONSUMER, conf, errstr, sizeof(errstr));
        if (!rk) {
            fprintf(stderr, "%% Failed to create new consumer: %s\n", errstr);
            exit(-1);
        }

        conf = NULL;  /* Configuration object is now owned, and freed, by the rd_kafka_t instance. */

        /* Redirect all messages from per-partition queues to
         * the main queue so that messages can be consumed with one
         * call from all assigned partitions.
         *
         * The alternative is to poll the main queue (for events)
         * and each partition queue separately, which requires setting
         * up a rebalance callback and keeping track of the assignment:
         * but that is more complex and typically not recommended. 
         */
        rd_kafka_poll_set_consumer(rk);

        /* Convert the list of topics to a format suitable for librdkafka */
        subscription = rd_kafka_topic_partition_list_new(topic_cnt);
        for (i = 0; i < topic_cnt; i++)
            rd_kafka_topic_partition_list_add(subscription, topics[i].c_str(), RD_KAFKA_PARTITION_UA);
        /* the partition is ignored by subscribe() */
                                                    
        /* Subscribe to the list of topics */
        err = rd_kafka_subscribe(rk, subscription);
        if (err) {
            fprintf(stderr, "%% Failed to subscribe to %d topics: %s\n", subscription->cnt, rd_kafka_err2str(err));
            rd_kafka_topic_partition_list_destroy(subscription);
            rd_kafka_destroy(rk);
            exit(-1);
        }

        fprintf(stderr, "%% Subscribed to %d topic(s), waiting for rebalance and messages...\n", subscription->cnt);

        rd_kafka_topic_partition_list_destroy(subscription);

        /* Signal handler for clean shutdown */
        signal(SIGINT, stop);

        /* Subscribing to topics will trigger a group rebalance
         * which may take some time to finish, but there is no need
         * for the application to handle this idle period in a special way
         * since a rebalance may happen at any time.
         * Start polling for messages. 
         */

        while (true) {
            rd_kafka_message_t *rkm;

            rkm = rd_kafka_consumer_poll(rk, 100);
            if (!rkm)
                continue; /* Timeout: no message within 100ms,
                            *  try again. This short timeout allows
                            *  checking for `run` at frequent intervals.
                            */

            /* consumer_poll() will return either a proper message or a consumer error (rkm->err is set). */
            if (rkm->err) {
                /* Consumer errors are generally to be considered
                    * informational as the consumer will automatically
                    * try to recover from all types of errors. 
                    */
                // fprintf(stderr, "%% Consumer error: %s\n", rd_kafka_message_errstr(rkm));
                rd_kafka_message_destroy(rkm);
                continue;
            }

            /*
             * 这里是修改关键，获取topic和消息内容，进行处理并写入到数据库message表中
             */
            // 获取kafka topic和内容
            string kafka_topic(rd_kafka_topic_name(rkm->rkt));
            string kafka_value((const char *)rkm->payload);

            // 解析kafka内容
            Json::Value content_JSON;
            Json::Reader reader;
            kafka_value = drogon::utils::base64Decode(kafka_value);
            reader.parse(kafka_value, content_JSON);

            // 设置系统通知message
            Message message;
            message.setFromId(SYSTEM_USER_ID);
            message.setToId(content_JSON["entityUserId"].asInt());
            message.setConversationId(kafka_topic);
            message.setStatus(0);
            message.setCreateTime(trantor::Date::now());
            // 删除多余字段(entityUserId)后，重新json转字符串，并存进数据库
            content_JSON.removeMember("entityUserId");
            Json::StreamWriterBuilder wbuilder;
            wbuilder["indentation"] = "";
            string content_str = Json::writeString(wbuilder, content_JSON);
            message.setContent(content_str);

            service::message::add_message(message);

            // /* Proper message. */
            // printf("Message on %s [%" PRId32 "] at offset %" PRId64
            //     ":\n",
            //     rd_kafka_topic_name(rkm->rkt), rkm->partition, rkm->offset);

            // /* Print the message key. */
            // if (rkm->key && is_printable((const char *)rkm->key, rkm->key_len))
            //     printf(" Key: %.*s\n", (int)rkm->key_len, (const char *)rkm->key);
            // else if (rkm->key)
            //     printf(" Key: (%d bytes)\n", (int)rkm->key_len);

            // /* Print the message value/payload. */
            // if (rkm->payload && is_printable((const char *)rkm->payload, rkm->len))
            //     printf(" Value: %.*s\n", (int)rkm->len, (const char *)rkm->payload);
            // else if (rkm->payload)
            //     printf(" Value: (%d bytes)\n", (int)rkm->len);

            // rd_kafka_message_destroy(rkm);
        }

        /* Close the consumer: commit final offsets and leave the group. */
        fprintf(stderr, "%% Closing consumer\n");
        rd_kafka_consumer_close(rk);

        /* Destroy the consumer */
        rd_kafka_destroy(rk);

        return 0;
    });
    thread.detach();
}
