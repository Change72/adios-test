//
// Created by cguo51 on 12/30/23.
//
#ifndef KVCACHECOMMON_CPP
#define KVCACHECOMMON_CPP

#include "KVCacheCommon.h"

namespace adios2
{

    void KVCacheCommon::openConnection()
    {
        m_redisContext = redisConnect(m_host.c_str(), m_port);
        if (m_redisContext == NULL || m_redisContext->err)
        {
            std::cout << "Error to connect to kvcache server: " << m_redisContext->errstr << std::endl;
            if (m_redisContext)
            {
                redisFree(m_redisContext);
            }
        }
        else
        {
            std::cout << "------------------------------------------------------------" << std::endl;
            std::cout << "Connected to kvcache server. KV Cache Version Control: V1.0" << std::endl;
        }
    }

    void KVCacheCommon::closeConnection()
    {
        redisFree(m_redisContext);
        std::cout << "KVCache connection closed" << std::endl;
    }

    void KVCacheCommon::set(const char *key, size_t size, void *data){
        m_redisReply = (redisReply *)redisCommand(m_redisContext, "SET %s %b", key, data, size);
        if (m_redisReply == NULL)
        {
            std::cout << "Error to set key: " << key << std::endl;
        }
        else
        {
            std::cout << "SET Key: " << key << " Value size: " << size << std::endl;
            freeReplyObject(m_redisReply);
        }
    }

    void KVCacheCommon::get(const char *key, size_t size, void *data){
        m_redisReply = (redisReply *)redisCommand(m_redisContext, "GET %s", key);
        if (m_redisReply == NULL)
        {
            std::cout << "Error to get key: " << key << std::endl;
        }
        else
        {
            memcpy(data, m_redisReply->str, size);
            freeReplyObject(m_redisReply);
        }
    }

    void KVCacheCommon::AppendCommandInBatch(const char *key, size_t mode, size_t size, void *data)
    {
        if (mode == 0)
        {
            redisAppendCommand(m_redisContext, "SET %s %b", key, data, size);
        }
        else if (mode == 1)
        {
            redisAppendCommand(m_redisContext, "GET %s", key);
        }
    }

    void KVCacheCommon::ExecuteBatch(const char *key, size_t mode, size_t size, void *data)
    {
        if (redisGetReply(m_redisContext, (void**)&m_redisReply) == REDIS_OK) {
            if (mode == 1)
            {
                memcpy(data, m_redisReply->str, size);
            }
            freeReplyObject(m_redisReply);
        }
        else {
            std::cout << "Error to execute batch command: " << key << std::endl;
        }
    }

    void KVCacheCommon::del(std::string key)
    {
        m_command = "DEL " + key;
        m_redisReply = (redisReply *)redisCommand(m_redisContext, m_command.c_str());
        if (m_redisReply == NULL)
        {
            std::cout << "Error to delete key: " << key << std::endl;
        }
        else
        {
            freeReplyObject(m_redisReply);
        }
    }

    bool KVCacheCommon::exists(std::string key)
    {
        m_command = "EXISTS " + key;
        redisReply *reply = (redisReply *)redisCommand(m_redisContext, m_command.c_str());
        if (reply == NULL)
        {
            std::cout << "The Key: " << key << " does not exist" << std::endl;
            return false;
        }
        else
        {
            std::cout << "dfsfd " << reply->integer << std::endl;
            if (!reply->integer)
            {
                std::cout << "The Key: " << key << " 22222 does not exist" << std::endl;
                return false;
            }
            std::cout << "The Key: " << key << " exists" << std::endl;
            freeReplyObject(reply);
            return true;
        }
    }

    std::string KVCacheCommon::keyPrefix(char *VarName, size_t AbsStep, size_t BlockID)
    {
        return VarName + std::to_string(AbsStep) + std::to_string(BlockID);
    }

//    std::string KVCacheCommon::keyComposition(const std::string &key_prefix, Dims Start, Dims Count)
//    {
//        std::string box = QueryBox::serializeQueryBox(QueryBox{Start, Count});
//        std::string cacheKey = key_prefix + box;
//        // replace special characters
//        std::replace(cacheKey.begin(), cacheKey.end(), '"', '_');
//        std::replace(cacheKey.begin(), cacheKey.end(), ',', '_');
//        std::replace(cacheKey.begin(), cacheKey.end(), '(', '_');
//        std::replace(cacheKey.begin(), cacheKey.end(), ')', '_');
//        std::replace(cacheKey.begin(), cacheKey.end(), '[', '_');
//        std::replace(cacheKey.begin(), cacheKey.end(), ']', '_');
//        std::replace(cacheKey.begin(), cacheKey.end(), '{', '_');
//        std::replace(cacheKey.begin(), cacheKey.end(), '}', '_');
//        return cacheKey;
//    }

    void KVCacheCommon::keyPrefixExistence(const std::string &key_prefix, std::set<std::string> &keys)
    {
        std::string keyPattern = key_prefix + "*";
        m_command = "KEYS " + keyPattern;
        m_redisReply = (redisReply *)redisCommand(m_redisContext, m_command.c_str());
        if (m_redisReply == NULL)
        {
            std::cout << "Error to get keys with prefix: " << key_prefix << std::endl;
        }
        else
        {
            for (int i = 0; i < m_redisReply->elements; i++)
            {
                keys.insert(m_redisReply->element[i]->str);
            }
            freeReplyObject(m_redisReply);
        }
    }

};     // namespace adios2
#endif // KVCACHECOMMON_CPP