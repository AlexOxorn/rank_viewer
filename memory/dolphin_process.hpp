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
    u64 emu_ram_address = 0;
    u64 mem2_address = 0;
    bool mem2_present = false;
protected:
    virtual bool wrong_endian() override {
        return ox::O32_HOST_ORDER() != ox::O32_BIG_ENDIAN;
    }
public:
    dolphin_process(int _pid);

    bool read_memory_raw(i64 address, void* buffer, size_t size, int length, bool byte_swap = false) const override;
    bool write_memory_raw(i64 address, void* buffer, size_t size, int length, bool byte_swap = false) const override;
};
