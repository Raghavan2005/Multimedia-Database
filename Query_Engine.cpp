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

const std::string query_list[5] = { "create", "drop", "use", "rename","export"}; //main cmd


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
        std::cout << query_list[1];
        //drop

    }
    else if (cmd == query_list[2]) {
        process_use_command(command);
        //use

    }
    else if (cmd == query_list[3]) {
        std::cout << query_list[3];
        //rename

    }
    else if (cmd == query_list[4]) {
        std::cout << query_list[4];
        //export

    }
    else {
        std::cout << "Unknown command: " << command << std::endl;
    }

}