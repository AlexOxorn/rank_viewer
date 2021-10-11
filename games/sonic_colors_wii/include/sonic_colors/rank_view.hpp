#pragma once

#include <compare>

namespace gc::sonic_colors {
    constexpr int stall_time_milli = 2500;

    struct state {
        int zone;
        int act;

        bool operator<=>(const state& other) const = default;
    };

    void display_ranks(int pid);
    void display_ranksX(int pid);
}
