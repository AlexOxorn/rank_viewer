#include <jsr/rank_view.hpp>
#include <process.h>
#include <rank.hpp>
#include <rankX.hpp>
#include <ox/formatting.h>
// #include <fmt/core.h>
#include <display_rank.hpp>

namespace jsr {
    const std::array<std::string, LAST> data::score_names{
            "Score",
            "Cans",
            "Health",
            "Max Health",
            "Time",
            "Final Score"
    };

    static constexpr std::array<ox::color, LAST> score_colors{
            ox::named_colors::bright_teal,
            ox::named_colors::grey30,
            ox::named_colors::maroon,
            ox::named_colors::maroon4,
            ox::named_colors::MediumAquamarine,
            ox::named_colors::bright_teal,
    };

    static score_data to_score_data(i32 s, std::string name, ox::color foreground) {
        return {.score = s, .name = name, .foreground = foreground};
    }

    static std::array<score_data, LAST> interpret_data(native_process& game) {
        std::array<score_data, LAST> to_return;

        int score = safe_get_score_tally(game).value_or(get_score(game));

        auto cans = get_cans(game) * 100;
        auto health = get_target_health(game);
        auto max = get_max_health(game);

        double h_precent = 100.0 * ((double)health/(double)max);
        i32 h_score = 30 * (i32)h_precent;
        i32 max_bonus = (health == max) ? 3000 : 0;

        int frames = safe_get_frames_remaining_dyn(game).value_or(get_frames_remaining(game));
        frames = std::max(frames, 0);
        int time_bonus = 30 * (frames/30);

        std::array<i32, LAST> scores{score, cans, h_score, max_bonus, time_bonus, 0};
        auto res = std::views::zip_transform(to_score_data, scores, data::score_names, score_colors);
        std::ranges::copy(res, to_return.begin());
        return to_return;
    }

    constexpr int stall_time_milli = 2500;

    data::level_state data::read_level_state(data::process_type& game) {
        return get_level_pointer(game);
    }

    void data::read_stage_data(data::process_type& game, data::static_calculations& state) {
        auto rank_values = safe_get_ranks(game);
        if (!rank_values) {
            state.type = -1;
            return;
        }
        state.level = get_level_pointer(game);
        state.type = (*rank_values)[1] > (*rank_values)[0] ? 0 : 1;
        state.score_rank_values = *rank_values;
    }

    void data::get_rank_data([[maybe_unused]] data::process_type& game, data::static_calculations& state) {
        auto& [level, ranks, scores, type] = state;
        if (type < 0)
            return;
        std::ranges::transform(scores, "DCBAS", ranks.begin(), [](i32 score, char rank) {
            return score_data{score, std::string{rank}};
        });
    }

    void data::load_rank_text(ox::sdl_instance& window, const data::static_calculations& state) {
        auto& [level, ranks, scores, type] = state;
        load_requirement_text(window, state.ranks);
    }

    data::calculation_temp data::calculate_data(data::process_type& game, const data::static_calculations& state) {
        auto& [level, ranks, score_req, type] = state;
        auto score_values = interpret_data(game);
        int total_score = std::accumulate(score_values.begin(), score_values.end(), 0);

        int manual = 30 * get_max_time(game) - get_frames_remaining(game);
        int time = safe_get_score_total(game).value_or(manual)/30;

        if (time == score_values[0].score) {
            time = manual/30;
        }

        return {score_values,
                score_data{time, "Time", ox::named_colors::bright_teal},
                total_score,
                score_req[NUMBER_OF_RANKS-1]};
    }

    using namespace std::chrono_literals;

    void display_ranksX(int pid) {
        ::display_ranksX<data>(pid);
    }

    void current_score(ox::sdl_instance& window, const data::static_calculations& state,
                       const data::calculation_temp& calc) {
        dimensions size = dimensions{rank_font_size, 5, 10 + rank_font_size, 0};
        auto& [level, ranks, score_req, type] = state;
        auto& [scores, time, score, high_mark] = calc;
        auto current_score = std::ranges::fold_left(scores, 0, std::plus<>());
        auto current_score_text = std::format("Current Score\t\t: {}", current_score);
        window.load_text("current_score", rank_font, rank_font_size, current_score_text, {255, 255, 255, 255});
        auto texture = window.get_texture("current_score");
        texture->render(size.left() + 120, size.top());
    }

    const std::string data::display_name = "Jet Set Radio Ranks";
    const std::pair<int, int> data::display_dimensions = std::make_pair(1920, 180);
    const std::chrono::milliseconds data::render_sleep = 16ms;
    void data::draw_state(ox::sdl_instance& window, const data::static_calculations& state) {
        auto& [level, ranks, score_req, type] = state;
        draw_score_text(window, ranks, dimensions{rank_font_size, 5, 10 + rank_font_size, 0});
    }
    void data::draw_data(ox::sdl_instance& window, const data::static_calculations& state,
                         const data::calculation_temp& calc) {
        auto& [level, ranks, score_req, type] = state;
        auto& [scores, time, score, high_mark] = calc;

        if (type == 0) {
            draw_score_progress_bar(window, scores, high_mark);
            draw_rank_markers_scores(window, state.ranks, score, high_mark);
        }
        else if (type == 1) {
            draw_score_progress_bar(window, std::span(&time, 1), ranks[1].score);
            draw_rank_markers_scores(window,
                                     state.ranks,
                                     time.score,
                                     ranks[1].score,
                                     dimensions{},
                                     std::less<int>{});
        }
        current_score(window, state, calc);
    }
} // namespace unleashed
