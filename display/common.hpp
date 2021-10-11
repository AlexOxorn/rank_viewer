#pragma once
#include <ox/types.h>
#include <ox/triple.h>
#include <ox/colors.h>
#include <ox/canvas.h>
#include <fmt/core.h>
#include <filesystem>

inline const std::filesystem::path rank_font{"/usr/share/fonts/truetype/ubuntu/Ubuntu-M.ttf"};
inline constexpr int rank_font_size = 24;

struct rank_data {
    int score;
    std::string name;

    bool operator<(const rank_data& other) {
        return score < other.score;
    }
};

struct time_rank_data {
    int seconds;
    std::string name;

    bool operator<(const time_rank_data& other) {
        return seconds < other.seconds;
    }
};

struct score_data {
    int score = 0;
    ox::color foreground = ox::named_colors::black;
    ox::color background = foreground;
    std::string name{};
};

struct time_data {
    int seconds = 0;
    ox::color foreground = ox::named_colors::black;
    ox::color background = foreground;
};



template <std::size_t N>
void load_requirement_text(ox::sdl_instance& win, std::array<rank_data, N>& s_ranks) {
    for (auto& rank : s_ranks) {
        win.load_text(fmt::format("{}_text", rank.name), rank_font, rank_font_size, fmt::format("{}: {}", rank.name, rank.score), {255, 255, 255, 255});
    }
}

template <std::size_t N>
void load_requirement_text(ox::sdl_instance& win, std::array<time_rank_data, N>& t_ranks) {
    for (auto& rank : t_ranks) {
        win.load_text(fmt::format("{}_text", rank.name), rank_font, rank_font_size, fmt::format("{}: {}m {}s", rank.name, rank.seconds / 60, rank.seconds % 60), {255, 255, 255, 255});
    }
}

using float_vector = ox::triple<float>;
using int_vector = ox::triple<i32>;
