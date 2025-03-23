#pragma once
#include "structs.hpp"
#include "variables.hpp"
#include <process.h>
#include <ox/formatting.h>
#include <rank.hpp>

namespace unleashed {
    struct interpret_ret {
        std::array<score_data, 9> scores;
        SScoreInfo data;
    };

    interpret_ret interpret_data(unleashed_process& process);
}
