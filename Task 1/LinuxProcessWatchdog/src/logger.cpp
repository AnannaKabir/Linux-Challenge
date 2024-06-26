#include "logger.h"
#include <fstream>
#include <ctime>

void Logger::logEvent(const std::string& message) {
    std::ofstream logFile("watchdog.log", std::ios_base::app);
    std::time_t now = std::time(nullptr);
    logFile << std::ctime(&now) << ": " << message << std::endl;
}
