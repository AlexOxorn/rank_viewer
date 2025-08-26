#pragma once

#include <ox/types.h>
#include <unordered_map>
#include <helpers.h>
#include <common.hpp>

namespace jsr {
    // Decrement Can during results screen
    // 0x004c4a69

    /*
        Final Score

        0x004c4733: 30 * (frames_remaining / 30)
                         (30 points per second)

        0x004c47e1: 3000 if health = max
                  : 30 * health%
        0x004c4836: cans * 100

        table = 0x00826774
        love_shocker_location (tmp): 0x20DE1410

        Reads: (B)0x004c3ea6:



             : (B)0x004c4012:
    */

    GAME_VARIABLE(int, score, 0x98fe44)
    GAME_VARIABLE(int, frames_remaining, 0xdf9d30)
    GAME_VARIABLE(u64, player_struct_ptr, 0xdfd548)

    GAME_INDIRECT_VARIABLE(int, cans, player_struct_ptr, 0x3c8)
    GAME_INDIRECT_VARIABLE(int, max_cans, player_struct_ptr, 0x3cC)
    GAME_INDIRECT_VARIABLE(int, target_health, player_struct_ptr, 0x8b8)
    GAME_INDIRECT_VARIABLE(int, max_health, player_struct_ptr, 0x8bC)


    GAME_VARIABLE(u64, result_pointer, 0xdfd500)
    GAME_INDIRECT_VARIABLE(int, score_total, result_pointer, 0xbc)

    GAME_VARIABLE(u64, global_data_pointer, 0x826774)
    GAME_INDIRECT_VARIABLE(u64, level_pointer, global_data_pointer, 0x2c)
    GAME_INDIRECT_ARRAY(i32, ranks, level_pointer, 0x0, 5)
}
