#include <sonic_heroes/data_extractor.hpp>
#include <helpers.hpp>
#include <ox/formatting.h>

namespace gc::sonic_heroes {
    constexpr int seaside_hill = 2;
    constexpr int rail_canyon = 8;
    constexpr int chaotix_rail_canyon = 36;
    constexpr int final_fortress =15;
    constexpr int egg_hawk = 16;
    constexpr int metal_madness = 23;
    constexpr int metal_overlord = 24;

    constexpr int seconds_per_minute = 60;
    constexpr int max_timebonus = 50000;
    constexpr int per_second_timebonus_penalty = 80;
    constexpr int max_timebonus_threshold = 90;
    constexpr int points_per_level = 500;
    constexpr int state_level_completed = 0xC;

    int get_ranks(dolphin_process& process, int level, int team, int mission, stage_union& buffer) {
        if (level != chaotix_rail_canyon && (level < seaside_hill || mission > 1 || level > metal_overlord)) {
            return -1;
        }

        // Metal Overlord
        level = level == metal_overlord ? metal_madness : level;
        // Chaotix Rail Canyon
        level = level == chaotix_rail_canyon ? rail_canyon : level;
        int offset = level - egg_hawk;

        if (level > final_fortress) {
            buffer.boss_timed = get_boss_times_ranks_at(process, offset);
            return BOSS_LEVEL | TIMED_LEVEL;
        }

        offset = level - seaside_hill;

        if (mission == 0) {
            // Chaotix extra rails canyon
            if (offset > rail_canyon - seaside_hill)
                offset++;
            buffer.stage = get_normal_stage_ranks_at(process, offset);
            return 0;
        }

        if (team == 0 || team == 3) {
            // Chaotix extra rails canyon
            if (offset >= rail_canyon - seaside_hill)
                offset++;
            buffer.extra = get_extra_stage_ranks_at(process, offset);
            return EXTRA_MISSION;
        }

        buffer.extra_timed = get_extra_times_ranks_at(process, offset);
        return EXTRA_MISSION | TIMED_LEVEL;
    }

    std::array<score_data, 5> interpret_score(dolphin_process& process) {
        int state = get_current_game_state(process);
        std::array<u32, 3> scores = get_current_scores(process);
        std::array<u8, 3> time = get_current_time(process);
        std::array<u8, 3> cores = get_current_character_levels(process);

        int seconds = time[0] * seconds_per_minute + time[1];
        int timebonus = max_timebonus - per_second_timebonus_penalty * seconds;
        int timebonus_rest = seconds <= max_timebonus_threshold ? max_timebonus - timebonus : 0;
        timebonus = timebonus < 0 ? 0 : timebonus;

        if (state != state_level_completed) {
            for(int i = 0; i < 3; i++) {
                scores.at(i) += points_per_level * cores.at(i);
            }
        }

        return std::array{
            score_data{.score = timebonus, .name = "Time Bonus", .foreground = ox::named_colors::grey50},
            score_data{.score = static_cast<int>(scores[0]), .name = "Speed Score", .foreground = ox::named_colors::RoyalBlue},
            score_data{.score = static_cast<int>(scores[1]), .name = "Fly Score", .foreground = ox::named_colors::gold},
            score_data{.score = static_cast<int>(scores[2]), .name = "Power Score", .foreground = ox::named_colors::IndianRed3},
            score_data{.score = timebonus_rest, .name = "90s Bonus", .foreground = ox::named_colors::gray30}
        };
    }

    template<typename rank_type>
    std::array<score_data, 4> interpret_score_rank_data(rank_type& stage, int team) {
        if constexpr (std::is_same_v<rank_type, extra_stages>) {
            team = team > 0;
        }
        auto ranks = *reinterpret_cast<std::array<u16, 4> *>(&stage.ranks_array[team]);

        return std::array{
            score_data{ranks[0] * 100, "D"},
            score_data{ranks[1] * 100, "C"},
            score_data{ranks[2] * 100, "B"},
            score_data{ranks[3] * 100, "A"}
        };
    }

    template<typename rank_type>
    std::array<score_data, 4> interpret_time_rank_data(rank_type& stage, int team) {
        if constexpr (std::is_same_v<rank_type, extra_timed_stages>) {
            team = team - 1;
        }
        auto ranks = *reinterpret_cast<std::array<std::array<u8, 2>, 4> *>(&stage.ranks_array[team]);
        return std::array{
            score_data{ranks[0][0] * 60 + ranks[0][1], "D"},
            score_data{ranks[1][0] * 60 + ranks[1][1], "C"},
            score_data{ranks[2][0] * 60 + ranks[2][1], "B"},
            score_data{ranks[3][0] * 60 + ranks[3][1], "A"}
        };
    }

    template  std::array<score_data, 4> interpret_score_rank_data<normal_stages>     (normal_stages& stage,      int team);
    template  std::array<score_data, 4> interpret_score_rank_data<extra_stages>      (extra_stages& stage,       int team);
    template  std::array<score_data, 4> interpret_time_rank_data <extra_timed_stages>(extra_timed_stages& stage, int team);
    template  std::array<score_data, 4> interpret_time_rank_data <boss_timed_stages> (boss_timed_stages& stage,  int team);
}
