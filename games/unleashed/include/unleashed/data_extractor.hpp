#pragma once
#include "structs.hpp"
#include "variables.hpp"
#include <process.h>
#include <ox/formatting.h>
#include <rank.hpp>

namespace unleashed {
    enum ScoreType {
        TimeBonus,
        EnemyBonus,
        TrickBonus,
        SpeedBonus1,
        SpeedBonus2,
        SpeedBonus3,
        ComboBonus,
        CrushBonus,
        RingBonus,
        RingBonus2,
        LAST
    };


    struct interpret_ret {
        std::array<score_data, LAST> scores;
        SScoreInfo data;
    };

    interpret_ret interpret_data(unleashed_process& process);
}
