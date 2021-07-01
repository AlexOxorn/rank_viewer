#include "process.hpp"

bool process::read_memory(u32 address, u8* buffer, size_t size, int length, bool byte_swap) {
    fseek(mem_file, address, SEEK_SET);
    int read_result = fread(buffer, size, length, mem_file);
    if(byte_swap) {
        for(int i = 0; i < read_result; i++) {
            switch(size) {
            case sizeof(u16):
                ox::swap(reinterpret_cast<u16*>(buffer) + i);
                break;
            case sizeof(u32):
                ox::swap(reinterpret_cast<u32*>(buffer) + i);
                break;
            case sizeof(u64):
                ox::swap(reinterpret_cast<u64*>(buffer) + i);
                break;
            }
        }
    }
    return read_result == length;
}
