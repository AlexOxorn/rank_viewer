//
// Created by alexoxorn on 3/17/25.
//

#include "unleashed_process.hpp"

namespace UNIX {
    size_t unleashed_process::read_memory_raw(u64 address, void* buffer, size_t size, int length) {
        if (address < unleashed_process::head) {
            address += unleashed_process::head;
        }
        fseek(mem_file.get(), static_cast<long>(address), SEEK_SET);
        size_t read_result = fread(buffer, size, length, mem_file.get());
        fflush(mem_file.get());
        return read_result;
    }
}