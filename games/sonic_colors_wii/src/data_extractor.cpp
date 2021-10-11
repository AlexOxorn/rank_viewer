#include <sonic_colors/data_extractor.hpp>
#include <helpers.hpp>
#include <ox/formatting.h>
#include <string_view>


namespace gc::sonic_colors {
    constexpr int max_zone = 7;
    constexpr int max_act = 7;
    constexpr int max_no_of_deaths = 5;
    constexpr int per_ring_bonus = 1000;

    const std::array<std::string, 21> score_names {
        "Check Point",
        "Tricks",
        "_184",
        "Drifting",
        "Grinding",
        "Quick Step",
        "Rainbow Ring",
        "Diamonds",
        "Enemy",
        "Steel Box",
        "Rings",
        "_1A8",
        "Lost Rings",
        "Special",
        "_1B4",
        "Drill",
        "Laser",
        "Spike",
        "Rocket",
        "Frenzy",
        "_1CC",
    };

    int read_stage_data(dolphin_process& process, int zone, int act, stage_data& buffer) {
        if (zone >= max_zone || act >= max_act) {
            return -1;
        }

        int level = zone * max_act + act;
        process.read_memory(stage_data_address + sizeof(stage_data) * level, &buffer);
        return 0;
    }

    std::array<rank_data, 4> interpret_score_rank_data(stage_data& stage) {
        auto ranks = *reinterpret_cast<std::array<i32, 4> *>(&stage.rank_requirements);
        return std::array{
            rank_data{ranks[0], "S"},
            rank_data{ranks[1], "A"},
            rank_data{ranks[2], "B"},
            rank_data{ranks[3], "C"}
        };
    }

    time_bonus interpret_time_bonus(stage_data& stage) {
        return stage.time_bonus_data;
    }

    i32 interpret_death_bonus(stage_data& stage, int number_of_deaths) {
        if (number_of_deaths >= max_no_of_deaths) {
            return 0;
        }
        return stage.no_miss_bonus[number_of_deaths];
    }

    i32 interpret_ring_bonus(stage_data&, int rings) {
        return rings * per_ring_bonus;
    }

    std::array<score_data, 28> interpret_score(dolphin_process& process, stage_data& stage) {
        int state1 = get_state1(process);
        int state2 = get_state2(process);

        float seconds = get_current_time(process);
        int rings = get_previous_rings(process);
        time_bonus timebonus_data = interpret_time_bonus(stage);
        int deaths = get_death_count(process);

        int timebonus = std::max(timebonus_data.base - timebonus_data.penalty * static_cast<int>(seconds), 0);
        int deathbonus = timebonus == 0 ? 0 : interpret_death_bonus(stage, deaths);
        int ringbonus = timebonus == 0 ? 0 : interpret_ring_bonus(stage, rings);
        auto scores = get_scores(process);

        std::array<score_data, 28> to_return;

        int i = 0;
        for(auto c = ox::named_colors::dark_teal; i < 21; ++i, c.lighten(0.02)) {
            auto score_name = score_names[i];
            ox::color forground = score_name[0] == '_' ? ox::named_colors::DarkGreen : c;
            to_return.at(i) = {.score = scores[i], .foreground = forground, .name = score_name};
        }
        for (auto [j, partial, c] = std::tuple{max_no_of_deaths, 0, ox::named_colors::DarkRed}; j > 0; j--, c.lighten(0.1)) {
            int part = stage.no_miss_bonus[j - 1] - partial;
            partial += part;
            to_return.at(i++) = {
                .score = deaths < j ? part : 0,
                .foreground = c,
                .name = j == max_no_of_deaths ? "Death Bonus" : std::string{}
            };
        }

        to_return.at(i++) = {.score = timebonus, .foreground = ox::named_colors::MediumAquamarine, .name = "Time Bonus"};
        to_return.at(i++) = {.score = ringbonus, .foreground = ox::named_colors::gold, .name = "Ring Bonus"};
        return to_return;
    }
}
