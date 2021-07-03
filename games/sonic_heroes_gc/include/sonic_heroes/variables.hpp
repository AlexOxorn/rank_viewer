#pragma once

#include <ox/types.h>

namespace gc::sonic_heroes {
    constexpr u32 normal_stage_ranks = 0x8028A2C0;
    constexpr u32 extra_stage_ranks = 0x8028A4DC;
    constexpr u32 extra_times_ranks = 0x8028A74C;
    constexpr u32 boss_times_ranks = 0x8028A608;

    constexpr u32 rings_address = 0x80303D28;
    constexpr u32 score_address = 0x80303D54;
    constexpr u32 stage_address = 0x8029C33C;
    constexpr u32 team_address  = 0x8029C54C;
    constexpr u32 character_levels = 0x809D9A38;
    constexpr u32 time_address = 0x8042C2FB;

    constexpr u32 high_score_address = 0x803E7798;
    constexpr u32 extra_flag_address = 0x80452C48;

    constexpr u32 game_state = 0x8029C31C;
}
