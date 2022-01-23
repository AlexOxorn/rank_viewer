#include <sa2/rank_view.hpp>
#include <dolphin_process.hpp>
#include <rank.hpp>
#include <rankX.hpp>
#include <ox/formatting.h>
#include <fmt/core.h>
#include <display_rank.hpp>

namespace sa2 {
    constexpr int stall_time_milli = 2500;

    [[noreturn]] void display_ranks(int pid) {
        process game{pid};
        stage_union buffer{};

        std::array<score_data, 4> s_ranks{};
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
                    s_ranks = interpret_time_rank_data(buffer.timed);
                } else {
                    s_ranks = interpret_score_rank_data(buffer.scored);
                }
            }

            if (result == -1)
                continue;

            if ((result & TIMED_LEVEL) != 0) {
                minute_second time = get_time(game);
                print_current_progress(t_ranks, {time.total_seconds(), {0xFF, 0xFF, 0xFF}, {0xFF, 0xFF, 0xFF}});
            } else {
                interpret_score(game);
                print_current_progress(s_ranks, interpret_score(game), 10000);
            }
        }
    }

    using data = sonic_adventure_2_data;
    using namespace std::chrono_literals;

    void display_ranksX(int pid) {
        ::display_ranksX<data>(pid);
    }

    const std::string data::display_name = "Sonic Adventure Ranks";
    const std::pair<int, int> data::display_dimensions = std::make_pair(1920, 160);
    const std::chrono::milliseconds data::render_sleep = 16ms;
    const std::array<std::string, 5> data::score_names{
            "Time Bonus",
            "Score",
    };

    data::level_state data::read_level_state(data::process_type &game) {
        return {get_current_level(game), get_current_mission(game), get_current_character(game)};
    }

    void data::read_stage_data(data::process_type &game,
                               data::static_calculations &state) {
        state.result = get_ranks(game, state.level.level, state.level.mission, state.level.character, state.stage);
    }

    void data::get_rank_data(process& game, data::static_calculations &state) {
        auto& [ranks, level, stage, result] = state;
        if((result & TIMED_LEVEL) != 0) {
            ranks = interpret_time_rank_data(stage.timed);
        } else {
            ranks = interpret_score_rank_data(stage.scored);
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
            minute_second time = get_time(game);
            int total_seconds = time.total_seconds();
            return {{}, {total_seconds, "", ox::named_colors::grey50}, total_seconds, ranks.back().score};
        } else {
            auto scores = interpret_score(game);
            auto score_values = std::ranges::views::transform(scores, &score_data::score);
            int total_score = std::accumulate(score_values.begin(), score_values.end(), 0);
            return {scores, {}, total_score, std::max(ranks.front().score, 10000)};
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
