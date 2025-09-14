#pragma once

#include <exception>
#include <string>
#include <utility>
#include <array>
#include <concepts>
#include <numeric>
#include <iostream>
#include <ox/formatting.h>
#include <ox/terminal.h>
// #include <fmt/core.h>
// #include <fmt/color.h>
#include "common.hpp"

template<std::size_t N, std::size_t M>
void print_current_progress(
    std::array<score_data, N> ranks,
    std::array<score_data, M> scores,
    int min = -1,
    double scale = 0.75
) {
    ox::terminal_size size = ox::get_terminal_size();
    int max_marker = ranks.back().score;
    if (min > 0) {
        max_marker = max_marker < min ? min : max_marker;
    }
    int divisor = max_marker / (size.columns * scale) + 1;
    int total_points = std::accumulate(scores.begin(), scores.end(), int{}, [](int sum, const score_data& n) -> int {return sum + n.score;});

    std::cout << std::format("{}{}", ox::move_cursor{0, 0}, ox::clear_line{ox::escape::all});

    for (auto score : scores) {
        int score_ticks = score.score / divisor;
        std::cout << std::format("{}{}",
                   ox::format{ox::escape::direct_color, 2, score.foreground.r, score.foreground.g, score.foreground.b},
                   ox::format{ox::escape::background_direct, 2, score.background.r, score.background.g, score.background.b});
        for (int i = 0; i < score_ticks; i++) {
            std::cout << std::format("|");
        }
    }

    std::cout << std::format("{}", ox::format{ox::escape::reset});

    for (int i = 0; i < static_cast<int>(ranks.size()); i++ ) {
        auto rank = ranks[i];
        int rank_ticks = rank.score / divisor;

        // auto format = total_points >= rank.score ?
        //     fg(fmt::color::black) | bg(fmt::color::green) | fmt::emphasis::bold :
        //     fg(fmt::color::white) | bg(fmt::color::red) | fmt::emphasis::bold;

        std::cout << std::format("{}{}", ox::move_cursor{0, rank_ticks}, rank.name);
        std::cout << std::format("{}{}: {}{}", ox::move_cursor{i+2, 0}, rank.name, rank.score, ox::clear_line{ox::escape::to_end});
    }
    std::cout << std::format("{}", ox::format{ox::escape::reset});
}

template<std::size_t N>
void print_current_progress(
    std::array<time_rank_data, N> ranks,
    time_data time,
    double scale = 0.75
) {
    ox::terminal_size size = ox::get_terminal_size();
    int divisor = ranks.front().seconds / (size.columns * scale) + 1;

    std::cout << std::format("{}{}", ox::move_cursor{0, 0}, ox::clear_line{ox::escape::all});

    int time_ticks = time.seconds / divisor;
    std::cout << std::format(
            "{}{}",
            ox::format{ox::escape::direct_color, 2, time.foreground.r, time.foreground.r, time.foreground.r},
            ox::format{ox::escape::background_direct, 2, time.background.r, time.background.r, time.background.r}
            );
    for (int i = 0; i < time_ticks; i++) {
        std::cout << std::format("|");
    }

    std::cout << std::format("{}", ox::format{ox::escape::reset});

    for(int i = 0; i < static_cast<int>(ranks.size()); i++) {
        auto rank = ranks[i];
        int rank_ticks = rank.seconds / divisor;

        // auto format = time.seconds < rank.seconds ?
        //   fg(fmt::color::black) | bg(fmt::color::green) | fmt::emphasis::bold :
        //   fg(fmt::color::white) | bg(fmt::color::red) | fmt::emphasis::bold;

        std::cout << std::format("{}{}", ox::move_cursor{0, rank_ticks}, rank.name);
        std::cout << std::format(
            "{}{}: {}m {:02}s{}",
            ox::move_cursor{i+2, 0},
            rank.name,
            rank.seconds / 60,
            rank.seconds % 60,
            ox::clear_line{ox::escape::to_end}
        );
    }
}
