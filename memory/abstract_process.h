//
// Created by alexoxorn on 2022-01-23.
//

#ifndef RANK_VIEWER_ABSTRACT_PROCESS_H
#define RANK_VIEWER_ABSTRACT_PROCESS_H

#include <filesystem>
#include <array>
#include <type_traits>
#include <format>
#include <ox/io.h>
#include <ox/types.h>
#include <ox/bytes.h>

using namespace ox::int_alias;

class no_file_exception : std::exception {
    std::string message;
public:
    no_file_exception(const char* filename) :
            message(std::format("Can't Open File {}\nError Number {}\n", filename, errno)) {}
    const char* what() const noexcept override  {
        return message.c_str();
    }
};

class abstract_process {
protected:
    long pid;

    [[nodiscard]] virtual bool wrong_endian(u64 = 0) const = 0;

    template <typename T>
    [[nodiscard]] bool should_endian_swap(u64 ptr = 0) const {
        return this->wrong_endian(ptr) && ox::is_endianable_v<T>;
    }
public:
    explicit abstract_process(int _pid) : pid(_pid) {};

    abstract_process(const abstract_process& other) = delete;
    abstract_process& operator=(const abstract_process& other) = delete;
    virtual ~abstract_process() = default;

    virtual size_t read_memory_raw(u64 address, void* buffer, size_t size, int length) = 0;
    virtual size_t write_memory_raw(u64 address, void* value, size_t size, int length) = 0;

    template <typename T>
    requires std::is_trivially_copyable<T>::value
    int read_memory(u64 address, T* result) {
        int amount_read = this->read_memory_raw(address, result, sizeof(T), 1);
        if (should_endian_swap<T>())
            ox::bswap(result, amount_read);
        return amount_read;
    }

    template <typename T, std::size_t N>
    requires std::is_trivially_copyable<T>::value
    int read_memory(u64 address, std::array<T, N>* result) {
        auto amount_read = this->read_memory_raw(address, result, sizeof(T), N);
        if (should_endian_swap<T>())
            ox::bswap(result->data(), amount_read);
        return amount_read;
    }

    template <typename T>
    requires std::is_trivially_copyable<T>::value
    int write_memory(u64 address, T* result) {
        bool swap = should_endian_swap<T>();
        if (swap)
            ox::bswap(result);
        int amount_wrote = this->write_memory_raw(address, result, sizeof(T), 1);
        if (swap)
            ox::bswap(result);
        return amount_wrote;
    }

    template <typename T, std::size_t N>
    requires std::is_trivially_copyable<T>::value
    int write_memory(u64 address, std::array<T, N>* result) {
        bool swap = should_endian_swap<T>();
        if (swap)
            ox::bswap(result);
        int amount_wrote = this->write_memory_raw(address, result->data(), sizeof(T), N);
        if (swap)
            ox::bswap(result);
        return amount_wrote;
    }
};

#endif // RANK_VIEWER_ABSTRACT_PROCESS_H
