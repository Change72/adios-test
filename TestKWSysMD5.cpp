#include <iostream>
#include <iomanip>
#include <cstring>
#include <adios2sys/MD5.h>  // Include the MD5 header

std::string md5(const std::string& input) {
    // Create a new MD5 instance
    adios2sysMD5* md5 = adios2sysMD5_New();
    if (!md5) {
        throw std::runtime_error("Failed to create MD5 instance");
    }

    // Initialize the MD5 instance
    adios2sysMD5_Initialize(md5);

    // Update the MD5 instance with the input data
    adios2sysMD5_Append(md5, reinterpret_cast<const unsigned char*>(input.c_str()), input.size());

    // Finalize the MD5 digest and get the hash value
    unsigned char digest[16];
    adios2sysMD5_Finalize(md5, digest);

    // Convert the digest to a hexadecimal string
    char hexDigest[32];
    adios2sysMD5_DigestToHex(digest, hexDigest);

    // Clean up the MD5 instance
    adios2sysMD5_Delete(md5);

    return std::string(hexDigest, 32);
}

int main() {
    std::string input = "This is a long string.";
    try {
        std::string hash = md5(input);
        std::cout << "MD5 hash: " << hash << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}