#pragma once
#include <ox/types.h>
#include <ox/triple.h>
#include <ox/colors.h>
#include <filesystem>

inline const std::filesystem::path rank_font{"/usr/share/fonts/truetype/ubuntu/Ubuntu-M.ttf"};
inline constexpr int rank_font_size = 24;

struct rank_data {
    int score;
    std::string name;
};

struct time_rank_data {
    int seconds;
    std::string name;
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

using float_vector = ox::triple<float>;
using int_vector = ox::triple<i32>;
