#include <iostream>
#include <vector>
#include <algorithm>
#include <adios2/helper/adiosType.h>


// Assuming CoreDims and DimsArray definitions are included here
using namespace adios2::helper;


int main() {
    // Using CoreDims with a vector
    std::vector<size_t> vec = {1, 2, 3, 4, 5};
    CoreDims coreDims(vec);
    std::cout << "CoreDims from vector: " << coreDims << std::endl;

    // Using DimsArray with different constructors
    DimsArray dims1(5);  // Initialize with no values
    std::cout << "DimsArray with no values: " << dims1 << std::endl;

    DimsArray dims2(5, 42);  // Initialize with a single value
    std::cout << "DimsArray with single value: " << dims2 << std::endl;

    DimsArray dims3(vec);  // Initialize from vector
    std::cout << "DimsArray from vector: " << dims3 << std::endl;

    size_t arr[] = {10, 20, 30, 40, 50};
    DimsArray dims4(5, arr);  // Initialize from array
    std::cout << "DimsArray from array: " << dims4 << std::endl;

    // Copying from CoreDims
    DimsArray dims5(coreDims);
    std::cout << "DimsArray copied from CoreDims: " << dims5 << std::endl;

    return 0;
}