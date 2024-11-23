#include "cmd_Create.h"
#include <filesystem>
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>
#include "Encoder_QE.h"
#include "globals.h"

// Function prototypes
bool createFolder(const std::string& path, const std::string& folderName);
std::string editConfig(const std::string& config, const std::string& newPoolName);
std::vector<std::string> decodePools(const std::string& poolField);
std::string encodePools(const std::vector<std::string>& pools);

void process_create_command(const std::string& command) {
    std::istringstream stream(command);
    std::string subCommand;
    std::string path = "D:/testfolder";

    // Extract the main command ("create")
    stream >> subCommand;
    if (subCommand != "create") {
        std::cerr << "Invalid command: Expected 'create' at the start.\n";
        return;
    }

    // Extract the sub-type ("db" or "pool")
    std::string subType;
    stream >> subType;
    if (subType != "db" && subType != "pool") {
        std::cerr << "Invalid sub-command: Expected 'db' or 'pool' after 'create'.\n";
        return;
    }

    // Extract the database or pool name
    std::string dbName;
    stream >> dbName;

    // Validate if the name is provided
    if (dbName.empty()) {
        std::cerr << "Error: No name provided for the " << subType << ".\n";
        return;
    }

    // Execute based on sub-type
    if (subType == "db") {
        if (createFolder(path, dbName)) {
            std::cout << "Database created successfully.\n";
            std::cout << "Info: Use the command 'use " << dbName << "' to access the database.\n";

            // Create a config file for the new database
            createEncryptedConfigFile(path + '/' + dbName, "config", dbName);
        }
    }
    else if (subType == "pool") {
        // Ensure a database is currently in use
        if (activeDatabase.empty()) {
            std::cerr << "Error: No active database. Use the 'use <dbname>' command to activate a database before creating a pool.\n";
            return;
        }

        // Create the pool inside the active database folder
        std::string activeDbPath = path + '/' + activeDatabase;
        if (createFolder(activeDbPath, dbName)) {
            // Load and edit the configuration file
            std::ifstream configFile(activeDbPath + "/config.mdb");
            if (!configFile.is_open()) {
                std::cerr << "Error: Could not open configuration file for editing.\n";
                return;
            }

            std::string configContent((std::istreambuf_iterator<char>(configFile)),
                std::istreambuf_iterator<char>());
            configFile.close();

            std::string updatedConfig = editConfig(configContent, dbName);

            // Write the updated config back to the file
            std::ofstream outFile(activeDbPath + "/config.mdb");
            if (!outFile.is_open()) {
                std::cerr << "Error: Could not write to configuration file.\n";
                return;
            }

            outFile << updatedConfig;
            outFile.close();

            std::cout << "Pool '" << dbName << "' created successfully inside the active database '" << activeDatabase << "'.\n";
        }
    }
}

bool createFolder(const std::string& path, const std::string& folderName) {
    // Construct the full path by combining the path and folder name
    std::filesystem::path fullPath = std::filesystem::path(path) / folderName;

    try {
        // Check if the directory already exists
        if (std::filesystem::exists(fullPath)) {
            std::cout << "Error: The folder already exists: " << fullPath << std::endl;
            return false;
        }

        // Create the directory and check if it was successful
        if (std::filesystem::create_directory(fullPath)) {
            return true;
        }
        else {
            std::cout << "Error: Failed to create folder: " << fullPath << std::endl;
            return false;
        }
    }
    catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << std::endl;
        return false;
    }
}

// Decode pool names from the string
std::vector<std::string> decodePools(const std::string& poolField) {
    std::vector<std::string> pools;
    if (poolField.front() == '[' && poolField.back() == ']') {
        std::string names = poolField.substr(1, poolField.size() - 2); // Remove brackets
        size_t pos = 0;
        while ((pos = names.find(',')) != std::string::npos) {
            pools.push_back(names.substr(0, pos));
            names.erase(0, pos + 1);
        }
        if (!names.empty()) pools.push_back(names);
    }
    return pools;
}

// Encode pools back into a string
std::string encodePools(const std::vector<std::string>& pools) {
    std::string result = "[";
    for (size_t i = 0; i < pools.size(); ++i) {
        result += pools[i];
        if (i < pools.size() - 1) {
            result += ",";
        }
    }
    result += "]";
    return result;
}

// Edit the configuration string
std::string editConfig(const std::string& config, const std::string& newPoolName) {
    std::istringstream stream(config);
    std::ostringstream updatedConfig;
    std::string line;
    int poolCount = 0;
    std::vector<std::string> pools;

    while (std::getline(stream, line)) {
        if (line.find("pool.count :") != std::string::npos) {
            // Extract and increment the current pool count
            size_t pos = line.find(":");
            poolCount = std::stoi(line.substr(pos + 1));
            ++poolCount;
            updatedConfig << "pool.count : " << poolCount << '\n';
        }
        else if (line.find("pool.name :") != std::string::npos) {
            // Decode, add the new pool, and encode the pool names
            size_t pos = line.find(":");
            pools = decodePools(line.substr(pos + 1));
            pools.push_back(newPoolName);
            updatedConfig << "pool.name : " << encodePools(pools) << '\n';
        }
        else {
            // Copy other lines unchanged
            updatedConfig << line << '\n';
        }
    }

    return updatedConfig.str();
}
