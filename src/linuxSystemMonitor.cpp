#include "linuxSystemMonitor.hpp"

#include <sys/statvfs.h>

#include <fstream>
#include <sstream>
#include <string>

namespace linuxSystemMonitor {

// Global paths for the files
const std::string PROC_STAT_PATH = "/proc/stat";
const std::string PROC_MEMINFO_PATH = "/proc/meminfo";
const std::string DEFAULT_DISK_PATH = "/";

// **CPU Information**
// Read the CPU data from /proc/stat
CpuStats readCpuData() {
    CpuStats result;
    std::ifstream procStat(PROC_STAT_PATH);

    if (procStat.good()) {
        std::string line;
        getline(procStat, line);

        unsigned int* statsPointer = (unsigned int*)&result;
        std::stringstream iss(line);
        std::string cpu;
        iss >> cpu;
        while (iss >> *statsPointer) {
            statsPointer++;
        };
    }

    procStat.close();
    return result;
}

// Get the total idle and active time
int CpuStats::getTotalIdle() const {
    return idle + iowait;
}
int CpuStats::getTotalActive() const {
    return user + nice + system + irq + softirq + steal + guest + guest_nice;
}

// Calculate the CPU usage
float getCpuUsage(const CpuStats& first, const CpuStats& second) {
    int activeTime = second.getTotalActive() - first.getTotalActive();
    int idleTime = second.getTotalIdle() - first.getTotalIdle();
    int totalTime = activeTime + idleTime;
    return static_cast<float>(activeTime) / totalTime;
}

// **Memory Information**
// Read the memory data from /proc/meminfo
MemoryStats readMemoryData() {
    MemoryStats result;
    std::ifstream procMeminfo(PROC_MEMINFO_PATH);

    if (procMeminfo.good()) {
        std::string line;
        for (int i = 0; i < 17; ++i) {
            getline(procMeminfo, line);
            std::stringstream iss(line);
            std::string key;
            int value;
            iss >> key >> value;
            if (key == "MemTotal:") {
                result.totalMemory = value;
            } else if (key == "MemAvailable:") {
                result.availableMemory = value;
            } else if (key == "SwapTotal:") {
                result.totalSwap = value;
            } else if (key == "SwapFree:") {
                result.freeSwap = value;
            }
        }
    }
    procMeminfo.close();
    return result;
}

// Calculate the memory usage
float MemoryStats::getMemoryUsage() const {
    return static_cast<float>(totalMemory - availableMemory) / totalMemory;
}

// Calculate the swap usage
float MemoryStats::getSwapUsage() const {
    return static_cast<float>(totalSwap - freeSwap) / totalSwap;
}

// **Disk Information**
// Read the disk data from the specified path
DiskStats readDiskData() {
    DiskStats result;
    struct statvfs diskData;
    if (statvfs(DEFAULT_DISK_PATH.c_str(), &diskData) == 0) {
        // calculate total and free space in MB
        unsigned long int totalSpace = diskData.f_blocks * diskData.f_frsize / 1024 / 1024;
        unsigned long int freeSpace = diskData.f_bfree * diskData.f_frsize / 1024 / 1024;
        result.totalSpace = totalSpace;
        result.freeSpace = freeSpace;
    }
    return result;
}

// Calculate the disk usage
float getDiskUsage(const DiskStats& disk) {
    return static_cast<float>(disk.totalSpace - disk.freeSpace) / disk.totalSpace;
}

}  // namespace linuxSystemMonitor
