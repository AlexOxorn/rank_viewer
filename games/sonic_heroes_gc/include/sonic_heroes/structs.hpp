#pragma once

#include <ox/types.h>
#include <ox/bytes.h>

namespace gc::sonic_heroes {
    struct scores {
        u32 speed_score;
        u32 fly_score;
        u32 power_score;
    };

    struct normal_stages {
        u32 level_id;
        union {
            struct {
                u16 sonic_ranks[4];
                u16 dark_ranks[4];
                u16 rose_ranks[4];
                u16 chaotix_ranks[4];
            };
            u16 ranks_array[4][4];
        };

        void endian_swap() {
            ox::bswap(&level_id);
            for(auto & i : ranks_array)
                ox::bswap(&i[0], 4);
        }
    };

    struct extra_stages {
        u32 level_id;
        union {
            struct {
                u16 sonic_ranks[4];
                u16 chaotix_ranks[4];
            };
            u16 ranks_array[2][4];
        };

        void endian_swap() {
            ox::bswap(&level_id);
            for(auto & i : ranks_array)
                ox::bswap(&i[0], 4);
        }
    };

    struct extra_timed_stages {
        u32 level_id;
        union {
            struct {
                u8 dark_ranks[4][2];
                u8 rose_ranks[4][2];
            };
            u8 ranks_array[2][4][2];
        };

        void endian_swap() {
            ox::bswap(&level_id);
        }
    };

    struct boss_timed_stages {
        u32 level_id;
        union {
            struct {
                u8 sonic_ranks[4][2];
                u8 dark_ranks[4][2];
                u8 rose_ranks[4][2];
                u8 chaotix_ranks[4][2];
            };
            u8 ranks_array[4][4][2];
        };

        void endian_swap() {
            ox::bswap(&level_id);
        }
    };

    struct saved_score {
        u16 rings;
        u16 _blank;
        u32 score;
        u8 time[3];
        u8 rank;
    };

    struct saved_time {
        u8 time[3];
        u8 rank;
    };

    struct level_saved_scores {
        saved_score sonic_normal;
        saved_score sonic_extra;
        saved_score dark_normal;
        saved_time dark_extra;
        saved_score rose_normal;
        saved_time rose_extra;
        saved_score chaotix_normal;
        saved_score chaotix_extra;
    };

    struct player_object2 {
        u16 action;
        u16 action_mirror;
        u16 _flag_04;
        u16 status_flags;
        u16 _flag_08;
        u16 _flag_0C;
        u16 x_rotation;
        u16 _flag_10;
        u16 y_rotation;
        u16 _flag_14;
        u16 z_rotation;
        float x_position;
        float y_position;
        float z_position;
    };

    struct player_object3 {
        float x_speed;
        float y_speed;
        float z_speed;
        float x_forced_speed;
        float y_forced_speed;
        float z_forced_speed;
        u16 _flag_18;
        u16 x_final_rotation;
        u16 _flag_1C;
        u16 y_final_rotation;
        u16 _flag_20;
        u16 z_final_rotation;
    };
}
