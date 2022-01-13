#pragma once
#include <ox/types.h>
#include <ox/utils.h>
#include <ox/colors.h>
#include <ox/canvas.h>
#include <fmt/core.h>
#include <fmt/format.h>
#include <filesystem>
#include <ox/canvas.h>
#include <concepts>

extern const std::filesystem::path rank_font;
extern const int rank_font_size;
using namespace ox::int_alias;

void load_rank_images(ox::sdl_instance& s);

struct score_data {
    int score = 0;
    std::string name{};
    ox::color foreground = ox::named_colors::black;
    ox::color background = foreground;

    std::strong_ordering operator<=>(const score_data& other) const {
        return score <=> other.score;
    }

    friend int operator+(int l, const score_data& r) {
        return l + r.score;
    }
};


struct time_rank_data {
    int seconds;
    std::string name;

    bool operator<(const time_rank_data& other) const {
        return seconds < other.seconds;
    }

    operator score_data() const {
        return score_data{seconds, name};
    }
};

struct rank_data {
    int score;
    std::string name;

    std::strong_ordering operator<=>(const rank_data& other) const {
        return score <=> other.score;
    }

    operator score_data() const {
        return score_data{score, name};
    }
};

struct time_data {
    int seconds = 0;
    ox::color foreground = ox::named_colors::black;
    ox::color background = foreground;
};



struct score_formatter {
    std::string operator ()(const std::string& name, int score) {
        return fmt::format("{}: {}", name, score);
    }
    std::string operator ()(int score) {
        return fmt::to_string(score);
    }
};

struct min_second_formatter {
    std::string operator ()(const std::string& name, int total_second) {
        auto [minutes, seconds] = std::make_pair(total_second / 60, total_second % 60);
        return fmt::format("{}: {}:{:2d}", name, minutes, seconds);
    }
    std::string operator ()(int total_second) {
        auto [minutes, seconds] = std::make_pair(total_second / 60, total_second % 60);
        return fmt::format("{}:{:02d}", minutes, seconds);
    }
};

template <std::size_t N, std::invocable<std::string, int> Formatter = score_formatter>
void load_requirement_text(ox::sdl_instance& win, const std::array<score_data, N>& s_ranks, Formatter f = Formatter{}) {
    for (auto& rank : s_ranks) {
        win.load_text(fmt::format("{}_text_with_name", rank.name), rank_font, rank_font_size, f(rank.name, rank.score), {255, 255, 255, 255});
        win.load_text(fmt::format("{}_text", rank.name), rank_font, rank_font_size, f(rank.score), {255, 255, 255, 255});
    }
}

template <std::size_t N>
void load_requirement_text(ox::sdl_instance& win, const std::array<time_rank_data, N>& t_ranks) {
    for (auto& rank : t_ranks) {
        win.load_text(fmt::format("{}_text", rank.name), rank_font, rank_font_size, fmt::format("{}: {}m {}s", rank.name, rank.seconds / 60, rank.seconds % 60), {255, 255, 255, 255});
    }
}

using float_vector = ox::triple<float>;
using int_vector = ox::triple<i32>;
