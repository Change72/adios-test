#include "KVCacheCommon.h"

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
    

    // set a list of double values
    std::vector<double> vec = {1.1, 2.2, 3.3, 4.4, 5.5};
    kvcache.set("test", vec);
    // get a list of double values
    std::vector<double> vec2;
    kvcache.get("test", vec2);
    for (auto &v : vec2)
    {
        std::cout << v << std::endl;
    }
    // del list
    kvcache.del("test");
    // exists list
//    std::cout << kvcache.exists("test") << std::endl;
    kvcache.closeConnection();
    return 0;
}
