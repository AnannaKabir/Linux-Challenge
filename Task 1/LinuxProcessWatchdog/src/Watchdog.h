#ifndef WATCHDOG_H
#define WATCHDOG_H

#include <vector>
#include <string>
#include <thread>
#include <nlohmann/json.hpp>

struct Process {
    std::string name;
    std::string startup_parameters;
};

class Watchdog {
public:
    Watchdog(const std::string& configFileName);
    ~Watchdog();

    void start();

private:
    std::string configFileName;
    std::vector<Process> processes;
    std::thread watcherThread;

    void loadConfiguration();
    void startProcess(const Process& process);
    bool isProcessRunning(const std::string& processName);
    void monitorProcesses();
    void watchConfigurationFile();

    static void logEvent(const std::string& message);
};

#endif // WATCHDOG_H
