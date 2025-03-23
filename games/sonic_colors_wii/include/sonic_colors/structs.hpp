#pragma once

#include <ox/types.h>
#include <ox/bytes.h>
#include <cstddef>
#include <array>
#include <cstdio>
#include <bit>

using namespace ox::int_alias;

namespace gc::sonic_colors {
    template <typename T, int Size = sizeof(T)>
    T endian_swap(T thing) {
        if constexpr (Size == 1) {
            return thing;
        } else if constexpr (Size == 2) {
            return std::bit_cast<T>(bswap(std::bit_cast<unsigned short>(thing)));
        } else if constexpr (Size == 4) {
            return std::bit_cast<T>(bswap(std::bit_cast<unsigned int>(thing)));
        } else if constexpr (Size == 8) {
            return std::bit_cast<T>(bswap(std::bit_cast<unsigned long>(thing)));
        }
        else return T{};
    }

    struct time_bonus {
        i32 base;
        i32 penalty;
    };

    struct stage_data_struct {
        char stageName[16];         // 0
        char stageData1[16];        // 16
        char stageData2[16];        // 32
        u8 blank30[16];             // 48
        float startX;               // 64
        float startY;               // 68
        float startZ;               // 72
        float startTheta;           // 76
        union {                     // 80
            struct {
                bool is2D;          // 80
                char blankB1_;      // 81
                char blankB2_;      // 82
                u8 LoadingScreen;   // 83
                char blankB4_;      // 84
                char blankB5_;      // 85
                char blankB6_;      // 86
                u8 start_action;    // 87
                float start_speed;  // 88
            };
            char blankB0[12];
        };
        u32 unknown_pointer_BC;     // 92
        u32 unknown_int_C0;         // 96
        u32 unknown_int_C4;         // 100
        u32 unknown_int_C8;         // 104
        u32 unknown_int_CC;         // 108
        u8 blankD0[20];             // 112
        u32 unknown_pointer_E4;     // 132
        u8 blankE8[20];             // 136
        float unknown_float_FC;     // 156
        u32 unknown_flag_00;        // 160
        float unknown_float_04;     // 164
        u32 unknown_flag_08;        // 168
        char background_music[0x20];// 172
        i32 rank_requirements[4];   // 192
        time_bonus time_bonus_data; // 208
        i32 no_miss_bonus[5];       // 216
        char result_background[0x20];// 236

        void endian_swap() {
            ox::bswap(&startX);
            ox::bswap(&startY);
            ox::bswap(&startZ);
            ox::bswap(&startTheta);
            ox::bswap(&time_bonus_data.base);
            ox::bswap(&time_bonus_data.penalty);
            for(auto & i : rank_requirements)
                ox::bswap(&i);
            for(auto & i : no_miss_bonus)
                ox::bswap(&i);
        }
    };


}

#undef es