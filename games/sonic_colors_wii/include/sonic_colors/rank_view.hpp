#pragma once

#include <compare>
#include <process.h>
#include <sonic_colors/structs.hpp>
#include <common.hpp>

namespace gc::sonic_colors {
    constexpr int stall_time_milli = 2500;

    struct state {
        int zone = -1;
        int act = -1;

        bool operator<=>(const state& other) const = default;
    };

    struct sonic_colors_data {
        using process_type = dolphin_process;
        using stage_data = stage_data_struct;
        using rank_array = std::array<score_data, 4>;
        using level_state = state;
        using calculation_temp = struct calculation_temp {
            std::array<score_data, 28> scores;
            int total_score{};
        };
        using static_calculations = struct static_calculations {
            rank_array ranks;
            level_state level;
            stage_data stage{};
            explicit operator bool() {
                return true;
            }
        };
        
        const static std::string display_name;
        const static std::pair<int, int> display_dimensions;
        const static std::chrono::milliseconds render_sleep;
        const static std::array<std::string, 28> score_names;

        static level_state read_level_state(process_type& game);
        static void read_stage_data(process_type& game, static_calculations& state);
        static void get_rank_data(process_type&, static_calculations& state);
        static void load_rank_text(ox::sdl_instance& window, const static_calculations& state);
        static void draw_state(ox::sdl_instance& window, const static_calculations& state);
        static calculation_temp calculate_data(process_type& game, const static_calculations& state);
        static void draw_data(ox::sdl_instance& window, const static_calculations& state, const calculation_temp& calculations);
    };

    void display_ranks(int pid);
    void display_ranksX(int pid);
}
