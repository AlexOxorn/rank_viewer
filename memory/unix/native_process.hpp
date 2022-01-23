#pragma once

#include <filesystem>
#include <array>
#include <type_traits>
#include "ox/io.h"
#include "ox/types.h"
#include "ox/bytes.h"
#include "../abstract_process.h"

using namespace ox::int_alias;

namespace UNIX {
    class native_process : public abstract_process {
    protected:
        std::filesystem::path proc_dir;
        std::filesystem::path mem_path;

        ox::file mem_file;
    public:
        [[nodiscard]] bool wrong_endian() const override {
            return false;
        }

        explicit native_process(int _pid) :
                abstract_process{_pid},
                proc_dir{std::filesystem::path{"/proc"} / std::to_string(pid)},
                mem_file{proc_dir / "mem", "r+b"} {}

        native_process(const native_process& other) = delete;
        native_process& operator=(const native_process& other) = delete;
        ~native_process() override = default;

        size_t read_memory_raw(u64 address, void* buffer, size_t size, int length) override;
        size_t write_memory_raw(u64 address, void* value, size_t size, int length) override;
    };
} // namespace UNIX
