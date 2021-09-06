#pragma once

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
#include "common.hpp"

struct dimensions {
    int height = 50;
    int start_x = 5;
    int start_y = 5;
    double scale = 0.75;
};

template<std::size_t N, std::size_t M>
void draw_score_progress(
        const ox::X11Window<>& window,
        std::array<rank_data, N> ranks,
        std::array<score_data, M> scores,
        int min = -1,
        dimensions size = dimensions{}
) {
    XClearWindow(window.display, window.window);
    int width = window.attr.width - 2 * size.start_x;
    if (width <= 0)
        return;

    int max_marker = ranks.back().score;
    if (min > 0) {
        max_marker = std::max(min, max_marker);
    }
    int divisor = static_cast<int>(max_marker / (width * size.scale)) + 1;
    int total_points = std::accumulate(scores.begin(), scores.end(), int{}, [](int sum, const score_data& n) -> int {return sum + n.score;});

    int currentX = size.start_x;
    XSetForeground(window.display,window.gc,BlackPixel(window.display, window.screen));

    for (score_data& score : scores) {
        int score_ticks = score.score / divisor;
        int draw_width = std::min(score_ticks, width - currentX);
        XSetForeground(window.display, window.gc, score.foreground.rgb.rgb255());
        XDrawRectangle(
                window.display,
                window.window,
                window.gc,
                currentX,
                size.start_y,
                draw_width,
                size.height
                );
        currentX += draw_width;
    }

    for (auto& rank : ranks) {
        int rank_ticks = rank.score / divisor;
        XSetForeground(
                window.display,
                window.gc,
                total_points < rank.score ?
                    ox::rgb255({.rgb = {255, 0 , 0}}) :
                    ox::rgb255({.rgb = {0, 255 , 0}})
        );
        XDrawLine( window.display,
                   window.window,
                   window.gc,
                   rank_ticks + size.start_x,
                   size.start_y,
                   rank_ticks + size.start_x,
                   size.start_y + size.height
                   );
    }
}
