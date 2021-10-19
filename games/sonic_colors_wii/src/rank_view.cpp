#include <sonic_colors/rank_view.hpp>
#include <dolphin_process.hpp>
#include <rank.hpp>
#include <rankX.hpp>
#include <ox/formatting.h>
#include <sonic_colors/data_extractor.hpp>
#include <fmt/core.h>
#include <ox/canvas.h>
#include <iostream>
#include <ranges>

namespace gc::sonic_colors {
    void display_ranks(int pid) {}

    void display_ranksX(int pid) {
        using namespace std::chrono_literals;

        dolphin_process game{pid};
        stage_data stage{};

        std::array<score_data, 4> ranks{};

        state current{-1, -1};
        int result = 0;

        ox::sdl_instance rank_display{"Sonic Colors Ranks", true, {1920, 160}};
        const std::chrono::milliseconds render_sleep = 16ms;
        SDL_Event e;
        bool quit = false;

        for (auto s : score_names) {
            rank_display.load_text(s, rank_font, rank_font_size, s);
        }
        rank_display.load_text("Death Bonus", rank_font, rank_font_size, "Death Bonus");
        rank_display.load_text("Time Bonus", rank_font, rank_font_size, "Time Bonus");
        rank_display.load_text("Ring Bonus", rank_font, rank_font_size, "Ring Bonus");
        load_rank_images(rank_display);

        rank_display.clear_render();

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

            state next{get_current_zone(game), get_current_act(game)};
            rank_display.redraw();

            if(next != current) {
                current = next;
                result = read_stage_data(game, current.zone, current.act, stage);
                if(result == -1) {
                    continue;
                }
                ranks = interpret_score_rank_data(stage);                
                load_requirement_text(rank_display, ranks);
                draw_score_text(rank_display, ranks);
            }

            if (result == -1) {
                std::this_thread::sleep_until(end);
                continue;
            }

            auto scores = interpret_score(game, stage);
            auto score_values = std::ranges::views::transform(scores, &score_data::score);
            int total_score = std::accumulate(score_values.begin(), score_values.end(), 0);
            draw_score_progress_bar(rank_display, scores, ranks.front().score);
            draw_rank_markers_scores(rank_display, ranks, total_score, ranks.front().score);
            std::this_thread::sleep_until(end);
        }
    }
}
