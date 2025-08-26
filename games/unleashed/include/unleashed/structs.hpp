#pragma once

#include <ox/types.h>
#include "enum.hpp"
#include <unordered_map>
#include <helpers.h>
#include <fmt/core.h>
#include <fmt/ostream.h>
#include <ostream>
#include <bitset>

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
        GameMode Mode;        // 48
        u32 unknown_4C;       // 4C
        u32 unknown_50;       // 50

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

    inline std::ostream& operator<<(std::ostream& os, SScoreInfo i) {
        os << std::format("Time: {}\n", i.TimeBonusStart);
        os << std::format("Rate: {}\n", i.TimeBonusScale);
        os << std::format("S: {}\n", i.SRank);
        os << std::format("A: {}\n", i.ARank);
        os << std::format("B: {}\n", i.BRank);
        os << std::format("C: {}\n", i.CRank);
        os << std::format("D: {}\n", i.DRank);
        os << std::format("E: {}\n", i.ERank);
        return os;
    }

    struct StageRecords {
        // ABCDE
        /*
            A = Continent
                1 - Mazuri
                2 - Adabat
                3 - Chun-nan
                4 - Eggmanlanf
                5 - Spagonia
                6 - Apotos
                7 - Empire City
                8 - Shammar
                9 - Holoska
            B = Night?
            C:
                1 - Tails Plane
                7 - Town Mission?
                8 - ????
            D = AreaNumber
                1 = Town
                2 = Entrance
                4 -> Main Act
                4+ -> Acts/Missions
                8 -> Boss
                9 -> Tutorial Act (WI-1)
                Other -> level
            E = Sub-levels (DLC Act X-E)
        */
        u32 ID;             // 00
        u32 moon_metals;    // 04
        u32 sun_metals;     // 08
        u32 high_score;     // 0C
        float best_time;    // 10
        u32 rank;           // 14
        u32 unknown_38;     // 
        int DLC;

        u32 unknown_00;
        u32 unknown_04;
        u32 unknown_08;
        u32 unknown_0C;
        u32 unknown_10;
        u32 unknown_14;
        u32 unknown_18;
        u32 unknown_1C;

        void endian_swap() {
            ox::bswap(&ID);
            ox::bswap(&moon_metals);
            ox::bswap(&sun_metals);
            ox::bswap(&high_score);
            ox::bswap(&best_time);
            ox::bswap(&rank);
            ox::bswap(&DLC);
            
            ox::bswap(&unknown_00);
            ox::bswap(&unknown_04);
            ox::bswap(&unknown_08);
            ox::bswap(&unknown_0C);
            ox::bswap(&unknown_10);
            ox::bswap(&unknown_14);
            ox::bswap(&unknown_18);
            ox::bswap(&unknown_1C);
            ox::bswap(&unknown_38);

        }

        friend std::ostream& operator<<(std::ostream& os, StageRecords r) {
            constexpr char ranks[] = {'S', 'A', 'B', 'C', 'D', 'E', ' '};
            if (r.ID == 0)
                return os;

            os << std::format("ID: {}\n", r.ID);
            os << std::format("Moon Metals: ") << std::bitset<16>(r.moon_metals) << '\n';
            os << std::format("Sun  Metals: ") << std::bitset<16>(r.sun_metals) << '\n';
            os << std::format("High Score: {}\n", r.high_score);
            os << std::format("Best Time: {}\n", r.best_time);
            os << std::format("Rank: {}\n", ranks[r.rank]);
            os << std::format("DLC: {}\n\n", r.DLC);
            os << std::format("Unknowns: \n\t");
            os << std::format("00: {}\n\t", r.unknown_00);
            os << std::format("04: {}\n\t", r.unknown_04);
            os << std::format("08: {}\n\t", r.unknown_08);
            os << std::format("0C: {}\n\t", r.unknown_0C);
            os << std::format("10: {}\n\t", r.unknown_10);
            os << std::format("14: {}\n\t", r.unknown_14);
            os << std::format("18: {}\n\t", r.unknown_18);
            os << std::format("1C: {}\n\t", r.unknown_1C);
            os << std::format("38: {}\n\t", r.unknown_38);
            return os;
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
