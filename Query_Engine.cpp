#include "Query_Engine.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "Auth.h"
#include "ProductInfo.h"
#include "Cmd_Create.h"
#include "CMD_Manipulation.h"

const std::string query_list[5] = { "create", "drop", "use", "rename","export"}; //main cmd


void start_process_cmd(const std::string& command) {
	//create db
    query_Selector(toLowerCase(command));
	//use db
    
    //drop db

	//rename db

	//export meta json
    

}

void query_Selector(const std::string& command) {
    std::istringstream stream(command);
    std::string cmd;
    stream >> cmd; 

    if (cmd == query_list[0]) {
        std::cout << "Creating database..." << std::endl;
        std::cout << query_list[0] << std::endl;
       // process_Create_Command();
       //create
    }
    else if (cmd == query_list[1]) {
        std::cout << query_list[1];
        //drop

    }
    else if (cmd == query_list[2]) {
        std::cout << query_list[2];
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