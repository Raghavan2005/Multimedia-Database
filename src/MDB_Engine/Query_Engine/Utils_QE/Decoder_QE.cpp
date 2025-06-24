#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include "QE/Decoder_QE.h"

// Simple XOR encryption/decryption function
std::string xorEncryptDecrypt(const std::string& input  ) {
    std::string output = input;
    for (size_t i = 0; i < input.size(); ++i) {
        output[i] = input[i] ^ 'R';
    }
    return output;
}

// Function to read and decrypt the .mdb file content
bool readDecryptedConfigFile(const std::string& path, const std::string& fileName) {
    std::filesystem::path fullPath = std::filesystem::path(path) / (fileName + ".mdb");

    try {
        // Open the file in binary mode
        std::ifstream file(fullPath, std::ios::binary);
        if (!file) {
            std::cerr << "Failed to open file: " << fullPath << std::endl;
            return false;
        }

        // Read the encrypted content
        std::string encryptedContent((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        file.close();

        // Decrypt the content
        std::string decryptedContent = xorEncryptDecrypt(encryptedContent);

        // Output the decrypted content
        std::cout << "Decrypted Content:\n" << decryptedContent << std::endl;
        return true;
    }
    catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << std::endl;
        return false;
    }
}

