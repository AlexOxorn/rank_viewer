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

    GAME_VARIABLE(i16, current_level, 0x1934B70)
    GAME_VARIABLE(int, current_character, 0x1934B80)
    GAME_VARIABLE(i8, current_mission, 0x174AFE3)

    GAME_VARIABLE(float_vector, p1_possition_mirror, 0x19ED3FC)

    GAME_VARIABLE(ptr<object>, p1_object_ptr, 0x1DEA6E0)
    GAME_INDIRECT_VARIABLE(object, p1_object, p1_object_ptr, 0x0)
    GAME_INDIRECT_VARIABLE(ptr<entity_data>, p1_object_entity_ptr, p1_object_ptr, 0x34)
    GAME_INDIRECT_VARIABLE(float_vector, player1_position, p1_object_entity_ptr, 0x14)

    constexpr std::array<u64, 5> mission_rank_addresses {
        mission1_ranks_address,
        mission2_ranks_address,
        mission3_ranks_address,
        mission4_ranks_address,
        mission5_ranks_address
    };

    constexpr std::array<char, 45> stage_index {
        static_cast<char>(-1),
        static_cast<char>(-1),
        static_cast<char>(-1),
        static_cast<char>( 4),     // 3:  GreenForest
        static_cast<char>(23),     // 4:  WhiteJungle
        static_cast<char>( 5),     // 5:  PumpkingHill
        static_cast<char>(24),     // 6:  SkyRail
        static_cast<char>( 7),     // 7:  AquaticMine
        static_cast<char>(22),     // 8:  SecurityHall
        static_cast<char>( 2),     // 9:  PrisonLane
        static_cast<char>( 3),     // 10: MetalHarbor
        static_cast<char>(15),     // 11: IronGate
        static_cast<char>(21),     // 12: WeaponBed
        static_cast<char>( 0),     // 13: CityEscape
        static_cast<char>(18),     // 14: RadicalHighway
        static_cast<char>(-1),     // 15:
        static_cast<char>( 1),     // 16: WildCanyon
        static_cast<char>( 6),     // 17: MissionStreet
        static_cast<char>(16),     // 18: DryLagoon
        static_cast<char>(-1),     // 19:
        static_cast<char>(-1),     // 20:
        static_cast<char>(17),     // 21: SandOcean
        static_cast<char>(13),     // 22: CrazyGadget
        static_cast<char>( 8),     // 23: HiddenBase
        static_cast<char>(11),     // 24: EternalEngine
        static_cast<char>(10),     // 25: DeathChamber
        static_cast<char>(19),     // 26: EggQuarters
        static_cast<char>(20),     // 27: LostColony
        static_cast<char>( 9),     // 28: PyramidCave
        static_cast<char>(-1),     // 29:
        static_cast<char>(14),     // 30: FinalRush
        static_cast<char>(29),     // 31: GreenHill
        static_cast<char>(12),     // 32: MeteorHerd
        static_cast<char>(-1),     // 33:
        static_cast<char>(28),     // 34: CannonsCoreSonic
        static_cast<char>(28),     // 35: CannonsCore2
        static_cast<char>(28),     // 36: CannonsCore3
        static_cast<char>(28),     // 37: CannonsCore4
        static_cast<char>(28),     // 38: CannonsCore5
        static_cast<char>(-1),     // 39:
        static_cast<char>(27),     // 40: FinalChase
        static_cast<char>(-1),     // 41:
        static_cast<char>(-1),     // 42:
        static_cast<char>(26),     // 43: CosmicWall
        static_cast<char>(25),     // 44: MadSpace
    };
}
