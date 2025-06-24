// Decoder_QE.h
#ifndef Decoder_QE
#define Decoder_QE
#include <string>

std::string xorEncryptDecrypt(const std::string& input );
bool readDecryptedConfigFile(const std::string& path, const std::string& fileName);
#endif // Decoder_QE
