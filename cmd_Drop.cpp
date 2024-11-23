#include <iostream>
#include <string>
#include <filesystem> // For folder and file management
#include <sstream>
#include <string>         
#include <fstream>

#include "cmd_drop.h"

namespace fs = std::filesystem;

// Function to delete a folder
bool deleteFolder(const std::string& path) {
    try {
        if (fs::exists(path) && fs::is_directory(path)) {
            fs::remove_all(path); // Recursively deletes the folder and its contents
            return true;
        }
        else {
            std::cerr << "Error: Path does not exist or is not a directory.\n";
            return false;
        }
    }
    catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << '\n';
        return false;
    }
}

// Function to process the "drop" command
void process_drop_command(const std::string& command) {
    std::istringstream stream(command);
    std::string subCommand;
    std::string path = "D:/testfolder";

    // Extract the main command ("drop")
    stream >> subCommand;
    if (subCommand != "drop") {
        std::cerr << "Invalid command: Expected 'drop' at the start.\n";
        return;
    }

    // Extract the sub-type ("db" or "pool")
    std::string subType;
    stream >> subType;
    if (subType != "db" && subType != "pool") {
        std::cerr << "Invalid sub-command: Expected 'db' or 'pool' after 'drop'.\n";
        return;
    }

    // Extract the name of the database or pool
    std::string name;
    stream >> name;

    // Validate if the name is provided
    if (name.empty()) {
        std::cerr << "Error: No name provided for the " << subType << ".\n";
        return;
    }

    // Construct the path to delete
    std::string targetPath = path + '/' + name;

    if (subType == "db") {
        // Drop the database
        if (deleteFolder(targetPath)) {
            std::cout << "Database '" << name << "' dropped successfully.\n";
        }
    }
    else if (subType == "pool") {
        // Check if an active database is set
        extern std::string activeDatabase; // Assuming activeDatabase is defined elsewhere
        if (activeDatabase.empty()) {
            std::cerr << "Error: No active database. Use the 'use <dbname>' command to activate a database before dropping a pool.\n";
            return;
        }

        // Drop the pool from the active database
        targetPath = path + '/' + activeDatabase + '/' + name;
        if (deleteFolder(targetPath)) {
            std::cout << "Pool '" << name << "' dropped successfully from database '" << activeDatabase << "'.\n";
        }
    }
}
