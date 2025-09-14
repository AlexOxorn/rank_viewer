#include <sonic_heroes/rank_view.hpp>
#include <process.h>
#include <rank.hpp>
#include <rankX.hpp>
#include <ox/formatting.h>
// #include <fmt/core.h>
#include <iostream>
#include <ox/canvas.h>
#include <display_rank.hpp>

namespace gc::sonic_heroes {
    [[noreturn]] void display_ranks(int pid) {
        dolphin_process dolphin{pid};
        stage_union buffer{};

        std::array<score_data, 4> ranks{};

        state current{-1, -1, -1};
        int result = 0;

        while(true) {
            usleep(stall_time_milli);
            state next{get_current_stage(dolphin), get_current_team(dolphin), get_current_mission(dolphin)};
            std::cout << std::flush;

            if(next != current) {
                std::cout << std::format("{}{}",
                    static_cast<const char*>(ox::format{ox::escape::reset}),
                    static_cast<const char*>(ox::clear_screen{ox::escape::all}));
                current = next;
                result = get_ranks(dolphin, current.level, current.team, current.mission, buffer);
                if((result & TIMED_LEVEL) != 0) {
                    if((result & BOSS_LEVEL) != 0) {
                        ranks = interpret_time_rank_data(buffer.boss_timed, current.team);
                    } else if ((result & EXTRA_MISSION) != 0) {
                        ranks = interpret_time_rank_data(buffer.extra_timed, current.team);
                    }
                } else {
                    if((result & EXTRA_MISSION) != 0) {
                        ranks = interpret_score_rank_data(buffer.extra, current.team);
                    } else {
                        ranks = interpret_score_rank_data(buffer.stage, current.team);
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
        state.result = get_ranks(game, state.level.level, state.level.team, state.level.mission, state.stage);
    }

    void data::get_rank_data([[maybe_unused]] native_process& game, data::static_calculations &state) {
        auto& [ranks, level, stage, result] = state;
        if((result & TIMED_LEVEL) != 0) {
            if((result & BOSS_LEVEL) != 0) {
                ranks = interpret_time_rank_data(stage.boss_timed, level.team);
            } else if ((result & EXTRA_MISSION) != 0) {
                ranks = interpret_time_rank_data(stage.extra_timed, level.team);
            }
        } else {
            if((result & EXTRA_MISSION) != 0) {
                ranks = interpret_score_rank_data(stage.extra, level.team);
            } else {
                ranks = interpret_score_rank_data(stage.stage, level.team);
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
