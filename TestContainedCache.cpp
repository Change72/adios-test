#include <iostream>
#include <vector>
#include <set>
#include <string>
#include "QueryBox.h"
#include "KVCacheCommon.h"

using namespace adios2;

int main(int argc, char **argv) {
    int max_depth = 999;
    std::set<std::string> samePrefixKeys;
    std::string keyPrefix("U018446744073709551615");
    QueryBox targetBox("U018446744073709551615__count_:_64_1_64___start_:_0_32_0__");
    KVCacheCommon m_KVCacheCommon;

    std::vector<QueryBox> regularBoxes;
    std::vector<QueryBox> cachedBoxes;
    std::vector<std::string> cachedKeys;

    m_KVCacheCommon.openConnection();
    m_KVCacheCommon.keyPrefixExistence(keyPrefix, samePrefixKeys);
    if (samePrefixKeys.size() > 0) {
        targetBox.getMaxInteractBox(samePrefixKeys, max_depth, 0, regularBoxes,
                                    cachedBoxes, cachedKeys);
    } else {
        regularBoxes.push_back(targetBox);
    }
    std::cout << "Going to retrieve " << regularBoxes.size()
              << " boxes from remote server, and " << cachedBoxes.size()
              << " boxes from cache" << std::endl;
    for (auto &box : regularBoxes) {
        std::cout << "regular: " << box.toString() << std::endl;
    }
    m_KVCacheCommon.closeConnection();

}