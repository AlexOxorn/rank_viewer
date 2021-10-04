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

    double currentX = size.start_x;
    XSetForeground(window.display, window.gc, BlackPixel(window.display, window.screen));

    for (score_data& score : scores) {
        if (score.score == 0) {
            continue;
        }
        double score_ticks = static_cast<double>(score.score) / divisor;
        double nextX = std::min(currentX + score_ticks, static_cast<double>(width));
        int currentI = static_cast<int>(lround(currentX));
        int nextI = static_cast<int>(lround(nextX));

        XSetForeground(window.display, window.gc, score.foreground.rgb.rgb255());
        XFillRectangle(
                window.display, window.window, window.gc,
                currentI, size.start_y, nextI - currentI, size.height
                );
        XSetForeground(window.display, window.gc, BlackPixel(window.display, window.screen));
        XDrawString(
                window.display, window.window, window.gc,
                currentI, size.start_y + size.height,
                score.name.c_str(), static_cast<int>(score.name.length())
                );
        currentX = nextX;
    }

    for (auto& rank : ranks) {
        int rank_ticks = rank.score / divisor;
        XSetForeground(
                window.display,
                window.gc,
                total_points < rank.score ?
                    ox::named_colors::DarkRed.rgb.rgb255() :
                    ox::named_colors::DarkGreen.rgb.rgb255()
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
