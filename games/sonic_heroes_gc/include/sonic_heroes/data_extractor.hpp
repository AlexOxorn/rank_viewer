#pragma once
#include <dolphin_process.hpp>
#include <rank.hpp>
#include "structs.hpp"
#include "variables.hpp"

namespace gc::sonic_heroes {
    constexpr int EXTRA_MISSION = 1 << 1;
    constexpr int BOSS_LEVEL = 1 << 2;
    constexpr int TIMED_LEVEL = 1 << 3;

    int get_ranks(dolphin_process& process, int level, int team, int mission, void* buffer);
    std::array<score_data, 5> interpret_score(dolphin_process& process);

    template<typename rank_type>
    std::array<score_data, 4> interpret_score_rank_data(rank_type* stage, int team);

    template<typename rank_type>
    std::array<score_data, 4> interpret_time_rank_data(rank_type* stage, int team);
}
