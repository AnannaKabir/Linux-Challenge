#ifndef NATIVE_OS_API_H
#define NATIVE_OS_API_H

#include <string>

class NativeOSAPI {
public:
    static bool isProcessRunning(const std::string& processName);
    static void startProcess(const std::string& processName, const std::string& startupParameters);
};

#endif // NATIVE_OS_API_H
