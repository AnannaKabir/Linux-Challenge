# Linux Process Watchdog

This repository contains a Linux Process Watchdog program written in C++. The program monitors and ensures that specified processes are always running on a Linux system. It can dynamically reload its configuration when changes are detected in the configuration file.

## Table of Contents
- [Features](#features)
- [Dependencies](#dependencies)
- [Installation](#installation)
- [Usage](#usage)
- [Configuration](#configuration)
- [Logging](#logging)
- [Contributing](#contributing)
- [License](#license)

## Features
- Monitors specified processes to ensure they are always running.
- Automatically starts processes if they are not running.
- Dynamically reloads configuration when changes are detected in the configuration file.
- Logs meaningful events and actions to a log file.

## Dependencies
- C++17 or higher
- [nlohmann/json](https://github.com/nlohmann/json) (JSON for Modern C++)
- A Linux-based operating system

## Installation

1. **Clone the Repository**
    ```sh
    git clone https://github.com/yourusername/linux-process-watchdog.git
    cd linux-process-watchdog
    ```

2. **Install Dependencies**
    Ensure you have `nlohmann/json` installed. You can install it via your package manager or by including the single-header file in your project.

    For example, on Ubuntu:
    ```sh
    sudo apt-get install nlohmann-json3-dev
    ```

3. **Compile the Program**
    ```sh
    g++ -std=c++17 src/main.cpp src/Watchdog.cpp src/logger.cpp src/native_os_api.cpp -o watchdog -linotify
    ```

4. **Run the Program**
    ```sh
    ./watchdog
    ```

## Configuration
The configuration file `config.json` contains the list of processes to be monitored and their startup parameters. Example:

```json
{
  "processes": [
    {
      "name": "Process1",
      "startup_parameters": "param1 param2"
    },
    {
      "name": "Process2",
      "startup_parameters": "param3 param4"
    }
  ]
}
