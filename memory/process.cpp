#include "process.hpp"
#include <ox/bytes.h>

bool process::read_memory_raw(i64 address, void* buffer, size_t size, int length, bool byte_swap) {
    mem_file.seek(address, SEEK_SET);
    int read_result = mem_file.read(buffer, size, length);
    fflush(mem_file);
    if(byte_swap) {
        ox::swap(buffer, size, read_result);
    }
    return read_result == length;
}

bool process::write_memory_raw(i64 address, void* value, size_t size, int length, bool byte_swap) {
    mem_file.seek(address, SEEK_SET);
    if(byte_swap) {
        ox::swap(value, size, length);
    }
    int write_result = mem_file.write(value, size, length);
    mem_file.flush();
    if(byte_swap) {
        ox::swap(value, size, length);
    }
    return write_result == length;
}
