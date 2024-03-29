#include <sonic_heroes/structs.hpp>
#include <sonic_heroes/data_extractor.hpp>
#include <variant>
#include <process.h>
#include <common.hpp>

namespace gc::sonic_heroes {
    constexpr int stall_time_milli = 2500;

    struct state {
        int level = -1;
        int team = -1;
        int mission = -1;

        bool operator<=>(const state& other) const = default;
    };

    struct sonic_heroes_data {
        using process_type = dolphin_process;
        using rank_array = std::array<score_data, 4>;
        using level_state = state;
        using calculation_temp = struct calculation_temp {
            std::array<score_data, 5> scores;
            score_data time;
            int total_score{};
            int high_mark;
        };
        using static_calculations = struct static_calculations {
            rank_array ranks;
            level_state level;
            stage_union stage{};
            unsigned result;
            explicit operator bool() const {
                return result != static_cast<unsigned>(-1);
            }
        };

        [[maybe_unused]] const static std::string display_name;
        const static std::pair<int, int> display_dimensions;
        const static std::chrono::milliseconds render_sleep;
        const static std::array<std::string, 5> score_names;

        static level_state read_level_state(process_type& game);
        static void read_stage_data(process_type& game, static_calculations& state);
        static void get_rank_data(native_process& game, static_calculations& state);
        static void load_rank_text(ox::sdl_instance& window, const static_calculations& state);
        static void draw_state(ox::sdl_instance& window, const static_calculations& state);
        static calculation_temp calculate_data(process_type& game, const static_calculations& state);
        static void draw_data(ox::sdl_instance& window, const static_calculations& state, const calculation_temp& calc);
    };

    [[noreturn]] void display_ranks(int pid);
    void display_ranksX(int pid);
}
