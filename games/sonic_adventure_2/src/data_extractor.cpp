#include <sa2/data_extractor.hpp>
#include <helpers.hpp>

namespace sa2 {
    int get_ranks(process& process, int level, int mission, int character, void* buffer) {
        if (level == KartRoutes) {
            int char_offset = character == Characters_Rouge ? sizeof(stage_time_rank) * 5 : 0;
            auto* rbuffer = reinterpret_cast<stage_time_rank *>(buffer);
            process.read_memory(
                kart_mission_ranks_address + sizeof(*rbuffer) * mission + char_offset,
                rbuffer
            );
            return TIMED_LEVEL;
        }

        auto index = stage_index[level];
        if (index < 0) {
            return -1;
        }

        if (mission == 0 || mission == 3 || mission == 4) {
            auto* rbuffer = reinterpret_cast<stage_score_rank *>(buffer);
            process.read_memory(
                mission_rank_addresses.at(mission) + sizeof(*rbuffer) * index,
                rbuffer
            );
            return 0;
        }

        if (mission == 1 || mission == 2) {
            auto* rbuffer = reinterpret_cast<stage_time_rank *>(buffer);
            process.read_memory(
                mission_rank_addresses.at(mission) + sizeof(*rbuffer) * index,
                rbuffer
            );
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

    std::array<score_data, 4> interpret_score_rank_data(stage_score_rank* stage) {
        auto ranks = *reinterpret_cast<std::array<u16, 4> *>(&stage->ranks);
        return std::array{
            score_data{ranks[0] * 100, "D"},
            score_data{ranks[1] * 100, "C"},
            score_data{ranks[2] * 100, "B"},
            score_data{ranks[3] * 100, "A"}
        };
    }

    std::array<score_data, 4> interpret_time_rank_data(stage_time_rank* stage) {
        auto ranks = *reinterpret_cast<std::array<minute_second, 4> *>(&stage->ranks);
        return std::array{
            score_data{ranks[0].total_seconds(), "D"},
            score_data{ranks[1].total_seconds(), "C"},
            score_data{ranks[2].total_seconds(), "B"},
            score_data{ranks[3].total_seconds(), "A"}
        };
    }
}
