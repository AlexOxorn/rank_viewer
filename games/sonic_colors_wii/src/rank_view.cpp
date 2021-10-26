#include <sonic_colors/rank_view.hpp>
#include <dolphin_process.hpp>
#include <rank.hpp>
#include <rankX.hpp>
#include <ox/formatting.h>
#include <sonic_colors/data_extractor.hpp>
#include <display_rank.hpp>
#include <fmt/core.h>
#include <ox/canvas.h>
#include <iostream>
#include <ranges>
#include <span>

namespace gc::sonic_colors {
    void display_ranks(int pid) {}
    using namespace std::chrono_literals;
    using data = sonic_colors_data;
    const std::string data::display_name = "Sonic Colors Ranks";
    const std::pair<int, int> data::display_dimensions = std::make_pair(1920, 160);
    const std::chrono::milliseconds data::render_sleep = 16ms;
    const std::array<std::string, 28> data::score_names{
        "Check Point",
        "Tricks",
        "_184",
        "Drifting",
        "Grinding",
        "Quick Step",
        "Rainbow Ring",
        "Diamonds",
        "Enemy",
        "Steel Box",
        "Rings",
        "Blue Rings",
        "Lost Rings",
        "Special",
        "_1B4",
        "Drill",
        "Laser",
        "Spike",
        "Rocket",
        "Frenzy",
        "Hover",
        "Death Bonus",
        "",
        "",
        "",
        "",
        "Time Bonus",
        "Ring Bonus"
    };

    data::level_state data::read_level_state(data::process_type& game) {
        return {get_current_zone(game), get_current_act(game)};
    }

    void data::read_stage_data(data::process_type& game, data::static_calculations& state) {
        gc::sonic_colors::read_stage_data(game, state.level.zone, state.level.act, state.stage);
    }

    void data::get_rank_data(data::process_type&, data::static_calculations& state) {
        state.ranks = interpret_score_rank_data(state.stage);
    }

    void data::load_rank_text(ox::sdl_instance& window, const data::static_calculations& state) {
        load_requirement_text(window, state.ranks);
    }

    void data::draw_state(ox::sdl_instance& window, const data::static_calculations& state) {
        draw_score_text(window, state.ranks);
    }

    data::calculation_temp data::calculate_data(data::process_type& game, const data::static_calculations& state) {
        auto scores = interpret_score(game, state.stage);
        auto score_values = std::ranges::views::transform(scores, &score_data::score);
        int total_score = std::accumulate(score_values.begin(), score_values.end(), 0);
        return {scores, total_score};
    }

    void data::draw_data(ox::sdl_instance& window, const data::static_calculations& state, const data::calculation_temp& calulcations) {
        draw_score_progress_bar(window, std::span(calulcations.scores), state.ranks.front().score);
        draw_rank_markers_scores(window, state.ranks, calulcations.total_score, state.ranks.front().score);
    }

    void display_ranksX(int pid) {
        ::display_ranksX<data>(pid);
    }
}
