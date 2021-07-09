#pragma once

#include <ox/types.h>

namespace gc::sonic_heroes {
    constexpr u32 normal_stage_ranks = 0x8028A2C0;
    constexpr u32 extra_stage_ranks = 0x8028A4DC;
    constexpr u32 extra_times_ranks = 0x8028A74C;
    constexpr u32 boss_times_ranks = 0x8028A608;

    constexpr u32 current_game_state = 0x8029C31C;
    constexpr u32 current_stage_address = 0x8029C33C;
    constexpr u32 current_team_address  = 0x8029C54C;

    constexpr u32 current_rings_address = 0x80303D28;
    constexpr u32 current_scores_address = 0x80303D54;

    constexpr u32 high_scores_address = 0x803E7798;
    constexpr u32 current_time_address = 0x8042C2FB;
    constexpr u32 extra_flag_address = 0x80452C48;

    constexpr u32 character_levels = 0x809D9A38;
}
