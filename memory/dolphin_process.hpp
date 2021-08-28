#pragma once

#include <ox/types.h>
#include <ox/bytes.h>
#include "process.hpp"

class dolphin_process : public process {
    static constexpr u32 gc_memory_start = 0x80000000;
    u64 emu_ram_address = 0;
    u64 mem2_address = 0;
    bool mem2_present = false;
protected:
    [[nodiscard]] bool wrong_endian() const override {
        return ox::O32_HOST_ORDER != ox::O32_BIG_ENDIAN;
    }
public:
    explicit dolphin_process(int _pid);

    size_t read_memory_raw(u64 address, void* buffer, size_t size, int length) override;
    size_t write_memory_raw(u64 address, void* buffer, size_t size, int length) override;
};
