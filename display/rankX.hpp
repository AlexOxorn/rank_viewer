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
#include <ranges>
#include <span>
#include <ox/formatting.h>
#include <ox/terminal.h>
#include <fmt/core.h>
#include <fmt/color.h>
#include <ox/canvas.h>
#include "common.hpp"


struct dimensions {
    int height = rank_font_size;
    int start_x = 0;
    int start_y = 0;
    int y_buffer = 5;
    int x_buffer = 5;
    double scale = 0.75;
    std::optional<int> end_x{};
    std::optional<int> end_y{};

    [[nodiscard]] int top() const {
        return start_y + y_buffer;
    }

    [[nodiscard]] int left() const {
        return start_x + x_buffer;
    }
    [[nodiscard]] std::optional<int> right() const {
        return end_x.transform([this](int i) { return i - x_buffer; });
    }
    [[nodiscard]] std::optional<int> bottom() const {
        return end_y.transform([this](int i) { return i - y_buffer; });
    }
    [[nodiscard]] std::optional<int> width() const {
        return end_x.transform([this](int i) { return i - start_x - 2 * x_buffer; });
    }
    [[nodiscard]] std::optional<int> tall() const {
        return end_y.transform([this](int i) { return i - start_y - 2 * y_buffer; });
    }

    void clear_render (
        ox::sdl_instance& win
    ) const {
        win.reset_renderer_color();
        auto [screen_width, screen_height] = win.get_window_size();
        SDL_Rect screen_portion{start_x, start_y, screen_width, height + 2*y_buffer};
        SDL_RenderFillRect(win.screen_renderer(), &screen_portion);
    }
};

void draw_score_progress(
        ox::sdl_instance& win,
        std::span<const score_data> ranks,
        std::span<const score_data> scores,
        int min = -1,
        dimensions size = dimensions{}
);

int draw_score_progress_bar(
        ox::sdl_instance& win,
        std::span<const score_data> scores,
        int highmark,
        dimensions size = dimensions{},
        bool clear_render = true
);

template<std::regular_invocable<int, int> CompareFunc = std::greater_equal<int>>
void draw_rank_markers_scores(
    ox::sdl_instance& win,
    std::span<const score_data> ranks,
    int total_points,
    int highmark,
    dimensions size = dimensions{},
    CompareFunc comp = {}
);

void draw_score_text(
    ox::sdl_instance& win,
    std::span<const score_data> scores,
    dimensions size = dimensions{rank_font_size, 5, 10 + rank_font_size, 0}
);
void draw_score_text_horizontal(
    ox::sdl_instance& win,
    std::span<const score_data> scores,
    dimensions size = dimensions{rank_font_size, 5, 10 + rank_font_size, 0}
);

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

    int text_y = size.start_y + size.height + 5;
    for (auto& rank : ranks) {
        int rank_ticks = rank.seconds / divisor;
        win.set_renderer_color(time.seconds >= rank.seconds ? ox::named_colors::DarkRed :  ox::named_colors::DarkGreen);
        SDL_Rect rank_box{rank_ticks + size.start_x, size.start_y, 2, size.height};
        SDL_RenderFillRect(win.screen_renderer(), &rank_box);

        auto text = win.get_texture(rank.name + "_text");
        if (text) {
            text->render(size.start_x, text_y);
        }
        text_y += (size.height);
    }
}
