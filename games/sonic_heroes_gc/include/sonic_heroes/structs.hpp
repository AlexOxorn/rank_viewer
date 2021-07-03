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

        void from_endian() {
            ox::swap(reinterpret_cast<u32*>(&level_id));
            for(int i = 0; i < 4; i++) ox::swap(reinterpret_cast<u16*>(&sonic_ranks[i]));
            for(int i = 0; i < 4; i++) ox::swap(reinterpret_cast<u16*>(&dark_ranks[i]));
            for(int i = 0; i < 4; i++) ox::swap(reinterpret_cast<u16*>(&rose_ranks[i]));
            for(int i = 0; i < 4; i++) ox::swap(reinterpret_cast<u16*>(&chaotix_ranks[i]));
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

        void from_endian() {
            ox::swap(reinterpret_cast<u32*>(&level_id));
            for(int i = 0; i < 4; i++) ox::swap(reinterpret_cast<u16*>(&sonic_ranks[i]));
            for(int i = 0; i < 4; i++) ox::swap(reinterpret_cast<u16*>(&chaotix_ranks[i]));
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

        void from_endian() {
            ox::swap(reinterpret_cast<u32*>(&level_id));
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

        void from_endian() {
            ox::swap(reinterpret_cast<u32*>(&level_id));
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
}
