//
// Created by cguo51 on 4/26/24.
//

#include <iostream>
#include <vector>
#include "QueryBox.h"

void test_case_1(){
    // right below
    adios2::QueryBox originalBox({0, 0}, {10, 10});
    adios2::QueryBox remainingBox({2, 2}, {8, 8});

    // Call the Cut function
    std::vector<adios2::QueryBox> cutBoxes;
    remainingBox.interactionCut(originalBox, cutBoxes);

    // print the cut boxes
    for (size_t i = 0; i < cutBoxes.size(); ++i) {
        std::cout << "Cut box " << i << ": start = ";
        for (size_t j = 0; j < cutBoxes[i].start.size(); ++j) {
            std::cout << cutBoxes[i].start[j] << " ";
        }
        std::cout << "count = ";
        for (size_t j = 0; j < cutBoxes[i].count.size(); ++j) {
            std::cout << cutBoxes[i].count[j] << " ";
        }
        std::cout << std::endl;
    }
}

void test_case_2(){
    // left upper
    adios2::QueryBox originalBox({0, 0}, {10, 10}); // Example original box (start, count)
    adios2::QueryBox remainingBox({0, 0}, {8, 8});

    // Call the Cut function
    std::vector<adios2::QueryBox> cutBoxes;
    remainingBox.interactionCut(originalBox, cutBoxes);

    // print the cut boxes
    for (size_t i = 0; i < cutBoxes.size(); ++i) {
        std::cout << "Cut box " << i << ": start = ";
        for (size_t j = 0; j < cutBoxes[i].start.size(); ++j) {
            std::cout << cutBoxes[i].start[j] << " ";
        }
        std::cout << "count = ";
        for (size_t j = 0; j < cutBoxes[i].count.size(); ++j) {
            std::cout << cutBoxes[i].count[j] << " ";
        }
        std::cout << std::endl;
    }
}

void test_case_3(){
    // right upper
    adios2::QueryBox originalBox({0, 0}, {10, 10}); // Example original box (start, count)
    adios2::QueryBox remainingBox({4, 0}, {6, 6});

    // Call the Cut function
    std::vector<adios2::QueryBox> cutBoxes;
    remainingBox.interactionCut(originalBox, cutBoxes);

    // print the cut boxes
    for (size_t i = 0; i < cutBoxes.size(); ++i) {
        std::cout << "Cut box " << i << ": start = ";
        for (size_t j = 0; j < cutBoxes[i].start.size(); ++j) {
            std::cout << cutBoxes[i].start[j] << " ";
        }
        std::cout << "count = ";
        for (size_t j = 0; j < cutBoxes[i].count.size(); ++j) {
            std::cout << cutBoxes[i].count[j] << " ";
        }
        std::cout << std::endl;
    }
}

void test_case_4(){
    // left below
    adios2::QueryBox originalBox({0, 0}, {10, 10}); // Example original box (start, count)
    adios2::QueryBox remainingBox({0, 4}, {6, 6});

    // Call the Cut function
    std::vector<adios2::QueryBox> cutBoxes;
    remainingBox.interactionCut(originalBox, cutBoxes);

    // print the cut boxes
    for (size_t i = 0; i < cutBoxes.size(); ++i) {
        std::cout << "Cut box " << i << ": start = ";
        for (size_t j = 0; j < cutBoxes[i].start.size(); ++j) {
            std::cout << cutBoxes[i].start[j] << " ";
        }
        std::cout << "count = ";
        for (size_t j = 0; j < cutBoxes[i].count.size(); ++j) {
            std::cout << cutBoxes[i].count[j] << " ";
        }
        std::cout << std::endl;
    }
}

void test_case_5(){
    // middle
    adios2::QueryBox originalBox({0, 0}, {10, 10}); // Example original box (start, count)
    adios2::QueryBox remainingBox({2, 4}, {3, 3});

    // Call the Cut function
    std::vector<adios2::QueryBox> cutBoxes;
    remainingBox.interactionCut(originalBox, cutBoxes);

    // print the cut boxes
    for (size_t i = 0; i < cutBoxes.size(); ++i) {
        std::cout << "Cut box " << i << ": start = ";
        for (size_t j = 0; j < cutBoxes[i].start.size(); ++j) {
            std::cout << cutBoxes[i].start[j] << " ";
        }
        std::cout << "count = ";
        for (size_t j = 0; j < cutBoxes[i].count.size(); ++j) {
            std::cout << cutBoxes[i].count[j] << " ";
        }
        std::cout << std::endl;
    }
}

int main(){
    test_case_5();
}
