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
#include "process.hpp"

class dolphin_process : public process {
    static constexpr u32 gc_memory_start = 0x80000000;
    int pid;
    u64 emu_ram_address = 0;
    u64 mem2_address = 0;
    bool mem2_present = false;
    FILE *mem_file = nullptr;
public:
    dolphin_process(int _pid);

    bool read_memory(s64 address, void* buffer, size_t size, int length, bool byte_swap = false) const override;
    bool write_memory(s64 address, void* buffer, size_t size, int length, bool byte_swap = false) const override;

    template<typename T> requires std::is_trivially_copyable_v<T>
    bool read_memory(u64 address, T* result) {
        return this->read_memory(address, result, sizeof(T), 1, ox::is_endianable_v<T>);
    }

    template<typename T, std::size_t N> requires std::is_trivially_copyable_v<T>
    bool read_memory(u64 address, std::array<T, N>* result) {
        bool valid_read = this->read_memory(address, result->data(), sizeof(T), N);
        if constexpr (ox::is_endianable_v<T>) {
            for(auto& a : *result) {
                ox::swap(&a);
            }
        }
        return valid_read;
    }

    template<typename T> requires std::is_trivially_copyable_v<T>
    bool write_memory(u64 address, T* result) {
        return this->write_memory(address, result, sizeof(T), 1, ox::is_endianable_v<T>);
    }

    template<typename T, std::size_t N> requires std::is_trivially_copyable_v<T>
    bool write_memory(u64 address, std::array<T, N>* result) {
        if constexpr (ox::is_endianable_v<T>) {
            for(auto& a : *result) {
                ox::swap(&a);
            }
        }
        bool valid_read = this->write_memory(address, result->data(), sizeof(T), N);
        return valid_read;
    }
};
