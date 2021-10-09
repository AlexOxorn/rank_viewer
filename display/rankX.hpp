#pragma once

#include <cmath>
#include <exception>
#include <string>
#include <utility>
#include <array>
#include <algorithm>
#include <concepts>
#include <numeric>
#include <iostream>
#include <ox/formatting.h>
#include <ox/terminal.h>
#include <fmt/core.h>
#include <fmt/color.h>
#include <ox/X11Test.h>
#include <ox/canvas.h>
#include "common.hpp"

struct dimensions {
    int height = 50;
    int start_x = 5;
    int start_y = 5;
    double scale = 0.75;
};

template<std::size_t N, std::size_t M>
void draw_score_progress(
        ox::sdl_instance& win,
        std::array<rank_data, N> ranks,
        std::array<score_data, M> scores,
        int min = -1,
        dimensions size = dimensions{}
) {
    win.set_renderer_color(ox::named_colors::black);
    win.clear_render();
    int fullwidth, fullheight;
    SDL_GetWindowSize(win.window(), &fullwidth, &fullheight);
    
    int width = fullwidth - 2 * size.start_x;
    if (width <= 0)
        return;

    int max_marker = ranks.back().score;
    if (min > 0) {
        max_marker = std::max(min, max_marker);
    }
    int divisor = static_cast<int>(max_marker / (width * size.scale)) + 1;
    int total_points = std::accumulate(scores.begin(), scores.end(), int{}, [](int sum, const score_data& n) -> int {return sum + n.score;});

    double currentX = size.start_x;

    for (score_data& score : scores) {
        if (score.score == 0) {
            continue;
        }
        double score_ticks = static_cast<double>(score.score) / divisor;
        double nextX = std::min(currentX + score_ticks, static_cast<double>(width));
        int currentI = static_cast<int>(lround(currentX));
        int nextI = static_cast<int>(lround(nextX));

        win.set_renderer_color(score.foreground);
        SDL_Rect r{currentI, size.start_y, nextI - currentI, size.height};
        SDL_RenderFillRect(win.screen_renderer(), &r);
        auto text = win.get_texture(score.name);
        if (text) {
            text->render(r.x, r.y);
        }
        currentX = nextX;
    }

    for (auto& rank : ranks) {
        int rank_ticks = rank.score / divisor;
        win.set_renderer_color(total_points < rank.score ? ox::named_colors::DarkRed :  ox::named_colors::DarkGreen);
        SDL_Rect r{rank_ticks + size.start_x, size.start_y, 2, size.height};
        SDL_RenderFillRect(win.screen_renderer(), &r);
    }
}

template<std::size_t N>
void draw_time_progress(
    ox::sdl_instance& win,
    std::array<time_rank_data, N> ranks,
    time_data time,
    dimensions size = dimensions{}
) {
    win.set_renderer_color(ox::named_colors::black);
    win.clear_render();
    int fullwidth, fullheight;
    SDL_GetWindowSize(win.window(), &fullwidth, &fullheight);

    int width = fullwidth - 2 * size.start_x;
    if (width <= 0)
        return;
    
    int max_marker = ranks.front().seconds;
    double divisor = (max_marker / (width * size.scale));

    int time_ticks = static_cast<int>(time.seconds / divisor);
    win.set_renderer_color(time.foreground);
    SDL_Rect r{size.start_x, size.start_y, time_ticks, size.height};
    SDL_RenderFillRect(win.screen_renderer(), &r);

    for (auto& rank : ranks) {
        int rank_ticks = rank.seconds / divisor;
        win.set_renderer_color(time.seconds >= rank.seconds ? ox::named_colors::DarkRed :  ox::named_colors::DarkGreen);
        SDL_Rect r{rank_ticks + size.start_x, size.start_y, 2, size.height};
        SDL_RenderFillRect(win.screen_renderer(), &r);
    }
}
