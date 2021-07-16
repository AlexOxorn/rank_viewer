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
#include <ox/formating.h>
#include <fcntl.h>

template <typename T>
std::string
type_name()
{
    typedef typename std::remove_reference<T>::type TR;
    std::string r = typeid(TR).name();
    if (std::is_const<TR>::value)
        r += " const";
    if (std::is_volatile<TR>::value)
        r += " volatile";
    if (std::is_lvalue_reference<T>::value)
        r += "&";
    else if (std::is_rvalue_reference<T>::value)
        r += "&&";
    return r;
}

class process {
protected:
    int pid;
    std::filesystem::path proc_dir;
    std::filesystem::path mem_path;

    FILE *mem_file;
protected:
    virtual bool wrong_endian() {
        return false;
    }
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
        fclose(mem_file);
    }

    virtual bool read_memory_raw(i64 address, void* buffer, size_t size, int length, bool byte_swap = false) const;
    virtual bool write_memory_raw(i64 address, void* value, size_t size, int length, bool byte_swap = false) const;

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
