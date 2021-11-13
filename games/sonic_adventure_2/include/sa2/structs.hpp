#pragma once

#include <ox/types.h>
#include <ox/bytes.h>
#include <common.hpp>
#include <ox/ptr.h>
#include <ox/triple.h>

using ox::ptr;

namespace sa2 {
    struct minute_second {
        u8 minutes;
        u8 seconds;

        [[nodiscard]] int total_seconds() const {
            return minutes * 60 + seconds;
        }
    };

    struct minute_second_centi {
        u8 minutes;
        u8 seconds;
        u8 centiseconds;

        [[nodiscard]] int total_seconds() const {
            return minutes * 60 + seconds;
        }

        int total_centiseconds() {
            return total_seconds() * 100 + centiseconds;
        }
    };

    struct entity_data {
        i8 action;
        i8 next_action;
        i8 field_2;
        i8 index;
        i16 status;
        i16 field_6;
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
        ptr<void> unknown_ptrA;
        ptr<void> object_data2;
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
        minute_second ranks[4];
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

    union stage_union {
        stage_time_rank timed;
        stage_score_rank scored;
    };
}
