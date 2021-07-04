#pragma once

#include <ox/types.h>
#include "enum.hpp"
#include <unordered_map>

namespace sa2 {
    constexpr u64 score_address = 0x174B050;
    constexpr u64 time_address = 0x174AFDB;
    constexpr u64 rings_address = 0x174B028;

    constexpr u64 mission1_ranks = 0x173AD40;
    constexpr u64 mission2_ranks = 0x173B0D0;
    constexpr u64 mission3_ranks = 0x173B208;
    constexpr u64 mission4_ranks = 0x173AE70;
    constexpr u64 mission5_ranks = 0x173AFA0;
    constexpr u64 kart_mission_ranks = 0x173B378;

    constexpr std::array<u64, 5> mission_rank_addresses {
        mission1_ranks,
        mission2_ranks,
        mission3_ranks,
        mission4_ranks,
        mission5_ranks
    };

    constexpr u64 current_level_address = 0x1934B70;
    constexpr u64 current_character_address = 0x1934B80;
    constexpr u64 current_mission_address = 0x174AFE3;

    const std::unordered_map<int, int> stage_index{
        {CityEscape, 0},
        {WildCanyon, 1},
        {PrisonLane, 2},
        {MetalHarbor, 3},
        {GreenForest, 4},
        {PumpkingHill, 5},
        {MissionStreet, 6},
        {AquaticMine, 7},
        {HiddenBase, 8},
        {PyramidCave, 9},
        {DeathChamber, 10},
        {EternalEngine, 11},
        {MeteorHerd, 12},
        {CrazyGadget, 13},
        {FinalRush, 14},
        {IronGate, 15},
        {DryLagoon, 16},
        {SandOcean, 17},
        {RadicalHighway, 18},
        {EggQuarters, 19},
        {LostColony, 20},
        {WeaponBed , 21},
        {SecurityHall, 22},
        {WhiteJungle, 23},
        {SkyRail, 24},
        {MadSpace, 25},
        {CosmicWall, 26},
        {FinalChase, 27},
        {CannonsCoreSonic, 28},
        {CannonsCore2, 28},
        {CannonsCore3, 28},
        {CannonsCore4, 28},
        {CannonsCore5, 28},
        {GreenHill, 29},
    };
}

// 3550
//-1600
// 29690
