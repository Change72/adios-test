#include <iostream>
#include <vector>
#include <algorithm>
#include <adios2/helper/adiosType.h>


// Assuming CoreDims and DimsArray definitions are included here
using namespace adios2::helper;


int main() {
    /*
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
*/
    // Declare a pointer to DimsArray
    DimsArray* dimsPointer = nullptr;

    // Later, you can decide the count
    size_t count = 5; // Example count
    dimsPointer = new DimsArray(count);

    // Now you can initialize the array with values
    for (size_t i = 0; i < count; ++i) {
        (*dimsPointer)[i] = i + 1;
    }

    CoreDims& d1 = *dimsPointer;
    DimsArray dimsPointer4(d1);

    // dimsPointer2 by copy constructor
    DimsArray dimsPointer2(reinterpret_cast<CoreDims&>(*dimsPointer));

    // only copy the pointer, and will change the original value
//    DimsArray dimsPointer2(*dimsPointer);


    // dimsPoint3 by std::copy
//    DimsArray dimsPointer3(count, &(*dimsPointer)[0]);

//    DimsArray dimsPointer3(reinterpret_cast<CoreDims&>(dimsPointer2));
    DimsArray dimsPointer3(dimsPointer2);

    // Use the DimsArray pointer
    std::cout << "DimsArray initialized via pointer: " << *dimsPointer << std::endl;
    std::cout << "DimsArray copied from pointer: " << dimsPointer2 << std::endl;

    dimsPointer2[1] = 100;
    dimsPointer3[1] = 50;
    std::cout << "dimsPointer: " << *dimsPointer << std::endl;
    std::cout << "dimsPointer2: " << dimsPointer2 << std::endl;
    std::cout << "dimsPointer3: " << dimsPointer3 << std::endl;

    // Clean up and deallocate memory
    delete dimsPointer;

    return 0;
}