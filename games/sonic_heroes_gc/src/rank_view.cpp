#include <sonic_heroes/rank_view.hpp>
#include <dolphin_process.hpp>
#include <rank.hpp>
#include <rankX.hpp>
#include <ox/formatting.h>
#include <sonic_heroes/data_extractor.hpp>
#include <fmt/core.h>
#include <iostream>
#include <ox/canvas.h>
#include <display_rank.hpp>

namespace gc::sonic_heroes {
    [[noreturn]] void display_ranks(int pid) {
        dolphin_process dolphin{pid};
        normal_stages prototype{};
        void* buffer = &prototype;

        std::array<score_data, 4> ranks{};

        state current{-1, -1, -1};
        int result = 0;

        while(true) {
            usleep(stall_time_milli);
            state next{get_current_stage(dolphin), get_current_team(dolphin), get_current_mission(dolphin)};
            std::cout << std::flush;

            if(next != current) {
                fmt::print("{}{}", ox::format{ox::escape::reset}, ox::clear_screen{ox::escape::all});
                current = next;
                result = get_ranks(dolphin, current.level, current.team, current.mission, buffer);
                if((result & TIMED_LEVEL) != 0) {
                    if((result & BOSS_LEVEL) != 0) {
                        ranks = interpret_time_rank_data(reinterpret_cast<boss_timed_stages *>(buffer), current.team);
                    } else if ((result & EXTRA_MISSION) != 0) {
                        ranks = interpret_time_rank_data(reinterpret_cast<extra_timed_stages *>(buffer), current.team);
                    }
                } else {
                    if((result & EXTRA_MISSION) != 0) {
                        ranks = interpret_score_rank_data(reinterpret_cast<extra_stages *>(buffer), current.team);
                    } else {
                        ranks = interpret_score_rank_data(reinterpret_cast<normal_stages *>(buffer), current.team);
                    }
                }
            }

            if (result == -1)
                continue;

            if ((result & TIMED_LEVEL) != 0) {
//                std::array<u8, 3> time = get_current_time(dolphin);
//                print_current_progress(ranks, {time[0] * 60 + time[1], "TIME", ox::named_colors::grey50});
            } else {
                interpret_score(dolphin);
                print_current_progress(ranks, interpret_score(dolphin), 50000);
            }
        }
    }

    /*
    void display_ranksX(int pid) {
        using namespace std::chrono_literals;

        dolphin_process dolphin{pid};
        normal_stages prototype{};
        void* buffer = &prototype;
        std::array<score_data, 4> ranks{};
        state current{-1, -1, -1};
        int result = 0;

        SDL_Event e;
        ox::sdl_instance rank_display{"Sonic Hereos Ranks", true, {1920, 160}, {10, 10}};
        const std::chrono::milliseconds render_sleep = 16ms;
        bool quit = false;

        rank_display.load_text("Time Bonus", rank_font, rank_font_size, "Time Bonus");
        rank_display.load_text("Speed Score", rank_font, rank_font_size, "Speed Score");
        rank_display.load_text("Fly Score", rank_font, rank_font_size, "Fly Score");
        rank_display.load_text("Power Score", rank_font, rank_font_size, "Power Score");
        rank_display.load_text("90s Bonus", rank_font, rank_font_size, "90s Bonus");
        load_rank_images(rank_display);

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
            state next{get_current_stage(dolphin), get_current_team(dolphin), get_current_mission(dolphin)};
            rank_display.redraw();

            if(next != current) {
                current = next;
                result = get_ranks(dolphin, current.level, current.team, current.mission, buffer);
                if((result & TIMED_LEVEL) != 0) {
                    if((result & BOSS_LEVEL) != 0) {
                        ranks = interpret_time_rank_data(reinterpret_cast<boss_timed_stages *>(buffer), current.team);
                        load_requirement_text(rank_display, ranks);
                    } else if ((result & EXTRA_MISSION) != 0) {
                        ranks = interpret_time_rank_data(reinterpret_cast<extra_timed_stages *>(buffer), current.team);
                        load_requirement_text(rank_display, ranks);
                    }
                } else {
                    if((result & EXTRA_MISSION) != 0) {
                        ranks = interpret_score_rank_data(reinterpret_cast<extra_stages *>(buffer), current.team);
                        load_requirement_text(rank_display, ranks);
                    } else {
                        ranks = interpret_score_rank_data(reinterpret_cast<normal_stages *>(buffer), current.team);
                        load_requirement_text(rank_display, ranks);
                    }
                }
            }

            if (result == -1) {
                std::this_thread::sleep_until(end);
                continue;
            }

            if ((result & TIMED_LEVEL) != 0) {
//                std::array<u8, 3> time = get_current_time(dolphin);
//                draw_time_progress(rank_display, ranks, {time[0] * 60 + time[1], ox::named_colors::grey50});
            } else {
                auto score = interpret_score(dolphin);
                draw_score_progress(rank_display, ranks, score, 50000);
            }
            std::this_thread::sleep_until(end);
        }
    }
*/

