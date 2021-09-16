#include <chrono>
#include <thread>
#include <iostream>

#include <ox/common.h>
#include <fmt/core.h>
#include <sonic_colors/variables.hpp>
#include <sonic_colors/rank_view.hpp>
#include <sonic_colors/position_view.hpp>

#include <position_dump.hpp>

namespace gc::sonic_heroes {
    using namespace std::literals::chrono_literals;
    constexpr auto stall_time = 100ms;
}
