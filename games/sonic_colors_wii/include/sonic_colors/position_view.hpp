#pragma once
#include <process.h>
#include <filesystem>

namespace gc::sonic_colors {
    [[noreturn]] void print_position(const std::filesystem::path& p, int pid);
}
