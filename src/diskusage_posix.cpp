#include "diskusage.h"

#include <stdexcept>
#include <sys/statvfs.h>
#include <errno.h>
#include <string.h>

DiskUsage GetDiskUsage(const char* path)
{
    struct statvfs info = {};

    if (statvfs(path, &info)) {
        int errnum = errno;
        throw SystemError(errnum, "statvfs", strerror(errnum), path);
    }

    DiskUsage result;
    result.available = info.f_bavail * info.f_frsize;
    result.free = info.f_bfree * info.f_frsize;
    result.total = info.f_blocks * info.f_frsize;

    return result;
}
