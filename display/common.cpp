#include "common.hpp"
#include <ox/io.h>
#include <ranges>

const int rank_font_size = 25;
const std::filesystem::path rank_font{"/usr/share/fonts/truetype/ubuntu/Ubuntu-M.ttf"};

void load_rank_images(ox::sdl_instance& s) {
    static std::filesystem::path assets;
    if (assets.empty()) {
        assets.assign(ox::executable_folder() / ".." / "assets");
    }
    for (auto a : {"S", "A", "B", "C", "D", "E"}) {
        s.load_texture(std::format("{}{}", a, true), assets / std::format("{}_rank_{}.png", a, true));
        s.load_texture(std::format("{}{}", a, false), assets / std::format("{}_rank_{}.png", a, false));
    }
}


void load_rank_images_custom(ox::sdl_instance& s, std::ranges::range auto r) {
    static std::filesystem::path assets;
    if (assets.empty()) {
        assets.assign(ox::executable_folder() / ".." / "assets");
    }
    for (auto a : r) {
        s.load_texture(std::format("{}{}", a, true), assets / std::format("{}_rank_{}.png", a, true));
        s.load_texture(std::format("{}{}", a, false), assets / std::format("{}_rank_{}.png", a, false));
    }
}
