#pragma once
#include "structs.hpp"
#include "variables.hpp"
#include <process.hpp>
#include <ox/formating.h>
#include <rank.hpp>

namespace sa2 {
    constexpr int TIMED_LEVEL = 1 << 1;
    constexpr int KART_MISSION = 1 << 2;

    int get_ranks(process& process, int level, int mission, int character, void* buffer);

    std::array<score_data, 2> interpret_score(process& process);

    std::array<rank_data, 4> interpret_score_rank_data(stage_score_rank* stage);

    std::array<time_rank_data, 4> interpret_time_rank_data(stage_time_rank* stage);
}
