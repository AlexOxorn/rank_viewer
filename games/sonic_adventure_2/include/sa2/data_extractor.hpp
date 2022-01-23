#pragma once
#include "structs.hpp"
#include "variables.hpp"
#include <process.h>
#include <ox/formatting.h>
#include <rank.hpp>

namespace sa2 {
    constexpr int TIMED_LEVEL = 1 << 1;
    constexpr int KART_MISSION = 1 << 2;

    int get_ranks(native_process& process, int level, int mission, int character, stage_union& buffer);

    std::array<score_data, 2> interpret_score(native_process& process);

    std::array<score_data, 4> interpret_score_rank_data(stage_score_rank& stage);

    std::array<score_data, 4> interpret_time_rank_data(stage_time_rank& stage);
}
