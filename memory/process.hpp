#pragma once

#include <filesystem>
#include <array>
#include <type_traits>
#include <ox/file.h>
#include <ox/types.h>

class process {
protected:
    int pid;
    std::filesystem::path proc_dir;
    std::filesystem::path mem_path;

    ox::file mem_file;
protected:
    virtual bool wrong_endian() {
        return false;
    }
public:
    process(int _pid) : pid{_pid},
                        proc_dir{std::filesystem::path{"/proc"} / std::to_string(pid)},
                        mem_file{proc_dir / "mem", "r+b"} {}

    process(const process& other) = delete;
    process& operator=(const process& other) = delete;
    virtual ~process() = default;

    virtual bool read_memory_raw(i64 address, void* buffer, size_t size, int length, bool byte_swap = false);
    virtual bool write_memory_raw(i64 address, void* value, size_t size, int length, bool byte_swap = false);

    template<typename T> requires std::is_trivially_copyable<T>::value
    bool read_memory(i64 address, T* result) {
        return this->read_memory_raw(address, result, sizeof(T), 1,
            this->wrong_endian() && ox::is_endianable_v<T>
        );
    }

    template<typename T, std::size_t N> requires std::is_trivially_copyable<T>::value
    bool read_memory(i64 address, std::array<T, N>* result) {
        return this->read_memory_raw(address, result, sizeof(T), N,
            this->wrong_endian() && ox::is_endianable_v<T>
        );
    }

    template<typename T> requires std::is_trivially_copyable<T>::value
    bool write_memory(i64 address, T* result) {
        return this->write_memory_raw(address, result, sizeof(T), 1,
            this->wrong_endian() && ox::is_endianable_v<T>
        );
    }

    template<typename T, std::size_t N> requires std::is_trivially_copyable<T>::value
    bool write_memory(i64 address, std::array<T, N>* result) {
        return this->write_memory_raw(address, result->data(), sizeof(T), N,
            this->wrong_endian() && ox::is_endianable_v<T>
        );
    }
};
