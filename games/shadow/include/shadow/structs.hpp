#pragma once

#include <ox/types.h>
#include <ox/bytes.h>

namespace gc::shadow {
    struct stage_data {
        struct {
            i32 rank_requirements[4];
            float act_clear_position[3];
        } missions[3];
        float unknown_1;
        float unknown_positions[3];
        u8 zeroes[92];

        void endian_swap() {
            for(auto & mission : missions) {
                for (auto &rank: mission.rank_requirements)
                    ox::bswap(&rank);
                for (auto &pos: mission.act_clear_position)
                    ox::bswap(&pos);
            }
        }
    };

    /*
     * Westopolis Struct
     * Ranks and Positions...
     *
     * -64
     *
     * -2840
     * -9128
     * 10976
     */

    /*
     * r4 = r29(1) * 28 => 28
     *
     * bossID
     * temp = bossID * 192
     * rank_off = temp + 28 + (?) + 96
     * rank = 0x8057a894 + rank_off
     *
     * stage_rank = stage_base + (current_stage - 5) * 0xC0
     * boss_rank = boss_base + (current_stage - 28) * 0xC0
     */

    struct boss_data {
        i32 ranks[4];
        char blank[176];

        void endian_swap() {
            for (auto &rank: ranks)
                ox::bswap(&rank);
        }
    };

    static_assert(sizeof(stage_data) == 0xC0, "Incorrect struct size shadow::stage_data");
    static_assert(sizeof(boss_data) == 0xC0, "Incorrect struct size shadow::boss_data");
}
