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
#include <fcntl.h>

class process {
protected:
    int pid;
    std::filesystem::path proc_dir;
    std::filesystem::path mem_path;

    FILE *mem_file;
public:
    process(int _pid) : pid{_pid} {
        proc_dir = std::filesystem::path{"/proc"};
        proc_dir /= std::to_string(pid);
        mem_path = proc_dir / "mem";

        mem_file = fopen(mem_path.c_str(), "r+b");
    }

    process(const process& p) = delete;
    process& operator=(const process& p) = delete;

    virtual ~process() {
        int result = fclose(mem_file);
    }

    virtual bool read_memory(s64 address, void* buffer, size_t size, int length, bool byte_swap = false) const;
    virtual bool write_memory(s64 address, void* value, size_t size, int length, bool byte_swap = false) const;

    template<typename T> requires std::is_trivially_copyable<T>::value
    bool read_memory(s64 address, T* result) {
        return this->read_memory(address, result, sizeof(T), 1);
    }

    template<typename T, std::size_t N> requires std::is_trivially_copyable<T>::value
    bool read_memory(s64 address, std::array<T, N>* result) {
        return this->read_memory(address, result->data(), sizeof(T), N);
    }

    template<typename T> requires std::is_trivially_copyable<T>::value
    bool write_memory(s64 address, T* result) {
        return this->write_memory(address, result, sizeof(T), 1);
    }

    template<typename T, std::size_t N> requires std::is_trivially_copyable<T>::value
    bool write_memory(s64 address, std::array<T, N>* result) {
        return this->write_memory(address, result->data(), sizeof(T), N);
    }
};
