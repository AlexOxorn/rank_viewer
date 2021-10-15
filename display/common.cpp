#include "common.hpp"

const int rank_font_size = 24;
const std::filesystem::path rank_font{"/usr/share/fonts/truetype/ubuntu/Ubuntu-M.ttf"};

void load_rank_images(ox::sdl_instance& s) {
    for (auto a : {"S", "A", "B", "C", "D", "E"}) {
        s.load_texture(fmt::format("{}{}", a, true), fmt::format("../assets/{}_rank_{}.png", a, true));
        s.load_texture(fmt::format("{}{}", a, false), fmt::format("../assets/{}_rank_{}.png", a, false));
    }
}
