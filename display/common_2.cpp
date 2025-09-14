#include "common.hpp"
#include <ox/io.h>
#include <format>

const int rank_font_size = 25;
const std::filesystem::path rank_font{"/usr/share/fonts/truetype/ubuntu/Ubuntu-M.ttf"};


static unsigned char S_t[] = {
    #embed "../assets/S_rank_true.png"
};
static unsigned char S_f[] = {
    #embed "../assets/S_rank_false.png"
};
static unsigned char A_t[] = {
    #embed "../assets/A_rank_true.png"
};
static unsigned char A_f[] = {
    #embed "../assets/A_rank_false.png"
};
static unsigned char B_t[] = {
    #embed "../assets/B_rank_true.png"
};
static unsigned char B_f[] = {
    #embed "../assets/B_rank_false.png"
};
static unsigned char C_t[] = {
    #embed "../assets/C_rank_true.png"
};
static unsigned char C_f[] = {
    #embed "../assets/C_rank_false.png"
};
static unsigned char D_t[] = {
    #embed "../assets/D_rank_true.png"
};
static unsigned char D_f[] = {
    #embed "../assets/D_rank_false.png"
};
static unsigned char E_t[] = {
    #embed "../assets/E_rank_true.png"
};
static unsigned char E_f[] = {
    #embed "../assets/E_rank_false.png"
};

#define LOAD_IMAGE(X) \
    s.load_texture(#X "true", X##_t, sizeof(X##_t)); \
    s.load_texture(#X "false", X##_f, sizeof(X##_t));

void load_rank_images(ox::sdl_instance& s) {
    LOAD_IMAGE(S)
    LOAD_IMAGE(A)
    LOAD_IMAGE(B)
    LOAD_IMAGE(C)
    LOAD_IMAGE(D)
    LOAD_IMAGE(E)
}
