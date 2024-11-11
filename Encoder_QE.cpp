#include <iostream>
#include <fstream>
#include <filesystem>
#include <sstream>
#include <string>
#include <random>
#include <ctime>
#include "Encoder_QE.h"
#include "ProductInfo.h"
// Simple XOR encryption function for demonstration
std::string xorEncryptDecrypt(const std::string& input, char key ='R') {
    std::string output = input;
    for (size_t i = 0; i < input.size(); ++i) {
        output[i] = input[i] ^ key;  // XOR with a key
    }
    return output;
}

// Function to generate a random ID of 8 alphanumeric characters
std::string generateId() {
    static const char chars[] = "0123456789abcdefghijklmnopqrstuvwxyz";
    std::default_random_engine engine(static_cast<unsigned>(time(0)));
    std::uniform_int_distribution<int> dist(0, sizeof(chars) - 2);  // -2 because we exclude null terminator
    std::string id;
    for (int i = 0; i < 8; ++i) {
        id += chars[dist(engine)];
    }
    return id;
}
#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS
std::string getCurrentDate() {
    // Get the current time
    time_t now = time(0);
    tm ltm;  // Create a tm struct
    
    // Use localtime_s instead of localtime for thread safety
    if (localtime_s(&ltm, &now) != 0) {
        std::cerr << "Failed to get local time." << std::endl;
        return "";
    }

    // Format the date as "YYYY-MM-DD"
    std::ostringstream dateStream;
    dateStream << 1900 + ltm.tm_year << "-" << 1 + ltm.tm_mon << "-" << ltm.tm_mday;

    return dateStream.str();
}



// Function to create the .mdb config file with encryption
bool createEncryptedConfigFile(const std::string& path, const std::string& fileName, std::string& mdbname) {
    // Construct the full path with .mdb extension
    std::filesystem::path fullPath = std::filesystem::path(path) / (fileName + ".mdb");

 


    // Prepare the content to be written in the config file
    std::ostringstream configContent;
    configContent << "version : "<< version<< "\n"
        << "created : " << getCurrentDate() << "\n"
        << "id : " << generateId() << "\n"
        << "mdb name : " << mdbname << "\n"
        << "pool.count : 0\n"
        << "pool.name : [pool.names]\n";

    // Encrypt the content
    std::string encryptedContent = xorEncryptDecrypt(configContent.str());

    try {
        // Create and open the file in binary mode
        std::ofstream file(fullPath, std::ios::binary);
        if (!file) {
            std::cerr << "Failed to create file: " << fullPath << std::endl;
            return false;
        }

        // Write encrypted content to the file
        file << encryptedContent;
        file.close();

        
        return true;
    }
    catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << std::endl;
        return false;
    }
}


