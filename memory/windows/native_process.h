//
// Created by alexoxorn on 3/11/23.
//

#pragma once

#include <windows.h>
#include <cstdint>
#include <cstddef>
#include "../abstract_process.h"

namespace WINDOWS {
    class native_process : public abstract_process {
    public:
        explicit native_process(long _pid) : abstract_process(_pid), hProcess(NULL) {
            // Open the process with the specified PID for reading and writing
            hProcess = OpenProcess(PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION, FALSE, _pid);
        }

        ~native_process() {
            // Close the process handle when the object is destroyed
            if (hProcess != NULL) {
                CloseHandle(hProcess);
            }
        }

        native_process(const native_process& other) = delete;
        native_process& operator=(const native_process& other) = delete;

        size_t read_memory_raw(u64 address, void* buffer, size_t size, int length) override;
        size_t write_memory_raw(u64 address, void* value, size_t size, int length) override;

    private:
        HANDLE hProcess;
    };

} // namespace WINDOWS
