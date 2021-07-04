#pragma once

#include <ox/types.h>
#include <ox/bytes.h>

namespace sa2 {
    struct min_second {
        u8 minutes;
        u8 seconds;

        int total_seconds() {
            return minutes * 60 + seconds;
        }
    };

    struct stage_score_rank {
        u16 level_id;
        u16 ranks[4];
    };

    struct stage_time_rank {
        u16 level_id;
        min_second ranks[4];
    };

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
}
