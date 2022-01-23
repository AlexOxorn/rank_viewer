#pragma once
#include <process.h>
#include <rank.hpp>
#include "structs.hpp"
#include "variables.hpp"

namespace gc::shadow {
    constexpr int EXTRA_MISSION = 1 << 1;
    constexpr int BOSS_LEVEL = 1 << 2;
    constexpr int TIMED_LEVEL = 1 << 3;

    int get_ranks(dolphin_process& process, int level, stage_union& buffer);
    std::array<score_data, 5> interpret_score(dolphin_process& process);

    std::array<score_data, 4> interpret_score_rank_data(stage_data* stage, int goal);

    std::array<std::array<score_data, 4>, 3> interpret_score_rank_data(stage_data* stage);

    std::array<score_data, 4> interpret_time_rank_data(boss_data* stage);
}
