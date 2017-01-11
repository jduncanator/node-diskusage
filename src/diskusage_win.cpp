#include "diskusage.h"

#include <stdexcept>
#include <Windows.h>

DiskUsage GetDiskUsage(const char* path)
{
    ULARGE_INTEGER available = {};
    ULARGE_INTEGER total = {};
    ULARGE_INTEGER free = {};

    if (!GetDiskFreeSpaceExA(path, &available, &total, &free)) {
        throw std::runtime_error("GetDiskFreeSpaceEx failed");
    }

    DiskUsage result;
    result.available = available.QuadPart;
    result.free = free.QuadPart;
    result.total = total.QuadPart;

    return result;
}
