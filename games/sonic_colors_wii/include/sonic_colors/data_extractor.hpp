#pragma once
#include <dolphin_process.hpp>
#include <rank.hpp>
#include "structs.hpp"
#include "variables.hpp"
#include "common.hpp"

namespace gc::sonic_colors {
    extern const std::array<std::string, 21> score_names;

    int read_stage_data(dolphin_process& process, int zone, int act, stage_data_struct& buffer);

    std::array<score_data, 28> interpret_score(dolphin_process& process, const stage_data_struct& stage);

    std::array<score_data, 4> interpret_score_rank_data(const stage_data_struct& stage);
}
