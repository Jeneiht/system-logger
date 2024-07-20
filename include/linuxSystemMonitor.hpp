#ifndef _LINUX_SYSTEM_MONITOR_HPP_
#define _LINUX_SYSTEM_MONITOR_HPP_
#include <string>

namespace linuxSystemMonitor {

// CPU Information
struct CpuStats {
    int user;
    int nice;
    int system;
    int idle;
    int iowait;
    int irq;
    int softirq;
    int steal;
    int guest;
    int guest_nice;

    int getTotalIdle() const;
    int getTotalActive() const;
};

// Memory Information
struct MemoryStats {
    int totalMemory;
    int availableMemory;
    int totalSwap;
    int freeSwap;

    float getMemoryUsage() const;
    float getSwapUsage() const;
};

struct DiskStats {
    // Disk space in MB
    int totalSpace;
    int freeSpace;
};

// Read the CPU data from /proc/stat
CpuStats readCpuData();

// Read the memory data from /proc/meminfo
MemoryStats readMemoryData();

// Read the disk data fro
DiskStats readDiskData();
float getCpuUsage(const CpuStats &first, const CpuStats &second);
float getDiskUsage(const DiskStats &disk);
}  // namespace linuxSystemMonitor

#endif  // _LINUX_SYSTEM_MONITOR_HPP_
