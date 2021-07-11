#pragma once

#include <ox/types.h>
#include <ox/bytes.h>
#include <common.hpp>

using ox::ptr;

namespace sa2 {
    struct min_second {
        u8 minutes;
        u8 seconds;

        int total_seconds() {
            return minutes * 60 + seconds;
        }
    };

    struct entity_data {
        s8 action;
        s8 next_action;
        s8 field_2;
        s8 index;
        s16 status;
        s16 field_6;
        int_vector rotation;
        float_vector position;
        float_vector scale;
        ptr<void> collision;
    };

    struct object {
        ptr<object> prev_addr;
        ptr<object> next_addr;
        ptr<object> parent_addr;
        ptr<object> child_addr;
        ptr<void> main_routine_addr;
        ptr<void> display_routine_addr;
        ptr<void> delete_routine_addr;
        ptr<void> display_routine_delay1_addr;
        ptr<void> display_routine_delay2_addr;
        ptr<void> display_routine_delay3_addr;
        ptr<void> display_routine_delay4_addr;
        ptr<void> field_2C;
        ptr<void> set_data;
        ptr<entity_data> object_data1;
        ptr<void> entity_data2;
        ptr<void> unknow_ptrA;
        ptr<char> name;
        ptr<char> name_again;
        ptr<void> field_4C;
    };

    struct stage_score_rank {
        u16 level_id;
        u16 ranks[4];
    };

    struct stage_time_rank {
        u8 level_id;
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
