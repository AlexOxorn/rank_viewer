#include <unleashed/data_extractor.hpp>
#include <helpers.h>

namespace unleashed {
    static_assert(LAST == 10);

    interpret_ret interpret_data(unleashed_process& process) {
        std::string name = get_stage_name(process).data();
        SScoreInfo level_data = get_score_data(process);
        i32 rings = 0;
        std::optional<night_context> night;

        if (level_data.MaxSpeedCount > 3)
            return {};

        if (unleashed::get_base_pointer(process) != 0) {
            rings = unleashed::get_rings(process);
        } else if (unleashed::get_werehog_base(process) != 0) {
            night = unleashed::get_night_date(process);
            rings = night->Rings;
        }

        std::array<score_data, int(LAST)> scores{};
        i32 timebonus = std::max(0,
                                 i32(-level_data.TimeBonusScale * std::max(0.0f, unleashed::get_current_time(process))
                                     + level_data.TimeBonusStart * level_data.TimeBonusScale));
        i32 ringbonus = 100 * rings;

        bool is_night = unleashed::get_werehog_base(process) != 0;

        scores[TimeBonus] = {.score = timebonus, .name = "Time", .foreground = ox::named_colors::MediumAquamarine};
        if (is_night) {
            scores[RingBonus] = {.score = ringbonus, .name = "Rings", .foreground = ox::named_colors::gold};
        } else {
            int loseable_rings = std::min(std::max(rings / 2 + 1, 20), rings);
            auto c = ox::named_colors::gold;
            scores[RingBonus] = {.score = std::max(0, rings - loseable_rings) * 100, .name = "Rings", .foreground = c};
            c.darken(0.2);
            scores[RingBonus2] = {
                    .score = loseable_rings * 100, .name = rings - loseable_rings ? "" : "Rings", .foreground = c};
        }

        if (name.contains("Boss")) {
            return {scores, level_data};
        }

        scores[EnemyBonus] = {
                .score = (i32) level_data.EnemyScore, .name = "Enemy", .foreground = ox::named_colors::maroon};

        if (is_night or name.contains("Eggman")) {
            scores[ComboBonus] = {.score = (i32) (night ? night->ComboScore : 0),
                                  .name = "Combo",
                                  .foreground = ox::named_colors::dark_teal};
            scores[CrushBonus] = {.score = (i32) (night ? night->ComboScore : 0),
                                  .name = "Crush",
                                  .foreground = ox::named_colors::DarkViolet};
        }
        else {
            scores[TrickBonus] = {.score = (i32) level_data.TrickScore,
                                  .name = "Tricks",
                                  .foreground = ox::named_colors::DarkViolet};

            if (level_data.MaxSpeedCount == 0) {
                scores[SpeedBonus1] = {.score = i32(std::max(level_data.GoalSpeed - 20.0, 0.0)) * 220,
                                       .name = "Speed",
                                       .foreground = ox::named_colors::dark_teal};
            }
            else {
                std::array<float, 3> partials;
                std::array<float, 3> contributions{};
                std::partial_sum(level_data.Speeds, level_data.Speeds + 3, partials.begin());
                auto sum = std::ranges::fold_left(level_data.Speeds, 0.f, std::plus<>());
                auto average = sum / level_data.MaxSpeedCount;
                auto speed_score = i32(std::max(average - 20.0, 0.0)) * 220;

                if (sum > 0)
                    std::ranges::transform(level_data.Speeds, contributions.begin(), [=](float s) { return s / sum; });

                auto c = ox::named_colors::dark_teal;

                int partial_score = 0;
                for (int j = level_data.MaxSpeedCount - 1; j > 0; --j) {
                    int score_part = speed_score * contributions[j];
                    partial_score += score_part;
                    scores[SpeedBonus1 + j] = {.score = score_part, .name = "", .foreground = c};
                    c.lighten(0.1);
                }
                scores[SpeedBonus1] = {
                        .score = speed_score - partial_score, .name = "Speed", .foreground = c};
            }
        };

        return {scores, level_data};
    }
} // namespace unleashed
