#include <hiredis/hiredis.h>
#include <iostream>
#include <chrono>
#include <vector>


redisContext* connectToRedis() {
    redisContext *c = redisConnect("127.0.0.1", 6379);
    if (c == nullptr || c->err) {
        if (c) {
            std::cerr << "Connection error: " << c->errstr << std::endl;
            redisFree(c);
        } else {
            std::cerr << "Connection error: can't allocate redis context" << std::endl;
        }
        exit(1);
    }
    return c;
}

void testWithoutPipelineSet() {
    redisContext *c = connectToRedis();
    const int numCommands = 1000;

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < numCommands; ++i) {
        std::string key = "key" + std::to_string(i);
        std::string value = "value" + std::to_string(i);
        redisReply *reply = (redisReply*)redisCommand(c, "SET %s %s", key.c_str(), value.c_str());
        if (reply == nullptr) {
            std::cerr << "SET command failed" << std::endl;
        } else {
            freeReplyObject(reply);
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Time taken of Set without pipeline: " << duration.count() << " seconds" << std::endl;

    redisFree(c);
}

void testWithPipelineSet() {
    redisContext *c = connectToRedis();
    const int numCommands = 1000;

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < numCommands; ++i) {
        std::string key = "key" + std::to_string(i);
        std::string value = "value" + std::to_string(i);
        redisAppendCommand(c, "SET %s %s", key.c_str(), value.c_str());
    }

    for (int i = 0; i < numCommands; ++i) {
        redisReply *reply;
        if (redisGetReply(c, (void**)&reply) == REDIS_OK) {
            freeReplyObject(reply);
        } else {
            std::cerr << "Pipeline command failed" << std::endl;
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Time taken of Set with pipeline: " << duration.count() << " seconds" << std::endl;

    redisFree(c);
}

void testWithoutPipelineGet() {
    redisContext *c = connectToRedis();
    const int numGets = 1000;
    std::vector<std::string> keys;

    // Prepare keys to GET
    for (int i = 0; i < numGets; ++i) {
        keys.push_back("key" + std::to_string(i));
    }

    auto start = std::chrono::high_resolution_clock::now();

    // Execute GET commands without pipeline
    for (const auto& key : keys) {
        redisReply *reply = (redisReply*)redisCommand(c, "GET %s", key.c_str());
        if (reply != nullptr && reply->type == REDIS_REPLY_STRING) {
            // Process or store reply as needed
            freeReplyObject(reply);
        } else {
            std::cerr << "GET command failed for key: " << key << std::endl;
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Time taken without pipeline: " << duration.count() << " seconds" << std::endl;

    redisFree(c);
}

void testWithPipelineGet() {
    redisContext *c = connectToRedis();
    const int numGets = 1000;
    std::vector<std::string> keys;

    // Prepare keys to GET
    for (int i = 0; i < numGets; ++i) {
        keys.push_back("key" + std::to_string(i));
    }

    auto start = std::chrono::high_resolution_clock::now();

    // Execute GET commands with pipeline
    for (const auto& key : keys) {
        redisAppendCommand(c, "GET %s", key.c_str());
    }

    for (const auto& key : keys) {
        redisReply *reply;
        if (redisGetReply(c, (void**)&reply) == REDIS_OK) {
            if (reply != nullptr && reply->type == REDIS_REPLY_STRING) {
                // Process or store reply as needed
//                std::cout << "GET for key " << key << ": " << reply->str << std::endl;
                freeReplyObject(reply);
            }
        } else {
            std::cerr << "Pipeline GET command failed for key: " << key << std::endl;
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Time taken with pipeline: " << duration.count() << " seconds" << std::endl;

    redisFree(c);
}

int main() {
    std::cout << "Testing SET without pipeline..." << std::endl;
    testWithoutPipelineSet();

    std::cout << "Testing SET with pipeline..." << std::endl;
    testWithPipelineSet();

    std::cout << "Testing GET without pipeline..." << std::endl;
    testWithoutPipelineGet();

    std::cout << "Testing GET with pipeline..." << std::endl;
    testWithPipelineGet();

    return 0;
}
