#pragma once

#include <filesystem>
#include <array>
#include <type_traits>
#include <ox/file.h>
#include <ox/types.h>
#include <ox/bytes.h>

class process {
protected:
    int pid;
    std::filesystem::path proc_dir;
    std::filesystem::path mem_path;

    ox::file mem_file;
protected:
    virtual bool wrong_endian() const {
        return false;
    }

    template <typename T>
    bool should_endian_swap() const {
        return this->wrong_endian() && ox::is_endianable_v<T>;
    }
public:
    process(int _pid) : pid{_pid},
                        proc_dir{std::filesystem::path{"/proc"} / std::to_string(pid)},
                        mem_file{proc_dir / "mem", "r+b"} {}

    process(const process& other) = delete;
    process& operator=(const process& other) = delete;
    virtual ~process() = default;

    virtual int read_memory_raw(i64 address, void* buffer, size_t size, int length);
    virtual int write_memory_raw(i64 address, void* value, size_t size, int length);

    template<typename T> requires std::is_trivially_copyable<T>::value
    int read_memory(i64 address, T* result) {
        int amount_read = this->read_memory_raw(address, result, sizeof(T), 1);
        if (should_endian_swap<T>()) ox::swap(result, amount_read);
        return amount_read;
    }

    template<typename T, std::size_t N> requires std::is_trivially_copyable<T>::value
    int read_memory(i64 address, std::array<T, N>* result) {
        auto amount_read = this->read_memory_raw(address, result, sizeof(T), N);
        if (should_endian_swap<T>()) ox::swap(result->data(), amount_read);
        return amount_read;
    }

    template<typename T> requires std::is_trivially_copyable<T>::value
    int write_memory(i64 address, T* result) {
        bool swap = should_endian_swap<T>();
        if (swap) ox::swap(result);
        int amount_wrote = this->write_memory_raw(address, result, sizeof(T), 1);
        if (swap) ox::swap(result);
        return amount_wrote;
    }

    template<typename T, std::size_t N> requires std::is_trivially_copyable<T>::value
    int write_memory(i64 address, std::array<T, N>* result) {
        bool swap = should_endian_swap<T>();
        if (swap) ox::swap(result);
        int amount_wrote = this->write_memory_raw(address, result->data(), sizeof(T), N);
        if (swap) ox::swap(result);
        return amount_wrote;
    }
};
