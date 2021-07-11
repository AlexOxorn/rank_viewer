#pragma once

#include <ox/types.h>
#include "enum.hpp"
#include "structs.hpp"
#include <unordered_map>
#include <helpers.hpp>

namespace sa2 {
    GAME_VARIABLE(int, score, 0x174B050)
    GAME_VARIABLE(minute_second, time, 0x174AFDB)
    GAME_VARIABLE(minute_second_centi, full_time, 0x174AFDB)
    GAME_VARIABLE(int, rings, 0x174B028)

    GAME_ARRAY_VARIABLE(stage_score_rank, mission1_ranks, 0x173AD40, 30)
    GAME_ARRAY_VARIABLE(stage_time_rank,  mission2_ranks, 0x173B0D0, 34)
    GAME_ARRAY_VARIABLE(stage_time_rank,  mission3_ranks, 0x173B208, 30)
    GAME_ARRAY_VARIABLE(stage_score_rank, mission4_ranks, 0x173AE70, 30)
    GAME_ARRAY_VARIABLE(stage_score_rank, mission5_ranks, 0x173AFA0, 30)
    GAME_ARRAY_VARIABLE(stage_time_rank,  kart_mission_ranks, 0x173B378, 10)

    constexpr std::array<u64, 5> mission_rank_addresses {
        mission1_ranks_address,
        mission2_ranks_address,
        mission3_ranks_address,
        mission4_ranks_address,
        mission5_ranks_address
    };

    GAME_VARIABLE(int, current_level, 0x1934B70)
    GAME_VARIABLE(int, current_character, 0x1934B80)
    GAME_VARIABLE(int, current_mission, 0x174AFE3)

    GAME_VARIABLE(float_vector, p1_possition_mirror, 0x19ED3FC)

    GAME_VARIABLE(ptr<object>, p1_object_ptr, 0x1DEA6E0)
    GAME_INDIRECT_VARIABLE(object, p1_object, p1_object_ptr, 0x0)
    GAME_INDIRECT_VARIABLE(ptr<entity_data>, p1_object_entity_ptr, p1_object_ptr, 0x34)
    GAME_INDIRECT_VARIABLE(float_vector, player1_position, p1_object_entity_ptr, 0x14)

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
