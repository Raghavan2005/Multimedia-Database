#include "Query_Engine.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "Auth.h"
#include "ProductInfo.h"
#include "cmd_Create.h"
#include "CMD_Manipulation.h"
#include "cmd_Use.h"
#include "cmd_drop.h"
#include "globals.h"

const std::string query_list[9] = { "create", "drop", "use", "showpools","export","help","exit()","credits","insertmedia"}; //main cmd


void start_process_cmd(const std::string& command) {

    query_Selector(toLowerCase(command));
	
    


}

void query_Selector(const std::string& command) {
    std::istringstream stream(command);
    std::string cmd;
    std::string subquery;
    stream >> cmd; 

    if (cmd == query_list[0]) {
     
        //std::cout << query_list[0] << std::endl;
        process_create_command(command);
       //create
    }
    else if (cmd == query_list[1]) {
        process_drop_command(command);        //drop

    }
    else if (cmd == query_list[2]) {
        process_use_command(command);
        //use

    }
    else if (cmd == query_list[3]) {
        process_showpools_command();
        //rename -- show

    }
    else if (cmd == query_list[4]) {
        std::cout << "Unknown command: " << "comming soon" << std::endl;
        //export

    }
    else if (cmd == query_list[5]) {
        std::cout << "I can't help you now , this project still in development hehee" << std::endl;
        //export

    }
    else if (cmd == query_list[6] || cmd == "exit") {
 

        
            std::cout << "Exiting the program..." << std::endl;
            exit(0);  
        
        
        //exit

    }
    else if (cmd == query_list[7]) {
        std::cout << "@Raghavan , Still in Development \n Profile : https://github.com/Raghavan2005" << std::endl;
        
        //credits

    }
    else if (cmd == query_list[8]) {
        process_insertmedia_command(command);
        //insert

    }
    else {
        std::cout << "Unknown command: " << command << std::endl;
    }

}

//insert



void process_insertmedia_command(const std::string& command) {
    std::istringstream stream(command);
    std::string subCommand;

    // Extract the main command ("insertmedia")
    stream >> subCommand;
    if (subCommand != "insertmedia") {
        std::cerr << "Invalid command: Expected 'insertmedia' at the start.\n";
        return;
    }

    // Extract the pool name
    std::string poolName;
    stream >> poolName;
    if (poolName.empty()) {
        std::cerr << "Error: No pool name provided.\n";
        return;
    }

    // Extract the media file path (should be enclosed in double quotes)
    // Extract the media file path (allow parentheses or double quotes)
    std::string mediaFilePath;
    std::getline(stream, mediaFilePath);

    // Trim leading and trailing spaces
    mediaFilePath.erase(0, mediaFilePath.find_first_not_of(" \t"));
    mediaFilePath.erase(mediaFilePath.find_last_not_of(" \t") + 1);

    // Check if media path is enclosed in double quotes or parentheses
    if ((mediaFilePath.front() == '"' && mediaFilePath.back() == '"') ||
        (mediaFilePath.front() == '(' && mediaFilePath.back() == ')')) {
        // Remove the enclosing characters (either double quotes or parentheses)
        mediaFilePath = mediaFilePath.substr(1, mediaFilePath.size() - 2);
    }
    else {
        std::cerr << "Error: Media file path must be enclosed in double quotes or parentheses.\n";
        return;
    }


    // Remove the double quotes from the file path
    mediaFilePath = mediaFilePath.substr(1, mediaFilePath.size() - 2);

    // Ensure a database is currently in use
    if (activeDatabase.empty()) {
        std::cerr << "Error: No active database. Use the 'use <dbname>' command to activate a database before inserting media.\n";
        return;
    }

    // Construct the path to the target pool directory
    std::string poolPath = "D:/testfolder/" + activeDatabase + "/" + poolName;

    // Check if the pool directory exists
    if (!std::filesystem::exists(poolPath)) {
        std::cerr << "Error: Pool '" << poolName << "' does not exist in the active database.\n";
        return;
    }

    // Check if the media file exists
    if (!std::filesystem::exists(mediaFilePath)) {
        std::cerr << "Error: Media file '" << mediaFilePath << "' does not exist.\n";
        return;
    }

    // Copy the media file to the pool directory
    try {
        std::filesystem::path sourceFile(mediaFilePath);
        std::filesystem::path destinationFile = poolPath / sourceFile.filename();

        // Check if a file with the same name already exists in the pool
        if (std::filesystem::exists(destinationFile)) {
            std::cerr << "Error: A file with the same name already exists in the pool.\n";
            return;
        }

        std::filesystem::copy_file(sourceFile, destinationFile);
        std::cout << "Media file '" << sourceFile.filename() << "' successfully inserted into pool '" << poolName << "'.\n";
    }
    catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << "\n";
    }
}



//show

void process_showpools_command() {
    // Ensure a database is currently in use
    if (activeDatabase.empty()) {
        std::cerr << "Error: No active database. Use the 'use <dbname>' command to activate a database before listing pools.\n";
        return;
    }

    // Construct the path to the active database folder
    std::string dbPath = "D:/testfolder/" + activeDatabase;

    // Check if the database folder exists
    if (!std::filesystem::exists(dbPath)) {
        std::cerr << "Error: Database '" << activeDatabase << "' does not exist.\n";
        return;
    }

    // Iterate over the subdirectories (pools) in the active database folder
    bool poolsFound = false;
    std::cout << "Pools in database '" << activeDatabase << "':\n";
    for (const auto& entry : std::filesystem::directory_iterator(dbPath)) {
        if (entry.is_directory()) {
            std::cout << " - " << entry.path().filename().string() << '\n';
            poolsFound = true;
        }
    }

    if (!poolsFound) {
        std::cout << "No pools found in the active database.\n";
    }
}