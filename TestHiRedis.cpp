#include "KVCacheCommon.h"
#include "QueryBox.h"

using namespace adios2;

// Example function using kvcache.exists
void testCacheExistence(KVCacheCommon kvcache, const std::string& key) {
    bool exists = kvcache.exists(key);
    std::cout << "Key: " << key << " exists? " << (exists ? "Yes" : "No") << std::endl;
}

int main(int argc, char const *argv[])
{
    KVCacheCommon kvcache;
    kvcache.openConnection();
    // set 1 string
//    std::string str = "test";
//    kvcache.set("test", str);
//    // get 1 string
//    std::string str2;
//    kvcache.get("test", str2);
//    std::cout << str2 << std::endl;
//    // del string
//    kvcache.del("test");
    // exists string
//    std::cout << kvcache.exists("test") << std::endl;
    // Test with "U" key
    testCacheExistence(kvcache, "U018446744073709551615__count_:_64_64_64___start_:_0_0_0__");

    void* data;
    kvcache.AppendCommandInBatch("U018446744073709551615__count_:_64_64_64___start_:_0_0_0__", 1, 0, data);

    // Test with "V" key
    testCacheExistence(kvcache, "V018446744073709551615__count_:_64_64_64___start_:_0_0_0__");

    bool test = kvcache.exists("V018446744073709551615__count_:_64_64_64___start_:_0_0_0__");
    std::cout << test << std::endl;
    // set a list of double values
//    std::vector<double> vec = {1.1, 2.2, 3.3, 4.4, 5.5};
//    kvcache.set("test", vec);
//    // get a list of double values
//    std::vector<double> vec2;
//    kvcache.get("test", vec2);
//    for (auto &v : vec2)
//    {
//        std::cout << v << std::endl;
//    }
    // del list
//    kvcache.del("test");
    // exists list
//    std::cout << kvcache.exists("test") << std::endl;
    kvcache.closeConnection();
    return 0;
}
