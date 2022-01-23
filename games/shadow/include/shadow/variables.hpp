#pragma once

#include <ox/types.h>
#include "structs.hpp"
#include <common.hpp>
#include <helpers.h>

namespace gc::shadow {
    GAME_ARRAY_VARIABLE(stage_data, stages, 0x8057ACB4, 22)
    GAME_ARRAY_VARIABLE(boss_data , bosses, 0x8057BE10, 17)

    GAME_ARRAY_VARIABLE(i32, current_scores, 0x80576710, 3)
    GAME_VARIABLE(i32, normal_score, 0x80576710)
    GAME_VARIABLE(i32, hero_score, 0x80576714)
    GAME_VARIABLE(i32, dark_score, 0x80576718)

    GAME_VARIABLE(i32, current_goal, 0x80575F1C)
    GAME_VARIABLE(float, current_time, 0x8057D734)
    GAME_VARIABLE(int, current_stage, 0x8057D74C)
}

#undef EACH_HERO_BASE_POINTER
#undef EACH_HERO_INDIRECT
