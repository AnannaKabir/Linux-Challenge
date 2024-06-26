#include "Watchdog.h"

int main() {
    std::string configFileName = "config.json";
    Watchdog watchdog(configFileName);
    watchdog.start();
    return 0;
}