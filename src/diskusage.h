#pragma once

#include <cstdint>

struct DiskUsage {
    uint64_t available;
    uint64_t free;
    uint64_t total;
};

DiskUsage GetDiskUsage(const char* path);
