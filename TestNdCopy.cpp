#include <iostream>
#include <vector>
#include "adios2/helper/adiosMemory.h"

// Define a test function
int testNdCopy2D() {
    // Define input and output buffers
    char in[100]; // Assuming a buffer size of 100
    char out[100]; // Assuming a buffer size of 100

    // Initialize 'in' with sequential values from 1 to 100
    for (int i = 0; i < 100; ++i) {
        in[i] = i + 1;
    }

    // Define input and output core dimensions
    std::vector<size_t> inStart = {0, 1}; // Example values
    std::vector<size_t> inCount = {10, 10}; // Example values

    bool inIsRowMajor = true;
    bool inIsLittleEndian = true;

    std::vector<size_t> outStart = {2, 2}; // Example values
    std::vector<size_t> outCount = {4, 4}; // Example values
    bool outIsRowMajor = true;
    bool outIsLittleEndian = true;
    int typeSize = sizeof(char); // Assuming char type

    // Call the NdCopy function
    int result = adios2::helper::NdCopy(in, inStart, inCount, inIsRowMajor, inIsLittleEndian,
                        out, outStart, outCount, outIsRowMajor, outIsLittleEndian,
                        typeSize);

    // print the out
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            std::cout << (int)out[i * 4 + j] << " ";
        }
        std::cout << std::endl;
    }

    // Test case passed
    std::cout << "NdCopy test passed." << std::endl;
    return 0;
}

// Define a test function
int testNdCopy2DSmallToBig() {
    // Define input and output buffers
    char in[100] = {0}; // Assuming a buffer size of 100
    char out[16]; // Assuming a buffer size of 100

    // Initialize 'in' with sequential values from 1 to 100
    for (int i = 0; i < 16; ++i) {
        out[i] = i + 1;
    }

    // Define input and output core dimensions
    std::vector<size_t> inStart = {0, 1}; // Example values
    std::vector<size_t> inCount = {10, 10}; // Example values

    bool inIsRowMajor = true;
    bool inIsLittleEndian = true;

    std::vector<size_t> outStart = {2, 2}; // Example values
    std::vector<size_t> outCount = {4, 4}; // Example values
    bool outIsRowMajor = true;
    bool outIsLittleEndian = true;
    int typeSize = sizeof(char); // Assuming char type

    // Call the NdCopy function
    int result = adios2::helper::NdCopy(out, outStart, outCount, outIsRowMajor, outIsLittleEndian,
                                        in, inStart, inCount, inIsRowMajor, inIsLittleEndian,
                                        typeSize);

    // print the in
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            std::cout << (int)in[i * 10 + j] << " ";
        }
        std::cout << std::endl;
    }
    
    // Test case passed
    std::cout << "NdCopy test passed." << std::endl;
    return 0;
}

// Define a test function
int testNdCopy3D() {
    // Define input and output buffers
    const int sizeX = 10;
    const int sizeY = 10;
    const int sizeZ = 10;
    int in[sizeX * sizeY * sizeZ]; // Assuming a buffer size of 1000
    int out[sizeX * sizeY * sizeZ]; // Assuming a buffer size of 1000

    // Initialize 'in' with sequential values from 1 to 1000
    for (int i = 0; i < sizeX * sizeY * sizeZ; ++i) {
        in[i] = i + 1;
    }

    // Define input and output core dimensions as std::vector<size_t>
    std::vector<size_t> inStart = {0, 0, 0}; // Example values
    std::vector<size_t> inCount = {10, 10, 10}; // Example values
    bool inIsRowMajor = true;
    bool inIsLittleEndian = true;
    std::vector<size_t> outStart = {2, 2, 2}; // Example values
    std::vector<size_t> outCount = {4, 4, 4}; // Example values
    bool outIsRowMajor = true;
    bool outIsLittleEndian = true;
    int typeSize = sizeof(int); // Assuming char type

    // Call the NdCopy function
    int result = adios2::helper::NdCopy(reinterpret_cast<char*>(in), inStart, inCount, inIsRowMajor, inIsLittleEndian,
                                        reinterpret_cast<char*>(out), outStart, outCount, outIsRowMajor, outIsLittleEndian,
                        typeSize);

    // print the out
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            for (int k = 0; k < 4; ++k) {
                std::cout << (int)out[i * 4 * 4 + j * 4 + k] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    return 0;
}

int main() {
    // Run the test
    return testNdCopy2DSmallToBig();
}
