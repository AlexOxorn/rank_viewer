#pragma once

#include <ox/types.h>

namespace gc::sonic_heroes {
    enum GameStates {
        StateMenu = 1,

        StatePlaying = 5,
        StatePaused = 6,
        StateVictory = 12,
        StateSaving = 14,
    };
}
