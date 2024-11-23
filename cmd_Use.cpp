#include <filesystem>
#include <iostream>
#include <sstream>
#include <string>         
#include <fstream>
#include "Decoder_QE.h"
#include "cmd_Use.h"
#include "globals.h"
// Function to decrypt and read config.mdb content
std::string decryptConfigFile(const std::string& filePath) {
    std::ifstream file(filePath, std::ios::binary);
    if (!file) {
        return "Error: Unable to open config file.";
    }

    // Read encrypted content
    std::string encryptedContent((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();

    // Decrypt content (simple XOR-based for demonstration; replace with actual method if needed)
    std::string decryptedContent = xorEncryptDecrypt(encryptedContent);
    return decryptedContent;
}

// Updated function to process "use" command and traverse folders
void process_use_command(const std::string& command) {
    std::istringstream stream(command);
    std::string subCommand;

    // Check command structure ("use")
    stream >> subCommand;
    if (subCommand != "use") {
        std::cerr << "Invalid command: Expected 'use' at the start.\n";
        return;
    }

    // Database name
    std::string dbName;
    stream >> dbName;

    if (dbName.empty()) {
        std::cerr << "Error: No database name provided.\n";
        return;
    }

    std::string path = "D:/testfolder";
    bool dbFound = false;

    // Iterate through each directory in the path
    for (const auto& entry : std::filesystem::directory_iterator(path)) {
        if (entry.is_directory()) {
            std::filesystem::path configPath = entry.path() / "config.mdb";

            // Reset configContent for each iteration
            std::string configContent;

            if (std::filesystem::exists(configPath)) {
                // Only proceed if the folder name matches the dbName
                if (entry.path().filename() == dbName) {
                    dbFound = true;
                    activeDatabase = dbName;
                    std::cout << "Database '" << dbName << "' found in folder: " << entry.path() << std::endl;

                    // Read and decrypt the config.mdb file
                    configContent = decryptConfigFile(configPath.string());
                    std::cout << "Config File Content:\n" << configContent << std::endl;
                    break;
                }
            }
        }
    }

    if (!dbFound) {
        std::cerr << "Database '" << dbName << "' not found or does not contain a valid config.mdb file.\n";
    }
}
