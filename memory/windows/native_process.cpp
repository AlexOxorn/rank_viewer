//
// Created by alexoxorn on 3/11/23.
//

#include "native_process.h"

namespace WINDOWS {
    size_t native_process::read_memory_raw(u64 address, void* buffer, size_t size, int length) {
        SIZE_T bytesRead;
        BOOL result = ReadProcessMemory(hProcess, reinterpret_cast<LPCVOID>(address), buffer, size, &bytesRead);
        return result ? bytesRead : 0;
    }

    size_t native_process::write_memory_raw(u64 address, void* value, size_t size, int length) {
        SIZE_T bytesWritten;
        BOOL result = WriteProcessMemory(hProcess, reinterpret_cast<LPVOID>(address), value, size, &bytesWritten);
        return result ? bytesWritten : 0;
    }
} // namespace WINDOWS