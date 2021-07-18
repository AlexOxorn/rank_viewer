#include "process.hpp"

int process::read_memory_raw(i64 address, void* buffer, size_t size, int length) {
    mem_file.seek(address, SEEK_SET);
    int read_result = mem_file.read(buffer, size, length);
    fflush(mem_file);
    return read_result;
}

int process::write_memory_raw(i64 address, void* value, size_t size, int length) {
    mem_file.seek(address, SEEK_SET);
    int write_result = mem_file.write(value, size, length);
    mem_file.flush();
    return write_result;
}
