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
    for (auto score : scores) {
        int score_ticks = score.score / divisor;
        int draw_width = std::min(score_ticks, width - currentX);
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
}
