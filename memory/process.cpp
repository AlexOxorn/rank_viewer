#include "process.hpp"

bool process::read_memory(s64 address, void* buffer, size_t size, int length, bool byte_swap) const {
    fseek(mem_file, address, SEEK_SET);
    int read_result = fread(buffer, size, length, mem_file);
    if(byte_swap) {
        ox::swap(buffer, size, read_result);
    }
    return read_result == length;
}

bool process::write_memory(s64 address, void* value, size_t size, int length, bool byte_swap) const {
    int seek_res = fseek(mem_file, address, SEEK_SET);
    if(byte_swap) {
        ox::swap(value, size, length);
    }
    int write_result = fwrite(value, size, length, mem_file);
    if(byte_swap) {
        ox::swap(value, size, length);
    }
    return write_result == length;
}
