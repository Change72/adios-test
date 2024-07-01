//
// Created by cguo51 on 4/26/24.
//

#include <iostream>
#include <vector>
#include "QueryBox.h"

using namespace adios2::kvcache;

void test_case_1(){
    // right below
    QueryBox bigBox("U32184|Start_0_0|Count_10_10|");
    QueryBox interactedBox("U32184|Start_2_2|Count_8_8|");
    std::cout << "Big box: " << bigBox.toString() << std::endl;
    std::cout << "Interacted box: " << interactedBox.toString() << std::endl;
    // Call the Cut function
    std::vector<QueryBox> cutBoxes;
    interactedBox.NdCut(bigBox, cutBoxes);

    // print the cut boxes
    for (size_t i = 0; i < cutBoxes.size(); ++i) {
        std::cout << "Cut box " << i << ": " << cutBoxes[i].toString() << std::endl;
    }

    std::cout << "===============================================================" << std::endl;
    std::cout << "NdCut test passed." << std::endl;
}

void test_case_2(){
    // left upper
    QueryBox bigBox("U32184|Start_0_0|Count_10_10|");
    QueryBox interactedBox("U32184|Start_0_0|Count_8_8|");
    std::cout << "Big box: " << bigBox.toString() << std::endl;
    std::cout << "Interacted box: " << interactedBox.toString() << std::endl;
    // Call the Cut function
    std::vector<QueryBox> cutBoxes;
    interactedBox.NdCut(bigBox, cutBoxes);

    // print the cut boxes
    for (size_t i = 0; i < cutBoxes.size(); ++i) {
        std::cout << "Cut box " << i << ": " << cutBoxes[i].toString() << std::endl;
    }

    std::cout << "===============================================================" << std::endl;
    std::cout << "NdCut test passed." << std::endl;
}

void test_case_3(){
    // right upper
    // left upper
    QueryBox bigBox("U32184|Start_0_0|Count_10_10|");
    QueryBox interactedBox("U32184|Start_4_0|Count_6_6|");
    std::cout << "Big box: " << bigBox.toString() << std::endl;
    std::cout << "Interacted box: " << interactedBox.toString() << std::endl;
    // Call the Cut function
    std::vector<QueryBox> cutBoxes;
    interactedBox.NdCut(bigBox, cutBoxes);

    // print the cut boxes
    for (size_t i = 0; i < cutBoxes.size(); ++i) {
        std::cout << "Cut box " << i << ": " << cutBoxes[i].toString() << std::endl;
    }

    std::cout << "===============================================================" << std::endl;
    std::cout << "NdCut test passed." << std::endl;
}

void test_case_4(){
    // left below
    // left upper
    QueryBox bigBox("U32184|Start_0_0|Count_10_10|");
    QueryBox interactedBox("U32184|Start_0_4|Count_6_6|");
    std::cout << "Big box: " << bigBox.toString() << std::endl;
    std::cout << "Interacted box: " << interactedBox.toString() << std::endl;
    // Call the Cut function
    std::vector<QueryBox> cutBoxes;
    interactedBox.NdCut(bigBox, cutBoxes);

    // print the cut boxes
    for (size_t i = 0; i < cutBoxes.size(); ++i) {
        std::cout << "Cut box " << i << ": " << cutBoxes[i].toString() << std::endl;
    }

    std::cout << "===============================================================" << std::endl;
    std::cout << "NdCut test passed." << std::endl;
}

void test_case_5(){
    // middle
    // left upper
    QueryBox bigBox("U32184|Start_0_0|Count_10_10|");
    QueryBox interactedBox("U32184|Start_2_4|Count_3_3|");
    std::cout << "Big box: " << bigBox.toString() << std::endl;
    std::cout << "Interacted box: " << interactedBox.toString() << std::endl;
    // Call the Cut function
    std::vector<QueryBox> cutBoxes;
    interactedBox.NdCut(bigBox, cutBoxes);

    // print the cut boxes
    for (size_t i = 0; i < cutBoxes.size(); ++i) {
        std::cout << "Cut box " << i << ": " << cutBoxes[i].toString() << std::endl;
    }

    std::cout << "===============================================================" << std::endl;
    std::cout << "NdCut test passed." << std::endl;

}

int main(){
    test_case_1();
    test_case_2();
    test_case_3();
    test_case_4();
    test_case_5();
}
