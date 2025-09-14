#include <process.h>
#include <jsr/structs.hpp>
#include <jsr/data_extractor.hpp>

namespace jsr {
    enum ScoreType {
        Score,
        CanBonus,
        HealthBonus,
        MaxHealthBonus,
        TimeBonus,
        Final,
        LAST
    };

    const static std::string display_name;
    const static std::pair<int, int> display_dimensions;
    const static std::chrono::milliseconds render_sleep{};
    const static std::array<std::string, 6> score_names;

    using StageInfo = u64;

    struct data {
        using process_type = native_process;
        using rank_array = std::array<score_data, NUMBER_OF_RANKS>;
        using level_state = StageInfo;
        using calculation_temp = struct calculation_temp {
            std::array<score_data, LAST> scores;
            score_data time_since_start{};
            int total_score{};
            int high_mark{};
        };
        using static_calculations = struct static_calculations {
            level_state level;
            rank_array ranks;
            std::array<i32, NUMBER_OF_RANKS> score_rank_values;
            i32 type;
            explicit operator bool() const {
                return type >= 0;
            }
        };

        const static std::string display_name;
        const static std::pair<int, int> display_dimensions;
        const static std::chrono::milliseconds render_sleep;
        const static std::array<std::string, LAST> score_names;

        static level_state read_level_state(process_type & game);
        static void read_stage_data(process_type& game, static_calculations& state);
        static void get_rank_data(process_type& game, static_calculations& state);
        static void load_rank_text(ox::sdl_instance& window, const static_calculations& state);
        static void draw_state(ox::sdl_instance& window, const static_calculations& state);
        static calculation_temp calculate_data(process_type& game, const static_calculations& state);
        static void draw_data(ox::sdl_instance& window, const static_calculations& state, const calculation_temp& calc);
    };

    [[noreturn]] void display_ranks(int pid);
    void display_ranksX(int pid);
}
