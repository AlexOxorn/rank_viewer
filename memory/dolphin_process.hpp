#pragma once

#include <exception>
#include <string>
#include <filesystem>
#include <cstdio>
#include <array>
#include <type_traits>
#include <iostream>
#include <sys/uio.h>
#include <fstream>
#include <ox/types.h>
#include <ox/bytes.h>

class dolphin_process {
    static constexpr u32 gc_memory_start = 0x80000000;
    int pid;
    u64 emu_ram_address = 0;
    u64 mem2_address = 0;
    bool mem2_present = false;
    FILE *mem_file = nullptr;
public:
    dolphin_process(int _pid);

    ~dolphin_process() {
        if (mem_file)
            fclose(mem_file);
    }

    bool read_memory(u64 address, u8* buffer, size_t size, int length, bool byte_swap) const;

    template<typename T> requires std::is_trivially_copyable_v<T>
    bool read_memory(u64 address, T* result, int length = 1) {
        if (address > 0x80000000) {
            address -= 0x80000000;
        }
        int seek_res = fseek(mem_file, emu_ram_address + address, SEEK_SET);
        int read_res = fread(result, sizeof(T), length, mem_file);
        if constexpr (std::is_integral_v<T>) {
            for (int i = 0; i < length; i++) {
                ox::swap(result + i);
            }
        }
        return read_res != length;
    }

    template<typename T, std::size_t N> requires std::is_trivially_copyable_v<T>
    bool read_memory(u64 address, std::array<T, N>* result) {
        if (address > 0x80000000) {
            address -= 0x80000000;
        }
        int seek_res = fseek(mem_file, emu_ram_address + address, SEEK_SET);
        int read_res = fread(result, sizeof(T), N, mem_file);
        if constexpr (std::is_integral_v<T>) {
            for (auto& a : *result) {
                ox::swap(&a);
            }
        }
        return read_res != N;
    }

    bool write_memory(u64 address, u8 value, int length);
};
