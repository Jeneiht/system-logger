#include <chrono>
#include <ctime>
#include <fstream>
#include <iostream>
#include <thread>

#include "linuxSystemMonitor.hpp"

const std::chrono::minutes LOG_INTERVAL(5);
const std::string LOG_FILE_PATH = "/var/log/system-usage.log";

// Function to get the current time as a string
std::string getCurrentTime() {
    std::time_t now = std::time(nullptr);
    char timeStr[100];
    std::strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
    return std::string(timeStr);
}

// Function to log system usage information
void logSystemUsage() {
    // Get initial CPU stats
    auto cpu1 = linuxSystemMonitor::readCpuData();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    // Get CPU stats again after 1 second
    auto cpu2 = linuxSystemMonitor::readCpuData();
    // Calculate CPU usage
    float cpuUsage = linuxSystemMonitor::getCpuUsage(cpu1, cpu2) * 100.0f;

    // Get memory statistics
    auto memStats = linuxSystemMonitor::readMemoryData();
    float memoryUsage = memStats.getMemoryUsage() * 100.0f;
    float swapUsage = memStats.getSwapUsage() * 100.0f;

    // Get disk statistics
    auto diskStats = linuxSystemMonitor::readDiskData();
    float diskUsage = linuxSystemMonitor::getDiskUsage(diskStats) * 100.0f;

    // Open the log file and append the system usage information
    std::ofstream logFile(LOG_FILE_PATH, std::ios_base::app);
    if (logFile.is_open()) {
        logFile << "[" << getCurrentTime() << "] "
                << "CPU Usage: " << cpuUsage << "%, "
                << "Memory Usage: " << memoryUsage << "%, "
                << "Swap Usage: " << swapUsage << "%, "
                << "Disk Usage: " << diskUsage << "%" << std::endl;
        logFile.close();  // Đóng file sau khi ghi
    } else {
        std::cerr << "Error opening log file: " << LOG_FILE_PATH << std::endl;
    }
}

int main() {
    // Continuously log system usage every LOG_INTERVAL
    while (true) {
        logSystemUsage();
        std::this_thread::sleep_for(LOG_INTERVAL);
    }
    return 0;
}
