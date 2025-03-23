#pragma once

#include <ox/types.h>
#include "enum.hpp"
#include <unordered_map>
#include <helpers.h>

namespace unleashed {
    using char_array = std::array<char, 64>;

    struct SScoreInfo {
        u32 SRank;            //  0
        u32 ARank;            //  4
        u32 BRank;            //  8
        u32 CRank;            //  C
        u32 DRank;            // 10
        u32 ERank;            // 14
        float TimeBonusStart; // 18
        u32 MaxSpeedCount;    // 1C
        float Speeds[3];      // 20
        float GoalSpeed;      // 2C
        u32 SpeedCount;       // 30
        u32 EnemyScore;       // 34
        u32 TrickScore;       // 38
        float unknown_3C;     // 3C
        float unknown_40;     // 3C
        i32 TimeBonusScale;   // 44
        GameMode Mode;        // 44
        u32 unknown_4C;       // 44
        u32 unknown_50;       // 44

        void endian_swap() {
            ox::bswap(&SRank);
            ox::bswap(&ARank);
            ox::bswap(&BRank);
            ox::bswap(&CRank);
            ox::bswap(&DRank);
            ox::bswap(&ERank);
            ox::bswap(&TimeBonusStart);
            ox::bswap(&MaxSpeedCount);
            for (auto& s : Speeds) {
                ox::bswap(&s);
            }
            ox::bswap(&SpeedCount);
            ox::bswap(&EnemyScore);
            ox::bswap(&TrickScore);
            ox::bswap(&TimeBonusScale);
            ox::bswap(&GoalSpeed);
        }
    };

    class night_context // : public CPlayerContext
    {
    public:
        u8 unknown_000[0x660]; // 000
        u32 Rings;             // 660
        u8 unknown_660[0x10];  // 664
        u32 CrushScore;        // 674
        u32 ComboScore;        // 678
        u8 unknown_67C[0xC];   // 67C
        float DarkGaiaEnergy;  // 688
        u8 unknown_68C[0x138]; // 68C
        u32 AnimationID;       // 7c4
        u8 unknown_7c8[0x38];  // 7c8
        float UnkHudGuideF32;  // 800
        u32 UnkHudGuideU32;    // 804
        u8 unknown_808[0x18];  // 808
        u32 GuideType;         // 820
        u8 unknown_828[0xA8];  // 828
        u32 OutOfControlCount; // 8d0

        void endian_swap() {
            ox::bswap(&Rings);
            ox::bswap(&CrushScore);
            ox::bswap(&ComboScore);
            ox::bswap(&DarkGaiaEnergy);
            ox::bswap(&AnimationID);
        }
    };
} // namespace unleashed
