#pragma once

#include <exception>
#include <string>
#include <utility>
#include <array>
#include <concepts>
#include <numeric>
#include <iostream>
#include <ox/formating.h>
#include <ox/terminal.h>
#include <fmt/core.h>
#include <fmt/color.h>

struct rank_data {
    int score;
    std::string name;
};

struct time_rank_data {
    int seconds;
    std::string name;
};

struct score_data {
    int score;
    std::string color;
};

struct time_data {
    int seconds;
    std::string color;
};

template<std::size_t N, std::size_t M>
void print_current_progress(
    std::array<rank_data, N> ranks,
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
    int total_points = std::accumulate(scores.begin(), scores.end(), int{}, [](int sum, score_data n) -> int {return sum + n.score;});

    // std::cout << ox::move_cursor{0, 0} << ox::clear_line{ox::escape::all};
    fmt::print("{}{}", ox::move_cursor{0, 0}, ox::clear_line{ox::escape::all});

    for (auto score : scores) {
        int score_ticks = score.score / divisor;
        // std::cout << score.color;
        fmt::print("{}", score.color);
        for (int i = 0; i < score_ticks; i++) {
            // std::cout << '|';
            fmt::print("|");
        }
    }

    std::cout << ox::format{ox::escape::reset};
    // fmt::print(0, "");

    for (int i = 0; i < ranks.size(); i++ ) {
        auto rank = ranks[i];
        int rank_ticks = rank.score / divisor;
        const std::string& rank_name = rank.name;

        auto format = total_points >= rank.score ?
            fg(fmt::color::black) | bg(fmt::color::green) | fmt::emphasis::bold :
            fg(fmt::color::white) | bg(fmt::color::red) | fmt::emphasis::bold;

        // std::cout   << ox::move_cursor{0, rank_ticks}
        //             << (total_points >= rank.score ?
        //                 ox::format{ox::escape::reset, ox::escape::black, ox::escape::background_green, ox::escape::bold} :
        //                 ox::format{ox::escape::reset, ox::escape::white, ox::escape::background_red, ox::escape::bold})
        //             << rank.name
        //             << ox::move_cursor{i+2, 0}
        //             << ox::format{ox::escape::reset}
        //             << rank.name << ": "
        //             << rank.score
        //             << ox::clear_line{ox::escape::to_end};
        fmt::print(format, "{}{}", ox::move_cursor{0, rank_ticks}, rank.name);
        fmt::print("{}{}: {}{}", ox::move_cursor{i+2, 0}, rank.name, rank.score, ox::clear_line{ox::escape::to_end});
    }
    std::cout << ox::format{ox::escape::reset};
}

template<std::size_t N>
void print_current_progress(
    std::array<time_rank_data, N> ranks,
    time_data time,
    double scale = 0.75
) {
    ox::terminal_size size = ox::get_terminal_size();
    int divisor = ranks.front().seconds / (size.columns * scale) + 1;

    std::cout << ox::move_cursor{0, 0} << ox::clear_line{ox::escape::all};
    // fmt::print("{}{}", ox::move_cursor{0, 0}, ox::clear_line{ox::escape::all});

    int time_ticks = time.seconds / divisor;
    std::cout << time.color;
    // fmt::print("{}", time.color);
    for (int i = 0; i < time_ticks; i++) {
        std::cout << '|';
        // fmt::print("|");
    }

    std::cout << ox::format{ox::escape::reset};
    // fmt::print(fmt::text_style{}, "");

    for(int i = 0; i < ranks.size(); i++) {
        auto rank = ranks[i];
        int rank_ticks = rank.seconds / divisor;
        const std::string& rank_name = rank.name;

        // auto format = time.seconds < rank.seconds ?
        //   fg(fmt::color::black) | bg(fmt::color::green) | fmt::emphasis::bold :
        //   fg(fmt::color::white) | bg(fmt::color::red) | fmt::emphasis::bold;

      std::cout   << ox::move_cursor{0, rank_ticks}
                  << (time.seconds < rank.seconds ?
                      ox::format{ox::escape::reset, ox::escape::black, ox::escape::background_green, ox::escape::bold} :
                      ox::format{ox::escape::reset, ox::escape::white, ox::escape::background_red, ox::escape::bold})
                  << rank.name
                  << ox::move_cursor{i+2, 0}
                  << ox::format{ox::escape::reset}
                  << rank.name << ": "
                  << rank.seconds / 60 << "m "
                  << rank.seconds % 60 << "s"
                  << ox::clear_line{ox::escape::to_end};
        // fmt::print(format, "{}{}", ox::move_cursor{0, rank_ticks}, rank.name);
        // fmt::print(
        //     "{}{}: {}m {:02}s{}",
        //     ox::move_cursor{i+2, 0},
        //     rank.name,
        //     rank.seconds / 60,
        //     rank.seconds % 60,
        //     ox::clear_line{ox::escape::to_end}
        // );
    }
}
