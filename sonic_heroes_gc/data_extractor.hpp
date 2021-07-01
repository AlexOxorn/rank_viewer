#pragma once
#include "structs.hpp"
#include "variables.hpp"
#include <concepts>
#include "../memory/dolphin_process.hpp"
#include <ox/formating.h>
#include "../rank.hpp"

constexpr int EXTRA_MISSION = 1 << 1;
constexpr int BOSS_LEVEL = 1 << 2;
constexpr int TIMED_LEVEL = 1 << 3;

int get_ranks(dolphin_process& process, int level, int team, int mission, void* buffer);

int get_level(dolphin_process& process);
int get_team(dolphin_process& process);
int get_mission(dolphin_process& process);
int get_state(dolphin_process& process);
std::array<u32, 3> get_score(dolphin_process& process);
std::array<u8, 3> get_time(dolphin_process& process);
std::array<u8, 3> get_cores(dolphin_process& process);
std::array<score_data, 5> interpret_score(dolphin_process& process);

template<typename rank_type> requires std::is_same_v<rank_type, normal_stages> || std::is_same_v<rank_type, extra_stages>
std::array<rank_data, 4> interpret_score_rank_data(dolphin_process& process, rank_type* stage, int team) {
    if constexpr (std::is_same_v<rank_type, extra_stages>) {
        team = team > 0;
    }
    auto ranks = *reinterpret_cast<std::array<u16, 4> *>(&stage->ranks_array[team]);

    return std::array{
        rank_data{ranks[0] * 100, "D"},
        rank_data{ranks[1] * 100, "B"},
        rank_data{ranks[2] * 100, "C"},
        rank_data{ranks[3] * 100, "A"}
    };
}

template<typename rank_type> requires std::is_same_v<rank_type, extra_timed_stages> || std::is_same_v<rank_type, boss_timed_stages>
std::array<time_rank_data, 4> interpret_time_rank_data(dolphin_process& process, rank_type* stage, int team) {
    if constexpr (std::is_same_v<rank_type, extra_timed_stages>) {
        team = team - 1;
    }
    auto ranks = *reinterpret_cast<std::array<std::array<u8, 2>, 4> *>(&stage->ranks_array[team]);
    return std::array{
        time_rank_data{ranks[0][0] * 60 + ranks[0][1], "D"},
        time_rank_data{ranks[1][0] * 60 + ranks[1][1], "C"},
        time_rank_data{ranks[2][0] * 60 + ranks[2][1], "B"},
        time_rank_data{ranks[3][0] * 60 + ranks[3][1], "A"}
    };
}
