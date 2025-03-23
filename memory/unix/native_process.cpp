#include "native_process.hpp"

namespace UNIX {
    size_t native_process::read_memory_raw(u64 address, void* buffer, size_t size, int length) {
        fseek(mem_file.get(), static_cast<long>(address), SEEK_SET);
        size_t read_result = fread(buffer, size, length, mem_file.get());
        fflush(mem_file.get());
        return read_result;
    }

    size_t native_process::write_memory_raw(u64 address, void* value, size_t size, int length) {
        fseek(mem_file.get(), static_cast<long>(address), SEEK_SET);
        size_t write_result = fwrite(value, size, length, mem_file.get());
        fflush(mem_file.get());
        return write_result;
    }
}
