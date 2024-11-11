#include "cmd_Create.h"
#include <filesystem>
#include <iostream>
#include <sstream>
#include <string>         
#include <fstream>
#include <filesystem>
#include "Encoder_QE.h"
void process_create_command(const std::string& command) {

    std::istringstream stream(command);
    std::string subCommand;

    //  ("create")
    stream >> subCommand;
    if (subCommand != "create") {
        std::cerr << "Invalid command: Expected 'create' at the start.\n";
        return;
    }

    //  ("db")
    std::string subType;
    stream >> subType;
    if (subType != "db") {
        std::cerr << "Invalid sub-command: Expected 'db' after 'create'.\n";
        return;
    }

   // dbname
    std::string dbName;
    stream >> dbName;

    // If no dbname is provided, show an error
    if (dbName.empty()) {
        std::cerr << "Error: No database name provided.\n";
    }
    else {
        std::string path = "D:/";
        if(createFolder(path,dbName)){
            std::cout << "database Created . "  << std::endl;
            std::cout << "Info: Use the command 'use " << dbName << "' to access the database." << std::endl;
            createEncryptedConfigFile(path+'/' + dbName, "config", dbName);
        }
        // You can call a function to create the DB with dbName
    }
    }
    

bool createFolder(const std::string& path, const std::string& folderName) {
    // Construct the full path by combining the path and folder name
  
    std::filesystem::path fullPath = std::filesystem::path(path) / folderName;

    try {
        // Check if the directory already exists
        if (std::filesystem::exists(fullPath)) {
            std::cout << "database already exists: " << fullPath << std::endl;
            return false;
        }

        // Create the directory and check if it was successful
        if (std::filesystem::create_directory(fullPath)) {
            return true;
        }
        else {
            std::cout << "Failed to create database: " << fullPath << std::endl;
            return false;
        }
    }
    catch (const std::filesystem::filesystem_error & e) {
        std::cerr << "Filesystem error: " << e.what() << std::endl;
        return false;
    }
}




