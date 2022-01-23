#pragma once

#include <ox/types.h>
#include "structs.hpp"
#include <common.hpp>
#include <helpers.h>

namespace gc::sonic_colors {
    GAME_ARRAY_VARIABLE(i32, scores, 0x90AB717C, 21)
    GAME_VARIABLE(i32, death_count, 0x90AB7448)
    GAME_VARIABLE(float, current_time, 0x90AB7170)
    GAME_VARIABLE(i32, previous_rings, 0x90B25F20)

    GAME_VARIABLE(i32, current_zone, 0x90AB6F44)
    GAME_VARIABLE(i32, current_act, 0x90AB6F48)

    GAME_ARRAY_VARIABLE(stage_data_struct, stage_data, 0x90BFD860, 75)

    GAME_VARIABLE(i32, state1, 0x808511D4)
    GAME_VARIABLE(i32, state2, 0x808511C8)
}
