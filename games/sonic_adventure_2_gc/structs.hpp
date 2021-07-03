#pragma once

#include <ox/types.h>
#include <ox/bytes.h>

struct stage_score {
    u16 rings;
    u16 _buffer1;
    u32 score;
    u8 time[3];
    u8 _buffer2;
};

struct stage_data {
    u8 ranks[6];
    u16 play_counts[5];
    stage_score scores[5][3];
};
