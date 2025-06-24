#include "QE/CMD_Manipulation.h"
#include <iostream>
#include <string>
#include <cctype>  // For std::tolower

// Function to convert a string to lowercase
std::string toLowerCase(const std::string& input) {
    std::string result = input;  
    for (char& c : result) {
        c = std::tolower(static_cast<unsigned char>(c));  // Convert each character to lowercase
    }
    return result;
}

#include <algorithm>

// Function to remove all occurrences of a substring from a sentence
std::string removeSubstring(const std::string& sentence, const std::string& target) {
    std::string result = sentence;
    size_t pos = 0;

    // Search for the target substring and erase it from the result
    while ((pos = result.find(target, pos)) != std::string::npos) {
        result.erase(pos, target.length());
    }

    return result;
}