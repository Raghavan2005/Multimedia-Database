// cmd_Create.h
#ifndef cmd_Create
#define cmd_Create
#include <string>

void process_create_command(const std::string& command);
bool createFolder(const std::string& path, const std::string& folderName);
bool createMdbFile(const std::string& path, const std::string& fileName);
#endif // cmd_Create
#pragma once
