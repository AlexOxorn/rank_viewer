#include <shadow/rank_view.hpp>
#include <process.h>
#include <rank.hpp>
#include <rankX.hpp>
#include <ox/formatting.h>
#include <fmt/core.h>
#include <iostream>
#include <ox/canvas.h>
#include <display_rank.hpp>

namespace gc::shadow {
    using data = shadow_data;
    using namespace std::chrono_literals;

    void display_ranksX(int pid) {
        ::display_ranksX<data>(pid);
    }

    [[maybe_unused]] const std::string data::display_name = "Shadow Ranks";
    const std::pair<int, int> data::display_dimensions = std::make_pair(1920, 160);
    const std::chrono::milliseconds data::render_sleep = 16ms;
    const std::array<std::string, 5> data::score_names{
            "Time Bonus",
            "90s Bonus",
            "Normal",
            "Hero",
            "Dark"
    };

    data::level_state data::read_level_state(data::process_type &game) {
        return {get_current_stage(game), get_current_goal(game)};
    }

    void data::read_stage_data(data::process_type &game,
                                            data::static_calculations &state) {
        state.result = get_ranks(game, state.level.level, state.stage);
    }

    void data::get_rank_data(data::process_type& game, data::static_calculations &state) {
        auto& [ranks, time_ranks, level, stage, result] = state;
        if((result & TIMED_LEVEL) != 0) {
            time_ranks = interpret_time_rank_data(&stage.boss);
        } else {
            ranks = interpret_score_rank_data(&stage.stage);
        }
    }

    void data::load_rank_text(ox::sdl_instance &window, const data::static_calculations &state) {
        auto& [ranks, time_ranks, level, stage, result] = state;
        if ((result & TIMED_LEVEL) != 0) {
            load_requirement_text(window, state.time_ranks, min_second_formatter{});
        } else {
            load_requirement_text(window, state.ranks[level.goal]);
        }
    }

    void data::draw_state(ox::sdl_instance &window, const data::static_calculations &state) {
        draw_score_text(window, state.ranks[state.level.goal]);
    }

    data::calculation_temp data::calculate_data(data::process_type &game, const data::static_calculations &state) {
        auto& [ranks, time_rank, level, stage, result] = state;
        if ((result & TIMED_LEVEL) != 0) {
            float time = get_current_time(game);
            int total_seconds = static_cast<int>(time);
            return {{}, {total_seconds, "", ox::named_colors::grey50}, total_seconds, time_rank.back().score};
        } else {
            auto scores = interpret_score(game);
            score_data penalty{};
            switch (level.goal) {
                case 0:
                    penalty = {
                            .score = -1 * scores[3].score,
                            .foreground = scores[3].foreground
                    };
                    scores[3].score *= 0;
                    break;
                case 1:
                    scores[3].score = 0;
                    scores[4].score = 0;
                    break;
                case 2:
                    penalty = {
                            .score = -1 * scores[4].score,
                            .foreground = scores[4].foreground
                    };
                    scores[4].score *= 0;
                    break;
                default:
                    break;
            }

            std::ranges::stable_partition(scores, [](int i) {return i >= 0;}, &score_data::score);
//            auto score_values = std::ranges::views::transform(scores, &score_data::score);

            auto score = std::accumulate(scores.begin(), scores.end(), 0);

            auto max_element = std::ranges::max_element(ranks, std::less{}, [](auto a){return a.front().score;});

            return {scores, penalty, score + penalty, std::max(max_element->front().score, 50000)};
        }
    }

    void data::draw_data(ox::sdl_instance &window, const data::static_calculations &state, const data::calculation_temp &calc) {
        auto& [ranks, time_ranks, level, stage, result] = state;
        auto& [scores, time, total, high_mark] = calc;

        if (result & TIMED_LEVEL) {
            draw_score_progress_bar(window, std::span(&time, 1), high_mark);
            draw_rank_markers_scores(window, time_ranks, total, high_mark, dimensions{}, std::less_equal<int>{});
        } else {
            int end_point = draw_score_progress_bar(window, scores, high_mark);
            draw_score_progress_bar(window, {&time, 1}, high_mark, {.height = rank_font_size - 10, .start_x = end_point, .start_y = 5}, false);
            draw_rank_markers_scores(window, ranks[level.goal], total, high_mark);
        }
    }
}
