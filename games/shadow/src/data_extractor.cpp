#include <shadow/data_extractor.hpp>
#include <helpers.hpp>
#include <ox/formatting.h>

namespace gc::shadow {
    constexpr int westopolis = 5;
    constexpr int black_bull1 = 28;

    constexpr int seconds_per_minute = 60;
    constexpr int max_timebonus = 50000;
    constexpr int per_second_timebonus_penalty = 80;
    constexpr int max_timebonus_threshold = 90;

    int get_ranks(dolphin_process& process, int level, stage_union& buffer) {
        if (level < westopolis || level == (black_bull1 - 1)) {
            return -1;
        }

        bool boss = level >= black_bull1;
        int offset = level - (boss ? black_bull1 : westopolis);

        if (boss) {
            buffer.boss = get_bosses_at(process, offset);
            return BOSS_LEVEL | TIMED_LEVEL;
        }

        buffer.stage = get_stages_at(process, offset);
        return 0;
    }

    std::array<score_data, 5> interpret_score(dolphin_process& process) {
        std::array<i32, 3> scores = get_current_scores(process);
        float time = get_current_time(process);

        int seconds = static_cast<int>(time);
        int timebonus = max_timebonus - per_second_timebonus_penalty * seconds;
        int timebonus_rest = seconds <= max_timebonus_threshold ? max_timebonus - timebonus : 0;
        timebonus = timebonus < 0 ? 0 : timebonus;

        auto interpreted_scores = std::array{
            score_data{.score = timebonus, .name = "Time Bonus", .foreground = ox::named_colors::grey50},
            score_data{.score = timebonus_rest, .name = "90s Bonus", .foreground = ox::named_colors::gray30},
            score_data{.score = static_cast<int>(scores[0]), .name = "Normal", .foreground = ox::named_colors::chartreuse1},
            score_data{.score = static_cast<int>(scores[1]), .name = "Hero", .foreground = ox::named_colors::RoyalBlue},
            score_data{.score = static_cast<int>(scores[2]), .name = "Dark", .foreground = ox::named_colors::IndianRed3}
        };

//        std::ranges::stable_partition(scores, [](int i) {return i < 0;}, &score_data::score);

        return interpreted_scores;
    }

    std::array<std::array<score_data, 4>, 3> interpret_score_rank_data(stage_data* stage) {
        std::array<std::array<score_data, 4>, 3> to_return;
        for(int i = 0; i < 3; i++) {
            auto ranks = stage->missions[i].rank_requirements;
            to_return[i] = std::array{
                    score_data{ranks[0], "A"},
                    score_data{ranks[1], "B"},
                    score_data{ranks[2], "C"},
                    score_data{ranks[3], "D"}
            };
        }
        return to_return;
    }

    std::array<score_data, 4> interpret_score_rank_data(stage_data* stage, int goal) {
        auto ranks = stage->missions[goal].rank_requirements;
        return std::array{
                score_data{ranks[0], "A"},
                score_data{ranks[1], "B"},
                score_data{ranks[2], "C"},
                score_data{ranks[3], "D"}
        };
    }

    std::array<score_data, 4> interpret_time_rank_data(boss_data* boss) {
        auto ranks = boss->ranks;
        return std::array{
            score_data{ranks[0], "A"},
            score_data{ranks[1], "B"},
            score_data{ranks[2], "C"},
            score_data{ranks[3], "D"}
        };
    }
}
