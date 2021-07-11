#include <dolphin_process.hpp>
#include <sa2/data_extractor.hpp>
#include <position_dump.hpp>
#include <sa2/variables.hpp>
#include <fmt/core.h>
#include <cstdlib>
#include <unistd.h>

namespace sa2 {
    void print_position(std::filesystem::path p, int pid);
}
