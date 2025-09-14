#include <unleashed/rank_view.hpp>
#include <process.h>
#include <rank.hpp>
#include <rankX.hpp>
#include <ox/formatting.h>
// #include <fmt/core.h>
#include <display_rank.hpp>

namespace unleashed {
    constexpr int stall_time_milli = 2500;

    data::level_state data::read_level_state(data::process_type& game) {
        auto data = get_score_data(game);
        auto level_name = get_stage_name(game);
        return {level_name.data(),
                data.SRank,
                data.TimeBonusStart,
                data.TimeBonusScale,
                data.Mode,
                get_is_loading(game)};
    }

    void data::read_stage_data(data::process_type& game, data::static_calculations& state) {
        if (state.level.loading)
            state.result = -1;
        else if (get_game_mode(game) != STAGE)
            state.result = -1;
        else if (state.level.SRank == 0)
            state.result = -1;
        else if (state.level.level.contains("BossDarkGaia") and !state.level.level.contains("Moray"))
            state.result = -1;
        else
            state.result = 0;
    }

    void data::get_rank_data(data::process_type& game, data::static_calculations& state) {
        auto& [level, ranks, result] = state;
        if (!level.level.empty())
            printf("stage_name: %s\n", level.level.c_str());
        std::ranges::transform(get_rank_values(game), "SABCD", ranks.begin(), [](i32 score, char rank) {
            return score_data{score, std::string{rank}};
        });
    }

    void data::load_rank_text(ox::sdl_instance& window, const data::static_calculations& state) {
        auto& [level, ranks, result] = state;
        load_requirement_text(window, state.ranks);
        window.load_text("time_bonus_limit",
                         rank_font,
                         rank_font_size,
                         hour_min_second_formatter()("Time Bonus Limit\t\t", (int) state.level.TimeBonusStart),
                         {255, 255, 255, 255});
        window.load_text("time_bonus_factor",
                         rank_font,
                         rank_font_size,
                         std::format("Time Bonus/second\t\t: {}", state.level.TimeBonusScale),
                         {255, 255, 255, 255});
    }

    data::calculation_temp data::calculate_data(data::process_type& game, const data::static_calculations& state) {
        auto& [level, ranks, result] = state;
        auto score_data = get_score_data(game);
        auto [scores, data] = interpret_data(game);
        auto score_values = std::ranges::views::transform(scores, &score_data::score);
        int total_score = std::accumulate(score_values.begin(), score_values.end(), 0);
        return {scores, total_score, std::max(int(data.SRank), int(data.TimeBonusScale * data.TimeBonusStart)), data};
    }

    using namespace std::chrono_literals;

    void display_ranksX(int pid) {
        ::display_ranksX<data>(pid);
    }

    void draw_time_bonus_factors(ox::sdl_instance& win, const std::span<const score_data> scores,
                                 dimensions size = dimensions{rank_font_size, 5, 10 + rank_font_size, 0}) {
        draw_score_text_horizontal(win, scores, size);
        size.start_y += size.height;
        auto limit_text = win.get_texture("time_bonus_limit");
        auto factor_text = win.get_texture("time_bonus_factor");

        limit_text->render(size.left(), size.top());
        factor_text->render(size.left(), size.top() + size.height);
    }

    void draw_time_remaining(ox::sdl_instance& window, const data::static_calculations& state,
                             const data::calculation_temp& calc) {
        dimensions size = dimensions{rank_font_size, 5, 10 + rank_font_size, 0};
        auto& [level, ranks, result] = state;
        auto& [scores, score, high_mark, data] = calc;
        auto remain = int(state.level.SRank) - std::ranges::fold_left(scores, 0, std::plus<>());
        auto remain_abs = std::abs(remain);
        auto time_remaining_text = hour_min_second_milli_formatter()("Time Until S Rank\t\t",
                                                                     double(remain_abs) / state.level.TimeBonusScale);
        window.load_text("time_remaining",
                         rank_font,
                         rank_font_size,
                         time_remaining_text,
                         {255, u8(remain > 0 ? 0 : 255), u8(remain > 0 ? 0 : 255), 255});
        auto texture = window.get_texture("time_remaining");
        texture->render(size.left() + 400, size.top() + size.height * 2);
    }
    void current_score(ox::sdl_instance& window, const data::static_calculations& state,
                       const data::calculation_temp& calc) {
        dimensions size = dimensions{rank_font_size, 5, 10 + rank_font_size, 0};
        auto& [level, ranks, result] = state;
        auto& [scores, score, high_mark, data] = calc;
        auto current_score = std::ranges::fold_left(scores, 0, std::plus<>());
        auto current_score_text = std::format("Current Score\t\t: {}", current_score);
        window.load_text("current_score", rank_font, rank_font_size, current_score_text, {255, 255, 255, 255});
        auto texture = window.get_texture("current_score");
        texture->render(size.left() + 400, size.top() + size.height);
    }

    const std::string data::display_name = "Sonic Unleashed Ranks";
    const std::pair<int, int> data::display_dimensions = std::make_pair(1920, 180);
    const std::chrono::milliseconds data::render_sleep = 16ms;
    void data::draw_state(ox::sdl_instance& window, const data::static_calculations& state) {
        draw_time_bonus_factors(window, state.ranks);
    }
    void data::draw_data(ox::sdl_instance& window, const data::static_calculations& state,
                         const data::calculation_temp& calc) {
        auto& [level, ranks, result] = state;
        auto& [scores, score, high_mark, data] = calc;
        draw_score_progress_bar(window, scores, high_mark);
        draw_rank_markers_scores(window, state.ranks, score, high_mark);
        current_score(window, state, calc);
        draw_time_remaining(window, state, calc);
    }
    const std::array<std::string, 9> data::score_names{
            "Time",
            "Rings",
            "Enemy",
            "Speed",
            "",
            "",
            "Tricks",
            "Combo",
            "Crush",
    };
} // namespace unleashed
