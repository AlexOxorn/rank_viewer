#pragma once
#include <ox/types.h>
#include <ox/triple.h>

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

using float_vector = ox::triple<float>;
using int_vector = ox::triple<i32>;
