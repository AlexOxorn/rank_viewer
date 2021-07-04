#include <sa2/data_extractor.hpp>

namespace sa2 {
    int get_ranks(process& process, int level, int mission, void* buffer) {
        auto index_iter = stage_index.find(level);
        if (index_iter == stage_index.end()) {
            return -1;
        }

        int index = index_iter->second;

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

    int get_level(process& process) {
        int temp = get_address(process, current_level_address);
        return temp;
    }

    int get_mission(process& process) {
        return get_address<u8>(process, current_mission_address);
    }

    int get_score(process& process) {
        return get_address(process, score_address);
    }

    min_second get_time(process& process) {
        return get_address<min_second>(process, time_address);
    }

    std::array<score_data, 2> interpret_score(process& process) {
        int score = get_score(process);
        min_second time = get_time(process);

        int seconds = time.minutes * 60 + time.seconds;
        int timebonus = seconds < 90 ? 10000 : 11200 - (seconds) * 20;
        timebonus = timebonus < 0 ? 0 : timebonus;

        return std::array{
            score_data{timebonus, ox::format{ox::escape::background_cyan, ox::escape::cyan}},
            score_data{score, ox::format{ox::escape::background_blue, ox::escape::blue}},
        };
    }

    std::array<rank_data, 4> interpret_score_rank_data(process& process, stage_score_rank* stage) {
        auto ranks = *reinterpret_cast<std::array<u16, 4> *>(&stage->ranks);
        return std::array{
            rank_data{ranks[0] * 100, "D"},
            rank_data{ranks[1] * 100, "B"},
            rank_data{ranks[2] * 100, "C"},
            rank_data{ranks[3] * 100, "A"}
        };
    }

    std::array<time_rank_data, 4> interpret_time_rank_data(process& process, stage_time_rank* stage) {
        auto ranks = *reinterpret_cast<std::array<min_second, 4> *>(&stage->ranks);
        return std::array{
            time_rank_data{ranks[0].total_second(), "D"},
            time_rank_data{ranks[1].total_second(), "C"},
            time_rank_data{ranks[2].total_second(), "B"},
            time_rank_data{ranks[3].total_second(), "A"}
        };
    }
}
