#include "native_os_api.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <cstdlib>

bool NativeOSAPI::isProcessRunning(const std::string& processName) {
    std::string command = "pgrep " + processName + " > /dev/null 2>&1";
    return system(command.c_str()) == 0;
}

void NativeOSAPI::startProcess(const std::string& processName, const std::string& startupParameters) {
    pid_t pid = fork();
    if (pid == 0) {
        execlp(processName.c_str(), processName.c_str(), startupParameters.c_str(), NULL);
        exit(EXIT_FAILURE);
    }
}
