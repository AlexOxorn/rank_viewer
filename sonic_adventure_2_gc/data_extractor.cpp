// #include "data_extractor.hpp"

// int get_ranks(dolphin_process& process, int level, int team, int mission, void* buffer) {
//     if (level != 36 && (level < 2 || mission > 1 || level > 24 || level <= 1)) {
//         return -1;
//     }
//     // Metal Overloard
//     level = level == 24 ? 23 : level;
//     // Chatorix Rail Canyon
//     level = level == 36 ? 8 : level;
//     int offset = level - 16;

//     if (level > 15) {
//         boss_timed_stages* rbuffer = reinterpret_cast<boss_timed_stages *>(buffer);
//         process.read_memory(boss_times_ranks + sizeof(*rbuffer) * offset, rbuffer);
//         rbuffer->from_endian();
//         return BOSS_LEVEL | TIMED_LEVEL;
//     }

//     offset = level - 2;

//     if (mission == 0) {
//         // Chaotix extra rails canyon
//         if (offset >= 9)
//             offset++;
//         normal_stages* rbuffer = reinterpret_cast<normal_stages *>(buffer);
//         process.read_memory(normal_stage_ranks + sizeof(*rbuffer) * offset, rbuffer);
//         rbuffer->from_endian();
//         return 0;
//     }

//     if (team == 0 || team == 3) {
//         // Chaotix extra rails canyon
//         if (offset >= 9)
//             offset++;
//         extra_stages* rbuffer = reinterpret_cast<extra_stages *>(buffer);
//         process.read_memory(extra_stage_ranks + sizeof(*rbuffer) * offset, rbuffer);
//         rbuffer->from_endian();
//         return EXTRA_MISSION;
//     }

//     extra_timed_stages* rbuffer = reinterpret_cast<extra_timed_stages *>(buffer);
//     process.read_memory(extra_times_ranks + sizeof(*rbuffer) * offset, rbuffer);
//     rbuffer->from_endian();
//     return EXTRA_MISSION | TIMED_LEVEL;
// }

// template<std::integral type = int>
// int get_address(dolphin_process& process, u32 address) {
//     type to_return;
//     process.read_memory(address, &to_return);
//     return to_return;
// }

// template<std::integral type = u32, int length = 3>
// std::array<type, length> get_array_address(dolphin_process& process, u32 address) {
//     std::array<type, length> to_return;
//     process.read_memory(address, &to_return);
//     return to_return;
// }

// int get_level(dolphin_process& process) {

//     int temp = get_address(process, stage_address);
//     return temp;
// }

// int get_team(dolphin_process& process) {
//     return get_address(process, team_address);
// }

// int get_mission(dolphin_process& process) {
//     return get_address<u8>(process, extra_flag_address);
// }

// int get_state(dolphin_process& process) {
//     return get_address(process, game_state);
// }

// std::array<u32, 3> get_score(dolphin_process& process) {
//     return get_array_address(process, score_address);
// }

// std::array<u8, 3> get_time(dolphin_process& process) {
//     return get_array_address<u8>(process, time_address);
// }

// std::array<u8, 3> get_cores(dolphin_process& process) {
//     return get_array_address<u8>(process, character_levels);
// }

// std::array<score_data, 4> interpret_score(dolphin_process& process) {
//     int state = get_state(process);
//     std::array<u32, 3> scores = get_score(process);
//     std::array<u8, 3> time = get_time(process);
//     std::array<u8, 3> cores = get_cores(process);

//     // printf("%08x, %08x, %08x\n", scores[0], scores[1], scores[2]);

//     int seconds = time[0] * 60 + time[1];
//     int timebonus = seconds <= 90 ? 50000 : 50000 - 80 * seconds;

//     if (state != 0xC) {
//         for(int i = 0; i < 3; i++) {
//             scores[i] += 500 * cores[i];
//         }
//     }

//     return std::array<score_data, 4>{
//         score_data{static_cast<int>(scores[0]), ox::format{ox::escape::background_blue, ox::escape::blue}},
//         score_data{static_cast<int>(scores[1]), ox::format{ox::escape::background_yellow, ox::escape::yellow}},
//         score_data{static_cast<int>(scores[2]), ox::format{ox::escape::background_red, ox::escape::red}},
//         score_data{timebonus, ox::format{ox::escape::background_white, ox::escape::white}}
//     };
// }
