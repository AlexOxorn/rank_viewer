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
    struct file_deleter {
        static void operator()(FILE* f) { fclose(f); }
    };
    using file = std::unique_ptr<FILE, file_deleter>;

    class native_process : public abstract_process {
    protected:
        std::filesystem::path proc_dir;
        std::filesystem::path mem_path;

        file mem_file;
    public:
        [[nodiscard]] bool wrong_endian(u64) const override {
            return false;
        }

        explicit native_process(int _pid) :
                abstract_process{_pid},
                proc_dir{std::filesystem::path{"/proc"} / std::to_string(pid)},
                mem_file{fopen((proc_dir / "mem").c_str(), "r+b")} {
            if (not mem_file.get()) {
                throw no_file_exception(this->mem_path.c_str());
            }
        }

        native_process(const native_process& other) = delete;
        native_process& operator=(const native_process& other) = delete;
        ~native_process() override = default;

        size_t read_memory_raw(u64 address, void* buffer, size_t size, int length) override;
        size_t write_memory_raw(u64 address, void* value, size_t size, int length) override;
    };
} // namespace UNIX
