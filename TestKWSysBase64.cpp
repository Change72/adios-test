#include <vector>
#include <string>
#include <iostream>
#include <cstring>  // For memcpy

#include <adios2sys/Base64.h>


template <typename T>
void encodeVector(const std::vector<T>& vec, std::string& encodedString) {
    size_t vecSize = vec.size() * sizeof(T);
    const unsigned char* vecBytes = reinterpret_cast<const unsigned char*>(vec.data());

    size_t encodedSize = vecSize * 3 / 2;
    std::vector<unsigned char> encodedBytes(encodedSize);

    size_t sizeAfterEncoded = adios2sysBase64_Encode(vecBytes, vecSize, encodedBytes.data(), 0);

    // Resize the vector to the actual size
    encodedBytes.resize(sizeAfterEncoded);

    // Convert the encoded bytes to a string
    encodedString.assign(encodedBytes.begin(), encodedBytes.end());
}

template <typename T>
void decodeVector(const std::string& str, std::vector<T>& vec) {
    size_t decodedSize = str.size() * 2;
    std::vector<unsigned char> decodedBytes(decodedSize);

    size_t sizeAfterDecoded = adios2sysBase64_Decode(reinterpret_cast<const unsigned char*>(str.data()), str.size(), decodedBytes.data(), decodedSize);

    // Resize the vector to the actual size
    decodedBytes.resize(sizeAfterDecoded);

    // Copy the decoded bytes to the vector
    vec.resize(sizeAfterDecoded / sizeof(T));
    memcpy(vec.data(), decodedBytes.data(), sizeAfterDecoded);

}

int main(int argc, char const *argv[])
{
    std::vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::string encodedString;
    encodeVector(vec, encodedString);
    std::cout << "Encoded string: " << encodedString << std::endl;

    std::vector<int> decodedVec;
    decodeVector(encodedString, decodedVec);
    std::cout << "Decoded vector: ";
    for (auto i : decodedVec) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    // Test with a string vector
    std::vector<std::string> strVec = {"Hello", "World", "KWSys", "Base64"};
    std::string encodedStrVec;
    encodeVector(strVec, encodedStrVec);
    std::cout << "Encoded string: " << encodedStrVec << std::endl;
    
    std::vector<std::string> decodedStrVec;
    decodeVector(encodedStrVec, decodedStrVec);
    std::cout << "Decoded vector: ";
    for (auto s : decodedStrVec) {
        std::cout << s << " ";
    }
    std::cout << std::endl;

    // Test with a double vector
    std::vector<double> doubleVec = {1.1, 2.2, 3.3, 4.4, 5.5};
    std::string encodedDoubleVec;
    encodeVector(doubleVec, encodedDoubleVec);
    std::cout << "Encoded string: " << encodedDoubleVec << std::endl;

    std::vector<double> decodedDoubleVec;
    decodeVector(encodedDoubleVec, decodedDoubleVec);
    std::cout << "Decoded vector: ";
    for (auto d : decodedDoubleVec) {
        std::cout << d << " ";
    }
    std::cout << std::endl;

    // Test with a longer double vector
    std::vector<double> longDoubleVec(1000);
    for (int i = 0; i < 1000; i++) {
        longDoubleVec[i] = i * 0.1;
    }
    std::string encodedLongDoubleVec;
    encodeVector(longDoubleVec, encodedLongDoubleVec);
    std::cout << "Encoded string: " << encodedLongDoubleVec << std::endl;

    std::vector<double> decodedLongDoubleVec;
    decodeVector(encodedLongDoubleVec, decodedLongDoubleVec);
    std::cout << "Decoded vector: ";
    for (auto d : decodedLongDoubleVec) {
        std::cout << d << " ";
    }
    std::cout << std::endl;


    return 0;
}


