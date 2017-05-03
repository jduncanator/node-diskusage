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

static std::string Utf16ToUtf8(const char* wstr)
{
    int size = WideCharToMultiByte(CP_UTF8, 0, (LPCWSTR)wstr, -1, NULL, 0, NULL, NULL);
    if (!size) throw std::runtime_error("WideCharToMultiByte failed");

    std::string result;
    result.resize(size);

    size = WideCharToMultiByte(CP_UTF8, 0, (LPCWSTR)wstr, -1, (LPSTR)result.data(), result.size(), NULL, NULL);
    if (!size) throw std::runtime_error("WideCharToMultiByte failed");

    return result;
}

DiskUsage GetDiskUsage(const char* path)
{
    ULARGE_INTEGER available = {};
    ULARGE_INTEGER total = {};
    ULARGE_INTEGER free = {};

    if (!GetDiskFreeSpaceExW(Utf8ToUtf16(path).c_str(), &available, &total, &free)) {
        LPVOID lpMsgBuf;
        DWORD lastError = GetLastError(); 

        FormatMessage(
            FORMAT_MESSAGE_ALLOCATE_BUFFER | 
            FORMAT_MESSAGE_FROM_SYSTEM |
            FORMAT_MESSAGE_IGNORE_INSERTS,
            NULL,
            lastError,
            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
            (LPTSTR) &lpMsgBuf,
            0, NULL);

        throw SystemError(lastError, "GetDiskFreeSpaceEx", Utf16ToUtf8((char*)lpMsgBuf), path);
    }

    DiskUsage result;
    result.available = available.QuadPart;
    result.free = free.QuadPart;
    result.total = total.QuadPart;

    return result;
}
