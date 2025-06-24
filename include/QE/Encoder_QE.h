// Encoder_QE.h
#ifndef Encoder_QE
#define Encoder_QE
#include <string>

std::string xorEncryptDecrypt(const std::string& input, char key );
std::string generateId();
bool createEncryptedConfigFile(const std::string& path, const std::string& fileName, std::string& mdbname);
#endif // Encoder_QE
