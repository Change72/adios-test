#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <hiredis/hiredis.h>

typedef struct {
    int32_t *Data;
} Request;

void store_to_redis(const char *key, int32_t *data, size_t length) {
    // Connect to Redis server
    redisContext *c = redisConnect("127.0.0.1", 6379);
    if (c == NULL || c->err) {
        if (c) {
            printf("Connection error: %s\n", c->errstr);
            redisFree(c);
        } else {
            printf("Connection error: can't allocate redis context\n");
        }
        exit(1);
    }

    // Serialize the data into a binary format
    size_t data_size = length * sizeof(int32_t);
    redisReply *reply = (redisReply *)redisCommand(c, "SET %s %b", key, data, data_size);
    if (reply == NULL) {
        printf("SET command failed: %s\n", c->errstr);
        redisFree(c);
        exit(1);
    }

    printf("SET command result: %s\n", reply->str);
    freeReplyObject(reply);

    // Disconnect from Redis server
    redisFree(c);
}

void get_and_print_from_redis(const char *key, size_t length) {
    // Connect to Redis server
    redisContext *c = redisConnect("127.0.0.1", 6379);
    if (c == NULL || c->err) {
        if (c) {
            printf("Connection error: %s\n", c->errstr);
            redisFree(c);
        } else {
            printf("Connection error: can't allocate redis context\n");
        }
        exit(1);
    }

    // Retrieve the data
    redisReply *reply = (redisReply *)redisCommand(c, "GET %s", key);
    if (reply == NULL) {
        printf("GET command failed: %s\n", c->errstr);
        redisFree(c);
        exit(1);
    }

    if (reply->type != REDIS_REPLY_STRING) {
        printf("Unexpected data type received: %d\n", reply->type);
        freeReplyObject(reply);
        redisFree(c);
        exit(1);
    }

    // Deserialize the data
    int32_t *data = (int32_t *)reply->str;

    // Print the data
    printf("Retrieved data:\n");
    for (size_t i = 0; i < length; ++i) {
        printf("%d ", data[i]);
    }
    printf("\n");

    freeReplyObject(reply);

    // Disconnect from Redis server
    redisFree(c);
}

int main() {
    size_t Nx = 10;
    Request Req;
    Req.Data = (int32_t *)malloc(Nx * sizeof(int32_t));
    
    // Fill Req.Data with some values
    for (size_t i = 0; i < Nx; ++i) {
        Req.Data[i] = (int32_t)i;
    }

    // Store Req.Data to Redis
    store_to_redis("Req.Data", Req.Data, Nx);

    // Retrieve and print Req.Data from Redis
    get_and_print_from_redis("Req.Data", Nx);

    // Free the allocated memory
    free(Req.Data);

    return 0;
}