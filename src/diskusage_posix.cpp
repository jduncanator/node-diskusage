#include "diskusage.h"

#include <stdexcept>
#include <sys/statvfs.h>
#include <errno.h>

DiskUsage GetDiskUsage(const char* path)
{
    struct statvfs info = {};

    if (statvfs(path, &info)) {
        throw SystemError(errno, "statvfs", "statvfs failed", path);
    }

    DiskUsage result;
    result.available = info.f_bavail * info.f_frsize;
    result.free = info.f_bfree * info.f_frsize;
    result.total = info.f_blocks * info.f_frsize;

    return result;
}
