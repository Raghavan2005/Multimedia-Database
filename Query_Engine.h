// Query_Engine.h
#ifndef Cmd_Create
#define Cmd_Create
#include <string>

void start_process_cmd(const std::string& command);

void query_Selector(const std::string& command);
void process_insertmedia_command(const std::string& command);
void process_showpools_command();
#endif // Query_Engine
