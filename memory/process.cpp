#include "process.hpp"

size_t process::read_memory_raw(u64 address, void* buffer, size_t size, int length) {
    mem_file.seek(address, SEEK_SET);
    size_t read_result = mem_file.read(buffer, size, length);
    fflush(mem_file);
    return read_result;
}

size_t process::write_memory_raw(u64 address, void* value, size_t size, int length) {
    mem_file.seek(address, SEEK_SET);
    size_t write_result = mem_file.write(value, size, length);
    mem_file.flush();
    return write_result;
}
