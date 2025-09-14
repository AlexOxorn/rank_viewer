#pragma once

#include "common.hpp"
#include <stdio.h>
#include <ranges>
// #include <fmt/core.h>
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
    const auto l = std::format("{}\n", line);
    fwrite(l.c_str(), 1, l.size(), fp);
}
