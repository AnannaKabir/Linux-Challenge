#include "Watchdog.h"
#include <fstream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/inotify.h>
#include <ctime>
#include <sstream>
#include <iostream>

using json = nlohmann::json;

Watchdog::Watchdog(const std::string& configFileName)
    : configFileName(configFileName) {
    loadConfiguration();
}

Watchdog::~Watchdog() {
    if (watcherThread.joinable()) {
        watcherThread.join();
    }
}

void Watchdog::start() {
    watcherThread = std::thread(&Watchdog::watchConfigurationFile, this);
    while (true) {
        monitorProcesses();
        sleep(10); // Check every 10 seconds
    }
}

void Watchdog::loadConfiguration() {
    logEvent("Loading configuration file: " + configFileName);
    std::ifstream file(configFileName);
    json config;
    file >> config;
    processes.clear();
    for (const auto& item : config["processes"]) {
        processes.push_back({item["name"], item["startup_parameters"]});
    }
    logEvent("Configuration loaded successfully");
}

void Watchdog::startProcess(const Process& process) {
    logEvent("Starting process: " + process.name + " with parameters: " + process.startup_parameters);
    pid_t pid = fork();
    if (pid == 0) {
        execlp(process.name.c_str(), process.name.c_str(), process.startup_parameters.c_str(), NULL);
        exit(EXIT_FAILURE);
    }
    logEvent("Process started: " + process.name);
}

bool Watchdog::isProcessRunning(const std::string& processName) {
    logEvent("Checking if process is running: " + processName);
    std::string command = "pgrep " + processName + " > /dev/null 2>&1";
    return system(command.c_str()) == 0;
}

void Watchdog::monitorProcesses() {
    for (const auto& process : processes) {
        if (!isProcessRunning(process.name)) {
            startProcess(process);
        }
    }
}

void Watchdog::watchConfigurationFile() {
    logEvent("Watching configuration file for changes: " + configFileName);
    int fd = inotify_init();
    if (fd < 0) {
        perror("inotify_init");
        exit(EXIT_FAILURE);
    }

    int wd = inotify_add_watch(fd, configFileName.c_str(), IN_MODIFY);
    if (wd == -1) {
        perror("inotify_add_watch");
        exit(EXIT_FAILURE);
    }

    char buffer[1024];
    while (true) {
        int length = read(fd, buffer, 1024);
        if (length < 0) {
            perror("read");
        }

        logEvent("Configuration file modified, reloading...");
        loadConfiguration();
        monitorProcesses();
    }

    inotify_rm_watch(fd, wd);
    close(fd);
}

void Watchdog::logEvent(const std::string& message) {
    std::ofstream logFile("watchdog.log", std::ios_base::app);
    std::time_t now = std::time(nullptr);
    logFile << std::ctime(&now) << ": " << message << std::endl;
}
