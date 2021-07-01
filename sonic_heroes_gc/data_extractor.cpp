#include "data_extractor.hpp"

constexpr int seaside_hill = 2;
constexpr int rail_canyon = 8;
constexpr int chaotix_rail_canyon = 36;
constexpr int final_fortress =15;
constexpr int egg_hawk = 16;
constexpr int metal_madness = 23;
constexpr int metal_overloard = 24;

constexpr int seconds_per_minute = 60;
constexpr int max_timebonus = 50000;
constexpr int per_second_timebonus_penalty = 80;
constexpr int max_timebonus_threashold = 90;
constexpr int points_per_level = 500;
constexpr int state_level_completed = 0xC;

int get_ranks(dolphin_process& process, int level, int team, int mission, void* buffer) {
    if (level != chaotix_rail_canyon && (level < seaside_hill || mission > 1 || level > metal_overloard)) {
        return -1;
    }

    // Metal Overloard
    level = level == metal_overloard ? metal_madness : level;
    // Chatorix Rail Canyon
    level = level == chaotix_rail_canyon ? rail_canyon : level;
    int offset = level - egg_hawk;

    if (level > final_fortress) {
        auto* rbuffer = reinterpret_cast<boss_timed_stages *>(buffer);
        process.read_memory(boss_times_ranks + sizeof(*rbuffer) * offset, rbuffer);
        rbuffer->from_endian();
        return BOSS_LEVEL | TIMED_LEVEL;
    }

    offset = level - seaside_hill;

    if (mission == 0) {
        // Chaotix extra rails canyon
        if (offset > rail_canyon - seaside_hill)
            offset++;
        auto* rbuffer = reinterpret_cast<normal_stages *>(buffer);
        process.read_memory(normal_stage_ranks + sizeof(*rbuffer) * offset, rbuffer);
        rbuffer->from_endian();
        return 0;
    }

    if (team == 0 || team == 3) {
        // Chaotix extra rails canyon
        if (offset >= rail_canyon - seaside_hill)
            offset++;
        auto* rbuffer = reinterpret_cast<extra_stages *>(buffer);
        process.read_memory(extra_stage_ranks + sizeof(*rbuffer) * offset, rbuffer);
        rbuffer->from_endian();
        return EXTRA_MISSION;
    }

    auto* rbuffer = reinterpret_cast<extra_timed_stages *>(buffer);
    process.read_memory(extra_times_ranks + sizeof(*rbuffer) * offset, rbuffer);
    rbuffer->from_endian();
    return EXTRA_MISSION | TIMED_LEVEL;
}

template<std::integral type = int>
int get_address(dolphin_process& process, u32 address) {
    type to_return;
    process.read_memory(address, &to_return);
    return to_return;
}

template<std::integral type = u32, int length = 3>
std::array<type, length> get_array_address(dolphin_process& process, u32 address) {
    std::array<type, length> to_return{};
    process.read_memory(address, &to_return);
    return to_return;
}

int get_level(dolphin_process& process) {

    int temp = get_address(process, stage_address);
    return temp;
}

int get_team(dolphin_process& process) {
    return get_address(process, team_address);
}

int get_mission(dolphin_process& process) {
    return get_address<u8>(process, extra_flag_address);
}

int get_state(dolphin_process& process) {
    return get_address(process, game_state);
}

std::array<u32, 3> get_score(dolphin_process& process) {
    return get_array_address(process, score_address);
}

std::array<u8, 3> get_time(dolphin_process& process) {
    return get_array_address<u8>(process, time_address);
}

std::array<u8, 3> get_cores(dolphin_process& process) {
    return get_array_address<u8>(process, character_levels);
}

std::array<score_data, 5> interpret_score(dolphin_process& process) {
    int state = get_state(process);
    std::array<u32, 3> scores = get_score(process);
    std::array<u8, 3> time = get_time(process);
    std::array<u8, 3> cores = get_cores(process);

    int seconds = time[0] * seconds_per_minute + time[1];
    int timebonus = max_timebonus - per_second_timebonus_penalty * seconds;
    int timebonus_rest = seconds <= max_timebonus_threashold ? max_timebonus - timebonus : 0;
    timebonus = timebonus < 0 ? 0 : timebonus;

    if (state != state_level_completed) {
        for(int i = 0; i < 3; i++) {
            scores.at(i) += points_per_level * cores.at(i);
        }
    }

    return std::array{
        score_data{timebonus, ox::format{ox::escape::background_white, ox::escape::white}},
        score_data{static_cast<int>(scores[0]), ox::format{ox::escape::background_blue, ox::escape::blue}},
        score_data{static_cast<int>(scores[1]), ox::format{ox::escape::background_yellow, ox::escape::yellow}},
        score_data{static_cast<int>(scores[2]), ox::format{ox::escape::background_red, ox::escape::red}},
        score_data{timebonus_rest, ox::format{ox::escape::reset, ox::escape::white}}
    };
}
