#include "diskusage.h"

#include <string>
#include <stdexcept>
#include <Windows.h>

static std::wstring Utf8ToUtf16(const char* str)
{
    int size = MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0);
    if (!size) throw std::runtime_error("MultiByteToWideChar failed");

    std::wstring result;
    result.resize(size);

    size = MultiByteToWideChar(CP_UTF8, 0, str, -1, (LPWSTR)result.data(), result.size());
    if (!size) throw std::runtime_error("MultiByteToWideChar failed");

    return result;
}

DiskUsage GetDiskUsage(const char* path)
{
    ULARGE_INTEGER available = {};
    ULARGE_INTEGER total = {};
    ULARGE_INTEGER free = {};

    if (!GetDiskFreeSpaceExW(Utf8ToUtf16(path).c_str(), &available, &total, &free)) {
        throw SystemError(GetLastError(), "GetDiskFreeSpaceEx", "GetDiskFreeSpaceEx failed", path);
    }

    DiskUsage result;
    result.available = available.QuadPart;
    result.free = free.QuadPart;
    result.total = total.QuadPart;

    return result;
}
