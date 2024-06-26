#ifndef LOGGER_H
#define LOGGER_H

#include <string>

class Logger {
public:
    static void logEvent(const std::string& message);
};

#endif // LOGGER_H
