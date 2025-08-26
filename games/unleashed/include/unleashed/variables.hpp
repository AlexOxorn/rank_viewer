#pragma once

#include <ox/types.h>
#include "enum.hpp"
#include "structs.hpp"
#include <unordered_map>
#include <helpers.h>

namespace unleashed {
    constexpr long map_offset = 0x100000000;
    constexpr int score_struct_offset = 0x1d8;
    constexpr int speeds_offset = score_struct_offset+0x20;
    constexpr int checkpoint_count_offset = score_struct_offset+0x30;
    constexpr int enemy_offset = score_struct_offset+0x34;
    constexpr int trick_offset = score_struct_offset+0x38;
    constexpr int ranks_offset = score_struct_offset+offsetof(SScoreInfo, SRank);
    constexpr int game_mode_offset = score_struct_offset+ offsetof(SScoreInfo, Mode);

    GAME_VARIABLE(bool, is_loading, 0x183367A4C)

    GAME_VARIABLE(u32, CApplicationDocument_ptr, 0x1833678A0)
    GAME_INDIRECT_VARIABLE(u32, m_Field74_ptr, CApplicationDocument_ptr, 0x74);
    GAME_INDIRECT_VARIABLE(u32, m_Field10C_ptr, CApplicationDocument_ptr, 0x10C);
    GAME_INDIRECT_VARIABLE(char_array, m_Field74, m_Field74_ptr, 0)
    GAME_INDIRECT_VARIABLE(char_array, m_Field10C, m_Field10C_ptr, 0)


    GAME_VARIABLE(u32, base_pointer, 0x183362f98)
    GAME_INDIRECT_VARIABLE(u32, base_obj, base_pointer, 0)
    GAME_INDIRECT_VARIABLE(u32, rings, base_pointer, 0x538)
    GAME_ARRAY_VARIABLE(float, position_mirror, 0x1A0000CE0, 3);

    GAME_VARIABLE(u32, score_base_base, 0x183367900);
    GAME_INDIRECT_VARIABLE(u32, score_base, score_base_base, 0x8);
    GAME_INDIRECT_VARIABLE(SScoreInfo, score_data, score_base, score_struct_offset)
    GAME_INDIRECT_VARIABLE(u32, stage_name_ptr, score_base, 0xAC);
    GAME_VARIABLE(u32, stage_id, 0x109216e48);
    GAME_INDIRECT_VARIABLE(GameMode, game_mode, score_base, game_mode_offset);
    GAME_INDIRECT_VARIABLE(char_array, stage_name, stage_name_ptr, 0)

    GAME_INDIRECT_VARIABLE(u32, enemy_score, score_base, enemy_offset)
    GAME_INDIRECT_VARIABLE(u32, trick_score, score_base, trick_offset)
    GAME_INDIRECT_VARIABLE(u32, top_speed_count, score_base, checkpoint_count_offset)
    GAME_INDIRECT_ARRAY(float, speeds, score_base, speeds_offset, 4)
    GAME_INDIRECT_ARRAY(i32, rank_values, score_base, ranks_offset, 5)

    GAME_INDIRECT_VARIABLE(float, current_time, score_base, 0x5C)

    inline u32 get_werehog_base(process & p) {
        auto& pp = dynamic_cast<unleashed_process&>(p);
        return get_address<u32>(p, pp.werehog_address());
    }

    GAME_INDIRECT_VARIABLE(u32, night_rings, werehog_base, offsetof(night_context, Rings))
    GAME_INDIRECT_VARIABLE(night_context, night_date, werehog_base, 0)
}
