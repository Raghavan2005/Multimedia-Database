// SystemInfo.cpp
#include "SystemInfo.h"
#include <sstream>

#ifdef _WIN32
#include <windows.h>

std::string getSystemInfo() {
    SYSTEM_INFO sysInfo;
    GetSystemInfo(&sysInfo);

    MEMORYSTATUSEX memoryStatus;
    memoryStatus.dwLength = sizeof(memoryStatus);
    GlobalMemoryStatusEx(&memoryStatus);

    std::ostringstream oss;
    oss << "OS_Windows";
    oss << "-ARCH-" << sysInfo.wProcessorArchitecture;
    oss << "-MEM-" << memoryStatus.ullAvailPhys / (1024 * 1024) << " MB";

    return oss.str();
}

#else
#include <sys/sysinfo.h>
#include <unistd.h>

std::string getSystemInfo() {
    struct sysinfo info;
    sysinfo(&info);

    std::ostringstream oss;
    oss << "OS_Unix/Linux";
    oss << "-MEM-" << info.freeram / (1024 * 1024) << " MB";


    return oss.str();
}
#endif
