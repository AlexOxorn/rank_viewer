#include <process.h>
#include <filesystem>

namespace sa2 {
    [[noreturn]] void print_position(std::filesystem::path p, int pid);
}
