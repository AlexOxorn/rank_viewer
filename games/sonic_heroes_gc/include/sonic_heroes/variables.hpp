#pragma once

#include <ox/types.h>
#include <helpers.hpp>

namespace gc::sonic_heroes {
    GAME_ARRAY_VARIABLE(normal_stages, normal_stage_ranks, 0x8028A2C0, 15);
    GAME_ARRAY_VARIABLE(extra_stages, extra_stage_ranks, 0x8028A4DC, 15);
    GAME_ARRAY_VARIABLE(extra_timed_stages, extra_times_ranks, 0x8028A74C, 15);
    GAME_ARRAY_VARIABLE(boss_timed_stages, boss_times_ranks, 0x8028A608, 8);

    GAME_VARIABLE(int, current_game_state, 0x8029C31C)
    GAME_VARIABLE(int, current_stage, 0x8029C33C)
    GAME_VARIABLE(int, current_team, 0x8029C54C);

    GAME_VARIABLE(int, current_rings, 0x80303D28);
    GAME_ARRAY_VARIABLE(u32, current_scores, 0x80303D54, 3);

    GAME_VARIABLE(int, high_scores, 0x803E7798);
    GAME_ARRAY_VARIABLE(u8, current_time, 0x8042C2FB, 3);
    GAME_VARIABLE(u8, current_mission, 0x80452C48);

    GAME_ARRAY_VARIABLE(u8, current_character_levels, 0x809D9A38, 3);
}
