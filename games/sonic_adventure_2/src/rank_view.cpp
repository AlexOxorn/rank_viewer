#include <sa2/rank_view.hpp>
#include <dolphin_process.hpp>
#include <rank.hpp>
#include <rankX.hpp>
#include <ox/formatting.h>
#include <sa2/data_extractor.hpp>
#include <fmt/core.h>

namespace sa2 {
    struct state {
        int level;
        int mission;
        int character;

        auto operator<=>(const state& other) const = default;
    };
    constexpr int stall_time_milli = 2500;

    [[noreturn]] void display_ranks(int pid) {
        process game{pid};
        stage_score_rank prototype{};
        void* buffer = &prototype;

        std::array<rank_data, 4> s_ranks{};
        std::array<time_rank_data, 4> t_ranks{};

        state current{-1, -1, -1};
        int result = 0;

        while(true) {
            usleep(stall_time_milli);
            state next{get_current_level(game), get_current_mission(game), get_current_character(game)};
            std::cout << std::flush;

            if(next != current) {
                fmt::print("{}{}", ox::format{ox::escape::reset}, ox::clear_screen{ox::escape::all});
                current = next;
                result = get_ranks(game, current.level, current.mission, current.character, buffer);
                if((result & TIMED_LEVEL) != 0) {
                    t_ranks = interpret_time_rank_data(reinterpret_cast<stage_time_rank *>(buffer));
                } else {
                    s_ranks = interpret_score_rank_data(reinterpret_cast<stage_score_rank *>(buffer));
                }
            }

            if (result == -1)
                continue;

            if ((result & TIMED_LEVEL) != 0) {
                minute_second time = get_time(game);
                print_current_progress(t_ranks, {time.total_seconds(), {{0xFF, 0xFF, 0xFF}}, {{0xFF, 0xFF, 0xFF}}});
            } else {
                interpret_score(game);
                print_current_progress(s_ranks, interpret_score(game), 10000);
            }
        }
    }

    void load_requirement_text(ox::sdl_instance& win, std::array<rank_data, 4>& s_ranks) {
        for (auto& rank : s_ranks) {
            win.load_text(fmt::format("{}_text", rank.name), rank_font, rank_font_size, fmt::format("{}: {}", rank.name, rank.score), {255, 255, 255, 255});
        }
    }

    void load_requirement_text(ox::sdl_instance& win, std::array<time_rank_data, 4>& t_ranks) {
        for (auto& rank : t_ranks) {
            win.load_text(fmt::format("{}_text", rank.name), rank_font, rank_font_size, fmt::format("{}: {}m {}s", rank.name, rank.seconds / 60, rank.seconds % 60), {255, 255, 255, 255});
        }
    }

    void display_ranksX(int pid) {
        using namespace std::chrono_literals;

        process game{pid};
        stage_score_rank prototype{};
        void* buffer = &prototype;

        std::array<rank_data, 4> s_ranks{};
        std::array<time_rank_data, 4> t_ranks{};

        state current{-1, -1, -1};
        int result = 0;

        ox::sdl_instance rank_display{"Sonic Adventure 2 Ranks", true, {1920, 160}};
        const std::chrono::milliseconds render_sleep = 16ms;
        SDL_Event e;
        bool quit = false;

        rank_display.load_text("Time Bonus", rank_font, rank_font_size, "Time Bonus");
        rank_display.load_text("Score", rank_font, rank_font_size, "Score");

        while(!quit) {
            ox::sdl_check_error();
            auto now = std::chrono::steady_clock::now();
            auto end = now + render_sleep;
            while(SDL_PollEvent( &e )) {
                switch (e.type) {
                case SDL_QUIT:
                    quit = true;
                    continue;
                }
            }

            state next{get_current_level(game), get_current_mission(game), get_current_character(game)};
            rank_display.redraw();

            if(next != current) {
                current = next;
                result = get_ranks(game, current.level, current.mission, current.character, buffer);
                if((result & TIMED_LEVEL) != 0) {
                    t_ranks = interpret_time_rank_data(reinterpret_cast<stage_time_rank *>(buffer));
                    load_requirement_text(rank_display, t_ranks);
                } else {
                    s_ranks = interpret_score_rank_data(reinterpret_cast<stage_score_rank *>(buffer));
                    load_requirement_text(rank_display, s_ranks);
                }
            }

            if (result == -1) {
                std::this_thread::sleep_until(end);
                continue;
            }

            if ((result & TIMED_LEVEL) != 0) {
                minute_second time = get_time(game);
                draw_time_progress(rank_display, t_ranks, {time.total_seconds(), ox::named_colors::grey50});
            } else {
                draw_score_progress(rank_display, s_ranks, interpret_score(game), 10000);
            }

            std::this_thread::sleep_until(end);
        }
    }
}
