#include "QueryBox.h"
#include <iostream>
#include <vector>

int main(){
    adios2::QueryBox bigBox("U018446744073709551615__count_:_64_64_64___start_:_0_0_0__");
    adios2::QueryBox smallBox("U018446744073709551615__count_:_32_64_64___start_:_32_0_0__");

    /*
    adios2::QueryBox interactedBox;
    bigBox.isInteracted(smallBox, interactedBox);
    // print interactedBox
    std::cout << interactedBox.toString() << std::endl;

    smallBox.isInteracted(bigBox, interactedBox);
    std::cout << interactedBox.toString() << std::endl;
    */

    // test getMaxInteractBox
    // void getMaxInteractBox(const std::set<std::string> &samePrefixKeys, const size_t &max_depth, size_t current_depth, std::vector<QueryBox> &regularBoxes, std::vector<QueryBox> &cachedBox, std::vector<std::string> &cachedKeys)
    std::set<std::string> samePrefixKeys;
    
    samePrefixKeys.insert("U018446744073709551615__count_:_8_64_64___start_:_0_0_0__");
    samePrefixKeys.insert("U018446744073709551615__count_:_8_64_64___start_:_8_0_0__");
    samePrefixKeys.insert("U018446744073709551615__count_:_8_64_64___start_:_16_0_0__");
    samePrefixKeys.insert("U018446744073709551615__count_:_8_64_64___start_:_24_0_0__");
    samePrefixKeys.insert("U018446744073709551615__count_:_8_64_64___start_:_32_0_0__");
    samePrefixKeys.insert("U018446744073709551615__count_:_8_64_64___start_:_40_0_0__");
    samePrefixKeys.insert("U018446744073709551615__count_:_8_64_64___start_:_48_0_0__");
    samePrefixKeys.insert("U018446744073709551615__count_:_8_64_64___start_:_56_0_0__");
    
    std::vector<adios2::QueryBox> regularBoxes;
    std::vector<adios2::QueryBox> cachedBox;
    std::vector<std::string> cachedKeys;
    smallBox.getMaxInteractBox(samePrefixKeys, 4, 0, regularBoxes, cachedBox, cachedKeys);

    for (auto &box : regularBoxes)
    {
        std::cout << "regular: " << box.toString() << std::endl;
    }

    for (auto &box : cachedBox)
    {
        std::cout << "cached: " << box.toString() << std::endl;
    }

    for (auto &key : cachedKeys)
    {
        std::cout << key << std::endl;
    }


    std::cout << "test pass" << std::endl;
}

