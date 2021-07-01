// #pragma once
// #include "structs.hpp"
// #include "variables.hpp"
// #include <concepts>
// #include "../memory/dolphin_process.hpp"
// #include <ox/formating.h>
// #include "../rank.hpp"

// constexpr int EXTRA_MISSION = 1 << 1;
// constexpr int BOSS_LEVEL = 1 << 2;
// constexpr int TIMED_LEVEL = 1 << 3;

// int get_ranks(dolphin_process& process, int level, int team, int mission, void* buffer);

// int get_level(dolphin_process& process);
// int get_team(dolphin_process& process);
// int get_mission(dolphin_process& process);
// int get_state(dolphin_process& process);
// std::array<u32, 3> get_score(dolphin_process& process);
// std::array<u8, 3> get_time(dolphin_process& process);
// std::array<u8, 3> get_cores(dolphin_process& process);
// std::array<score_data, 4> interpret_score(dolphin_process& process);

// template<typename rank_type> requires std::is_same_v<rank_type, normal_stages> || std::is_same_v<rank_type, extra_stages>
// score_rank<4> interpret_score_rank_data(dolphin_process& process, rank_type* stage, int team) {
// } 

// template<typename rank_type> requires std::is_same_v<rank_type, extra_timed_stages> || std::is_same_v<rank_type, boss_timed_stages>
// time_rank<4> interpret_time_rank_data(dolphin_process& process, rank_type* stage, int team) {
// } 