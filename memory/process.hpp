#pragma once

#include <exception>
#include <string>
#include <filesystem>
#include <cstdio>
#include <array>
#include <type_traits>
#include <iostream>
#include <ox/types.h>
#include <ox/bytes.h>

class process {
    int pid;
    std::filesystem::path proc_dir;
    std::filesystem::path mem_path;

    FILE *mem_file;
public:
    process(int _pid) : pid{_pid} {
        proc_dir = std::filesystem::path{"/proc"};
        proc_dir /= std::to_string(pid);
        mem_path = proc_dir / "mem";

        mem_file = fopen(mem_path.c_str(), "rb");
    }

    ~process() {
        int result = fclose(mem_file);
    }

    bool read_memory(u32 address, u8* buffer, size_t size, int length, bool byte_swap);

    template<typename T> requires std::is_trivially_copyable<T>::value
    bool read_memory(long address, T* result, int length = 1) {
        int seek_res = fseek(mem_file, address, SEEK_SET);
        int read_res = fread(result, sizeof(T), length, mem_file);
        return read_res != length;
    }

    template<typename T, std::size_t N> requires std::is_trivially_copyable<T>::value
    bool read_memory(long address, std::array<T, N>* result, int length = N) {
        int seek_res = fseek(mem_file, address, SEEK_SET);
        int read_res = fread(result, sizeof(T), length, mem_file);
        return read_res != length;
    }
};
