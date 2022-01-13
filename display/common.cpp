#include "common.hpp"
#include <ox/io.h>

const int rank_font_size = 25;
const std::filesystem::path rank_font{"/usr/share/fonts/truetype/ubuntu/Ubuntu-M.ttf"};

void load_rank_images(ox::sdl_instance& s) {
    static std::filesystem::path assets;
    if (assets.empty()) {
        assets.assign(ox::executable_folder() / ".." / "assets");
    }
    for (auto a : {"S", "A", "B", "C", "D", "E"}) {
        s.load_texture(fmt::format("{}{}", a, true), assets / fmt::format("{}_rank_{}.png", a, true));
        s.load_texture(fmt::format("{}{}", a, false), assets / fmt::format("{}_rank_{}.png", a, false));
    }
}
