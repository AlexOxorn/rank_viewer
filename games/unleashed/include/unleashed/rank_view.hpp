#include <process.h>
#include <unleashed/structs.hpp>
#include <unleashed/data_extractor.hpp>

namespace unleashed {
    const static std::string display_name;
    const static std::pair<int, int> display_dimensions;
    const static std::chrono::milliseconds render_sleep{};
    const static std::array<std::string, 9> score_names;

    struct StageInfo {
        std::string level;
        u32 SRank;
        float TimeBonusStart;
        i32 TimeBonusScale;
        GameMode Mode;

        bool operator<=>(const StageInfo&) const = default;
    };

    struct data {
        using process_type = unleashed_process;
        using rank_array = std::array<score_data, 5>;
        using level_state = StageInfo;
        using calculation_temp = struct calculation_temp {
            std::array<score_data, 9> scores;
            int total_score{};
            int high_mark{};
        };
        using static_calculations = struct static_calculations {
            StageInfo level;
            rank_array ranks;
            unsigned result{};
            explicit operator bool() const {
                return result != static_cast<unsigned>(-1);
            }
        };

        const static std::string display_name;
        const static std::pair<int, int> display_dimensions;
        const static std::chrono::milliseconds render_sleep;
        const static std::array<std::string, 9> score_names;

        static level_state read_level_state(unleashed_process & game);
        static void read_stage_data(unleashed_process& game, static_calculations& state);
        static void get_rank_data(unleashed_process& game, static_calculations& state);
        static void load_rank_text(ox::sdl_instance& window, const static_calculations& state);
        static void draw_state(ox::sdl_instance& window, const static_calculations& state);
        static calculation_temp calculate_data(unleashed_process& game, const static_calculations& state);
        static void draw_data(ox::sdl_instance& window, const static_calculations& state, const calculation_temp& calc);
    };

    [[noreturn]] void display_ranks(int pid);
    void display_ranksX(int pid);
}
