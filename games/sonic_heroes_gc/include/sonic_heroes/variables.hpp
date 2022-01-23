#pragma once

#include <ox/types.h>
#include "structs.hpp"
#include <common.hpp>
#include <helpers.h>

#define EACH_HERO_BASE_POINTER(number, address)\
GAME_VARIABLE_OFFSET(u32, lead_pointer_##number, address, current_leader);\
GAME_VARIABLE(u32, spd_pointer_##number, address);\
GAME_VARIABLE(u32, fly_pointer_##number, address + 4);\
GAME_VARIABLE(u32, pow_pointer_##number, address + 8);

#define EACH_HERO_INDIRECT(type, name, base_number, offset)\
GAME_INDIRECT_VARIABLE(type, lead_##name, lead_pointer_##base_number, offset);\
GAME_INDIRECT_VARIABLE(type, spd_##name, spd_pointer_##base_number, offset);\
GAME_INDIRECT_VARIABLE(type, fly_##name, fly_pointer_##base_number, offset);\
GAME_INDIRECT_VARIABLE(type, pow_##name, pow_pointer_##base_number, offset);

namespace gc::sonic_heroes {
    GAME_ARRAY_VARIABLE(normal_stages, normal_stage_ranks, 0x8028A2C0, 15);
    GAME_ARRAY_VARIABLE(extra_stages, extra_stage_ranks, 0x8028A4DC, 15);
    GAME_ARRAY_VARIABLE(extra_timed_stages, extra_times_ranks, 0x8028A74C, 15);
    GAME_ARRAY_VARIABLE(boss_timed_stages, boss_times_ranks, 0x8028A608, 8);

    GAME_VARIABLE(i32, current_game_state, 0x8029C31C)
    GAME_VARIABLE(i32, current_stage, 0x8029C33C)
    GAME_VARIABLE(i32, current_team, 0x8029C54C);

    GAME_VARIABLE(i32, current_rings, 0x80303D28);
    GAME_ARRAY_VARIABLE(u32, current_scores, 0x80303D54, 3);

    GAME_ARRAY_VARIABLE(level_saved_scores, high_scores, 0x803E7798, 14);
    GAME_ARRAY_VARIABLE(u8, current_time, 0x8042C2FB, 3);
    GAME_VARIABLE(u8, current_mission, 0x80452C48);

    GAME_ARRAY_VARIABLE(u8, current_character_levels, 0x809D9A38, 3);

    GAME_VARIABLE(i8, current_leader, 0x809D986A)

    EACH_HERO_BASE_POINTER(1, 0x802AD070)
    EACH_HERO_BASE_POINTER(2, 0x802AD090)
        EACH_HERO_INDIRECT(float_vector, position, 2, 0x18)
    EACH_HERO_BASE_POINTER(3, 0x802AD0B0)
    EACH_HERO_BASE_POINTER(4, 0x802AD0D0)
}

#undef EACH_HERO_BASE_POINTER
#undef EACH_HERO_INDIRECT
