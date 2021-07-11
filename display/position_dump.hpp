#pragma once

#include "common.hpp"
#include <stdio.h>
#include <ranges>
#include <ox/algorithms.h>

template <std::ranges::range T>
void print_csv_file(FILE *fp, T data) {
    std::string line{};
    ox::join(
        data.begin(),
        data.end(),
        ",",
        line
    );
    fmt::print(fp, "{}\n", line);
}
