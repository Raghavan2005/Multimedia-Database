#include <iostream>
#include <limits>
#include "QE/SystemInfo.h"
#include "QE/ProductInfo.h"
#include "src/MDB_Engine/Auth.cpp"
#include "QE/Query_Engine.h"
#include <stdlib.h>
#include "QE/globals.h"


std::string activeDatabase = "";
int main() {
    

    std::string systemInfo = getSystemInfo();
    std::cout << productName << " (tags / " << version << ":" << type << " Nov 7 2024, 7:30:53) [" << systemInfo << "]\n";
    std::cout << "Copyright by " << owner;
    std::cout << "\nType 'help', 'credits', or 'license' for more information.\n";
    std::cout << "https://github.com/Raghavan2005/Multimedia-Database\n";
    start_CheckAuth();
    std::string userInput;

  
   

    while (true) {
        std::cout << ">>> ";
        std::getline(std::cin, userInput); 
        //std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        start_process_cmd(userInput);
        //std::cout << "You entered: " << userInput << "\n";
    }

    return 0;
}
