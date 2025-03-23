#pragma once

#include "ox/types.h"
#include "ox/bytes.h"
#include "native_process.hpp"
#include <bit>

namespace UNIX {
    class dolphin_process : public native_process {
        constexpr static u32 gc_memory_start = 0x80000000;
        constexpr static u32 wii_memory_start = 0x90000000;
        u64 emu_ram_address = 0;
        u64 mem2_address = 0;
        bool mem2_present = false;
    protected:
        [[nodiscard]] bool wrong_endian(u64) const override { return std::endian::native != std::endian::big; }

        [[nodiscard]] u64 mapped_address(u64 address) const;
    public:
        explicit dolphin_process(int _pid);

        size_t read_memory_raw(u64 address, void* buffer, size_t size, int length) override;
        size_t write_memory_raw(u64 address, void* buffer, size_t size, int length) override;
    };

}
