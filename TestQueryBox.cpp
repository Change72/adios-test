#include "QueryBox.h"
#include <iostream>
#include <vector>

int main(){
    // Test QueryBox
    std::vector<size_t> startVec = {0, 1, 2};
    std::vector<size_t> countVec = {3, 4, 5};

    adios2::helper::DimsArray startArray(startVec);
    adios2::helper::DimsArray countArray(countVec);

    adios2::kvcache::QueryBox queryBox(startArray, countArray);

    // Test the size method
    std::cout << "Size of QueryBox: " << queryBox.size() << std::endl; // Expected output: 60 (3 * 4 * 5)

    // Test the toString method
    std::cout << queryBox.toString() << std::endl; // Expected output: "Box start: [0, 1, 2], count: [3, 4, 5]"

    adios2::kvcache::QueryBox bigBox("U32184|Start_0_0_1|Count_2_14_5|");
    std::cout << "Size of QueryBox: " << bigBox.size() << std::endl; // Expected output: 140 (3 * 4 * 5)

    // Test the toString method
    std::cout << bigBox.toString() << std::endl; // Expected output: "Box start: [0, 1, 2], count: [3, 4, 5]"

//    adios2::kvcache::QueryBox interactedBox(queryBox);
//    queryBox.IsInteracted(bigBox, interactedBox);

    adios2::kvcache::QueryBox smallBox("U32184|Start_5_12_13|Count_2_14_5|");

    adios2::kvcache::QueryBox interactedBox(queryBox.DimCount);
    bool isInteract = queryBox.IsInteracted(bigBox, interactedBox);
    if (isInteract) {
        std::cout << "Interacted box: " << interactedBox.toString()
                  << std::endl; // Expected output: "Box start: [0, 1, 2], count: [2, 4, 4]"
    }
    else {
        std::cout << "No interaction" << std::endl;
    }

    adios2::kvcache::QueryBox interactedBox2(queryBox.DimCount);
    isInteract = queryBox.IsInteracted(smallBox, interactedBox2);
    if (isInteract) {
        std::cout << "Interacted box: " << interactedBox2.toString()
                  << std::endl; // Expected output: "Box start: [5, 12, 13], count: [2, 2, 2]"
    }
    else {
        std::cout << "No interaction" << std::endl;
    }
    return 0;

/*
    adios2::QueryBox bigBox("U018446744073709551615__count_:_64_64_64___start_:_0_0_0__");
    adios2::QueryBox smallBox("U018446744073709551615__count_:_32_64_64___start_:_32_0_0__");


    adios2::QueryBox interactedBox;
    bigBox.isInteracted(smallBox, interactedBox);
    // print interactedBox
    std::cout << interactedBox.toString() << std::endl;

    smallBox.isInteracted(bigBox, interactedBox);
    std::cout << interactedBox.toString() << std::endl;


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
    */

    std::cout << "test pass" << std::endl;
}

