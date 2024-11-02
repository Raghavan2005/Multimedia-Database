// MDB.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include "SystemInfo.h"
#include "ProductInfo.h"



int main() {
    std::string systemInfo = getSystemInfo();
 
    std::cout << productName <<" (tags / "<< version<<":"<< type<< " Nov  7 2024, 7 : 30 : 53)["<<systemInfo<<"] \n";
    std::cout << "copyright by " << owner;
    std::cout << "\nType 'help', 'credits', or 'license' for more information.\n";
   
    while (true) {
      //  std::cin >> choice;
        std::cout << ">>> ";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    }
    return 0;
}
