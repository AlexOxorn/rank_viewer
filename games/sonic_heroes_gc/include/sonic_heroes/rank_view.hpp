#include <dolphin_process.hpp>
#include <rank.hpp>
#include <ox/formating.h>
#include <sonic_heroes/data_extractor.hpp>
#include <fmt/core.h>
#include <iostream>
#include <cstdlib>
#include <unistd.h>

namespace gc::sonic_heroes {
    constexpr int stall_time_milli = 2500;

    struct state {
        int level;
        int team;
        int mission;

        bool operator==(state other) const {
            return level == other.level &&
                    team == other.team &&
                    mission == other.mission;
        }
    };

    void display_ranks(int pid);
}
