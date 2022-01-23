#pragma once

#include <ox/types.h>
#include <unordered_map>
#include <helpers.h>
#include <common.hpp>

namespace jsr {
    GAME_VARIABLE(u64, score, 0x98fe44)
    GAME_VARIABLE(u64, player_struct_ptr, 0xdfd548)
    GAME_INDIRECT_VARIABLE(int, cans, player_struct_ptr, 0x3c8)
}
