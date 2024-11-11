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

const std::string query_list[8] = { "create", "drop", "use", "rename","export","help","exit()","credits"}; //main cmd


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
        std::cout << "Unknown command: " << "comming soon" << std::endl;
        //drop

    }
    else if (cmd == query_list[2]) {
        process_use_command(command);
        //use

    }
    else if (cmd == query_list[3]) {
        std::cout << "Unknown command: " << "comming soon" << std::endl;
        //rename

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
    else {
        std::cout << "Unknown command: " << command << std::endl;
    }

}