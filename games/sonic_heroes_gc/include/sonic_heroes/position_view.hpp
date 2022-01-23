#include <process.h>
#include <filesystem>

namespace gc::sonic_heroes {
    [[noreturn]] void print_position(const std::filesystem::path& p, int pid);
}
