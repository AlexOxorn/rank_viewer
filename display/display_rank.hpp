#pragma once

#include <rank.hpp>
#include <rankX.hpp>
#include <ox/formatting.h>
#include <fmt/core.h>
#include <ox/canvas.h>
#include <iostream>
#include <concepts>
#include <process.hpp>
#include <ranges>

template<typename game>
void display_ranksX(int pid) {
    using namespace std::chrono_literals;
    
    // define process
    typename game::process game_process{pid};
    // define state buffer
    typename game::static_calculations state{};
    // define result_flag
    unsigned general_purpose_results_flag;

    // define window
    ox::sdl_instance rank_display{game::display_name, true, game::display_dimensions};
    SDL_Event e;
    bool quit = false;

    // load score text_data
    // load rank images
    auto non_zero = std::ranges::views::filter(game::score_names, [](const std::string& s) -> bool {return !s.empty();});
    for (const std::string& s : non_zero) {
        rank_display.load_text(s, rank_font, rank_font_size, s);
    }
    load_rank_images(rank_display);
    // clear_render / choose background colour

    rank_display.clear_render();

    // Event Loop:
    while(!quit) {
        ox::sdl_check_error();
        auto now = std::chrono::steady_clock::now();
        auto end = now + game::render_sleep;
        while(SDL_PollEvent( &e )) {
            switch (e.type) {
            case SDL_QUIT:
                quit = true;
                continue;
            }
        }
        // redraw
        rank_display.redraw();

        // read current state
        typename game::level_state next = game::read_level_state(game_process);
        if(next != state.level) {
            // ** read stage and rank data into buffers
            state.level = next;
            game::read_stage_data(game_process, state);
            game::get_rank_data(state);

            // load requirements text
            game::load_rank_text(rank_display, state);
            // draw ranks
            game::draw_state(rank_display, state);
        }

        // if stage read failed: loop
        if (!state) {
            std::this_thread::sleep_until(end);
            continue;
        }

        // ** calculate scores
        auto calculations = game::calculate_data(game_process, state);
        // ** draw scores
        game::draw_data(rank_display, state, calculations);

        std::this_thread::sleep_until(end);
    }
}