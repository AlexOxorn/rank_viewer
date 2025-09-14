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

    constexpr int NUMBER_OF_RANKS = 5;

    GAME_VARIABLE(int, score, 0x98fe44)
    GAME_VARIABLE(int, frames_remaining, 0xdf9d30)
    GAME_VARIABLE(u32, frames_remaining_dyn_base, 0xdfd424)
    GAME_INDIRECT_VARIABLE(int, frames_remaining_dyn, frames_remaining_dyn_base, 0x74)

    GAME_VARIABLE(u32, player_struct_ptr, 0xdfd548)
    GAME_INDIRECT_VARIABLE(int, cans, player_struct_ptr, 0x3c8)
    GAME_INDIRECT_VARIABLE(int, max_cans, player_struct_ptr, 0x3cC)
    GAME_INDIRECT_VARIABLE(int, target_health, player_struct_ptr, 0x8b8)
    GAME_INDIRECT_VARIABLE(int, max_health, player_struct_ptr, 0x8bC)


    GAME_VARIABLE(u32, result_pointer, 0xdfd500)
    GAME_INDIRECT_VARIABLE(int, score_tally, result_pointer, 0xb8)
    GAME_INDIRECT_VARIABLE(int, score_total, result_pointer, 0xbc)

    GAME_VARIABLE(u32, global_data_pointer, 0x826774)
    GAME_INDIRECT_VARIABLE(u32, level_pointer, global_data_pointer, 0x2c)
    GAME_INDIRECT_VARIABLE(u32, max_time, global_data_pointer, 0xe4)
    GAME_INDIRECT_ARRAY(i32, ranks, level_pointer, 0x0, NUMBER_OF_RANKS)

    constexpr const char* rank_names[] = {
            "Jet",
            "Nitro",
            "Turbo",
            "Engine",
            "Motor",
            "Pedal",
    };
}

/*

Data Mined

Health
Beat: 110
Gum: 77
Tab: 110
Garam: 120
Mew: 77
Yo-Yo: 72
Combo: 150
Cube: 94
Slate: 116
Piranha: 110
Lover Shocker: 72
Poison Jam: 140
Noise Tank: 120
Goji: 150
Pots: 30

 Rank Requirements
 Shibuya
 Jet Graphiti:
      Jet: 80000
      Nitro: 67000
      Turbo: 60000
      Engine: 54000
      Motor: 47000
 Jet Technique:
      Jet: 43000
      Nitro: 33000
      Turbo: 29000
      Engine: 24000
      Motor: 19000
 Jet Crush:
      Jet: 88
      Nitro: 91
      Turbo: 97
      Engine: 406
      Motor: 200

 Kogane
 Jet Graphiti:
      Jet: 70000
      Nitro: 59000
      Turbo: 53000
      Engine: 48000
      Motor: 42000
 Jet Technique:
      Jet: 47000
      Nitro: 38000
      Turbo: 33000
      Engine: 29000
      Motor: 24000
 Jet Crush:
      Jet: 115
      Nitro: 120
      Turbo: 125
      Engine: 130
      Motor: 200

 Benten:
 Behind the Mask:
    Jet: 29000
    Nitro: 22000
    Turbo: 18000
    Engine: 15000
    Motor: 11000
 Jet Graphiti:
    Jet: 78000
    Nitro: 65000
    Turbo: 58000
    Engine: 52000
    Motor: 45000
 Jet Technique:
    Jet: 52000
    Nitro: 43000
    Turbo: 38000
    Engine: 34000
    Motor: 29000
Jet Crush:
    Jet: 90
    Nitro: 95
    Turbo: 100
    Engine: 105
    Motor: 200
 */