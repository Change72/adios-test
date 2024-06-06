#include "KVCacheCommon.h"

void KVCacheCommon::set(std::string key, const std::string& str)
{
    m_key = key;
    m_value = str;
    m_command = "SET " + m_key + " " + m_value;
    m_redisReply = (redisReply *)redisCommand(m_redisContext, m_command.c_str());
    if (m_redisReply == NULL)
    {
        std::cout << "Error: " << m_redisContext->errstr << std::endl;
    }
    else
    {
        std::cout << "SET Key: " << m_key << " Value: " << m_value << std::endl;
        freeReplyObject(m_redisReply);
    }
}

void KVCacheCommon::get(std::string key, std::string& str)
{
    m_key = key;
    m_command = "GET " + m_key;
    m_redisReply = (redisReply *)redisCommand(m_redisContext, m_command.c_str());
    if (m_redisReply == NULL)
    {
        std::cout << "Error: " << m_redisContext->errstr << std::endl;
    }
    else
    {
        // std::cout << "GET: " << m_redisReply->str << std::endl;
        str = m_redisReply->str;
        freeReplyObject(m_redisReply);
    }
}