    using data = sonic_heroes_data;
    using namespace std::chrono_literals;

    void display_ranksX(int pid) {
        ::display_ranksX<data>(pid);
    }

    [[maybe_unused]] const std::string data::display_name = "Sonic Heroes Ranks";
    const std::pair<int, int> data::display_dimensions = std::make_pair(1920, 160);
    const std::chrono::milliseconds data::render_sleep = 16ms;
    const std::array<std::string, 5> data::score_names{
            "Time Bonus",
            "Speed Score",
            "Fly Score",
            "Power Score",
            "90s Bonus"
    };

    data::level_state data::read_level_state(data::process_type &game) {
        return {get_current_stage(game), get_current_team(game), get_current_mission(game)};
    }

    void data::read_stage_data(data::process_type &game,
                                            data::static_calculations &state) {
        state.result = get_ranks(game, state.level.level, state.level.team, state.level.mission, &state.stage);
    }

    void data::get_rank_data(process& game, data::static_calculations &state) {
        auto& [ranks, level, stage, result] = state;
        if((result & TIMED_LEVEL) != 0) {
            if((result & BOSS_LEVEL) != 0) {
                ranks = interpret_time_rank_data(&stage.boss_time, level.team);
            } else if ((result & EXTRA_MISSION) != 0) {
                ranks = interpret_time_rank_data(&stage.extra_timed, level.team);
            }
        } else {
            if((result & EXTRA_MISSION) != 0) {
                ranks = interpret_score_rank_data(&stage.extra_stage, level.team);
            } else {
                ranks = interpret_score_rank_data(&stage.normal_stage, level.team);
            }
        }
        std::reverse(ranks.begin(), ranks.end());
    }

    void data::load_rank_text(ox::sdl_instance &window, const data::static_calculations &state) {
        auto& [ranks, level, stage, result] = state;
        if ((result & TIMED_LEVEL) != 0) {
            load_requirement_text(window, state.ranks, min_second_formatter{});
        } else {
            load_requirement_text(window, state.ranks);
        }
    }

    void data::draw_state(ox::sdl_instance &window, const data::static_calculations &state) {
        draw_score_text(window, state.ranks);
    }

    data::calculation_temp data::calculate_data(data::process_type &game, const data::static_calculations &state) {
        auto& [ranks, level, stage, result] = state;
        if ((result & TIMED_LEVEL) != 0) {
            auto time = get_current_time(game);
            int total_seconds = time[0] * 60 + time[1];
            return {{}, {total_seconds, "", ox::named_colors::grey50}, total_seconds, ranks.back().score};
        } else {
            auto scores = interpret_score(game);
            auto score_values = std::ranges::views::transform(scores, &score_data::score);
            int total_score = std::accumulate(score_values.begin(), score_values.end(), 0);
            return {scores, {}, total_score, std::max(ranks.front().score, 50000)};
        }
    }

    void data::draw_data(ox::sdl_instance &window, const data::static_calculations &state, const data::calculation_temp &calc) {
        auto& [ranks, level, stage, result] = state;
        auto& [scores, time, total_score, high_mark] = calc;

        if (result & TIMED_LEVEL) {
            draw_score_progress_bar(window, std::span(&time, 1), high_mark);
            draw_rank_markers_scores(window, state.ranks, total_score, high_mark, dimensions{}, std::less_equal<int>{});
        } else {
            draw_score_progress_bar(window, scores, high_mark);
            draw_rank_markers_scores(window, state.ranks, total_score, high_mark);
        }
    }
}
