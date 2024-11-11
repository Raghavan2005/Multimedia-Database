#include <iostream>
#include <string>
#include <limits>
#include "Auth.h"
#include "ProductInfo.h"

#ifdef _WIN32
#include <conio.h>  // For Windows hidden input
#else
#include <termios.h>  // For Linux/macOS hidden input
#include <unistd.h>
#endif

// Helper function to read a password without showing characters on screen
std::string getPassword() {
    std::string passwordInput;
    char ch;

#ifdef _WIN32
    while ((ch = _getch()) != '\r') {  // '\r' is Enter on Windows
        if (ch == '\b' && !passwordInput.empty()) {  // Handle backspace
            passwordInput.pop_back();
            std::cout << "\b \b";
        }
        else if (ch != ' ' && ch != '\r') {  // Ignore spaces and enter
            passwordInput += ch;
            std::cout << '*';
        }
    }
#else
    // POSIX (Linux/macOS) - Disable terminal echo for password input
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);  // Get current terminal attributes
    newt = oldt;
    newt.c_lflag &= ~ECHO;           // Turn off echo
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    while ((ch = getchar()) != '\n') {  // '\n' is Enter on Linux/macOS
        if ((ch == '\b' || ch == 127) && !passwordInput.empty()) {  // Handle backspace
            passwordInput.pop_back();
            std::cout << "\b \b";
        }
        else if (ch != ' ' && ch != '\n') {  // Ignore spaces and enter
            passwordInput += ch;
            std::cout << '*';
        }
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);  // Restore terminal settings
#endif

    std::cout << std::endl;
    return passwordInput;
}

bool password_Check() {
    std::string inputPassword;
    
    do {
        std::cout << "Enter password: ";
        inputPassword = getPassword();

        if (inputPassword.empty()) {
            std::cout << "Password cannot be empty. Please try again.\n";
        }
    } while (inputPassword.empty());

    return inputPassword == password;
}

void start_CheckAuth() {
    while (!password_Check()) {
        std::cout << "Incorrect password. Please try again.\n";
    }
}
