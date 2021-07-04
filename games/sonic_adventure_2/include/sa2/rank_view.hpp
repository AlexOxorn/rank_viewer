#include <dolphin_process.hpp>
#include <rank.hpp>
#include <ox/formating.h>
#include <sa2/data_extractor.hpp>
#include <fmt/core.h>
#include <iostream>
#include <cstdlib>
#include <unistd.h>

namespace sa2 {
    constexpr int stall_time_milli = 2500;

    struct state {
    	int level;
    	int mission;

    	bool operator==(state other) const {
    		return level == other.level &&
    				mission == other.mission;
    	}
    };

    void display_ranks(int pid);
}
