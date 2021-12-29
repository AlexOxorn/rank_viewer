#include <sa2/data_extractor.hpp>
#include <helpers.hpp>

namespace sa2 {
    int get_ranks(process& process, int level, int mission, int character, stage_union& buffer) {
        if (level == KartRoutes) {
            int char_offset = character == Characters_Rouge ? 5 : 0;
            buffer.timed = get_kart_mission_ranks_at(process, char_offset + mission);
            return TIMED_LEVEL;
        }

        auto index = stage_index[level];
        if (index < 0) {
            return -1;
        }

        if (mission == 0 || mission == 3 || mission == 4) {
            auto get_rank_at = get_score_mission_rank.at(mission);
            if (get_rank_at)
                buffer.scored = get_score_mission_rank.at(mission)(process, index);
            return 0;
        }

        if (mission == 1 || mission == 2) {
            auto get_rank_at = get_time_mission_rank.at(mission);
            if (get_rank_at)
                buffer.timed = get_time_mission_rank.at(mission)(process, index);
            return TIMED_LEVEL;
        }

        return -1;
    }

    std::array<score_data, 2> interpret_score(process& process) {
        int score = get_score(process);
        minute_second time = get_time(process);

        int seconds = time.minutes * 60 + time.seconds;
        int timebonus = seconds <= 60 ? 10000 : 11200 - seconds * 20;
        timebonus = timebonus < 0 ? 0 : timebonus;

        return std::array{
            score_data{.score = timebonus, .name = "Time Bonus", .foreground = ox::named_colors::DarkTurquoise},
            score_data{.score = score, .name = "Score", .foreground = ox::named_colors::DodgerBlue3}
        };
    }

    std::array<score_data, 4> interpret_score_rank_data(stage_score_rank& stage) {
        auto ranks = stage.ranks;
        return std::array{
            score_data{ranks[0] * 100, "D"},
            score_data{ranks[1] * 100, "C"},
            score_data{ranks[2] * 100, "B"},
            score_data{ranks[3] * 100, "A"}
        };
    }

    std::array<score_data, 4> interpret_time_rank_data(stage_time_rank& stage) {
        auto ranks = stage.ranks;
        return std::array{
            score_data{ranks[0].total_seconds(), "D"},
            score_data{ranks[1].total_seconds(), "C"},
            score_data{ranks[2].total_seconds(), "B"},
            score_data{ranks[3].total_seconds(), "A"}
        };
    }
}
