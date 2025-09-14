#include <chrono>
#include <thread>
#include <iostream>

#include <ox/array.h>
// #include <fmt/core.h>
#include <sonic_heroes/variables.hpp>
#include <sonic_heroes/rank_view.hpp>
#include <sonic_heroes/position_view.hpp>

#include <position_dump.hpp>

namespace gc::sonic_heroes {
    using namespace std::literals::chrono_literals;
    constexpr auto stall_time = 100ms;

    [[noreturn]] void print_position(const std::filesystem::path& dir, int pid) {
        dolphin_process game{pid};

        state current{-1, -1, -1};
        ox::file stage_file = nullptr;

        while(true) {
            std::cout << std::flush;
            std::this_thread::sleep_for(stall_time);
            state next{get_current_stage(game), get_current_team(game), get_current_mission(game)};

            if(next != current) {
                current = next;
                stage_file = nullptr;
            }

            i32 game_state = get_current_game_state(game);

            if (!stage_file) {
                if (game_state == 4 || game_state == 5 || game_state == 12 || game_state == 6) {
                    std::string file_name = std::format("{}-{}.csv", current.level, current.team);
                    std::filesystem::path outfile_path = dir / file_name;
                    std::cout << std::format("opening file: {}\n", outfile_path.c_str());
                    stage_file = ox::file{
                        outfile_path.c_str(),
                        "w"
                    };
                } else {
                    continue;
                }
            }

            if (!(game_state == 4 || game_state == 5 || game_state == 12)) {
                if(game_state != 6)
                    stage_file = nullptr;
                continue;
            }

            float_vector spd_position = get_spd_position(game);
            float_vector fly_position = get_fly_position(game);
            float_vector pow_position = get_pow_position(game);
            std::array<std::array<float, 3>, 3> position_array{
                ox::c_to_std_array(spd_position.data),
                ox::c_to_std_array(fly_position.data),
                ox::c_to_std_array(pow_position.data),
            };
            std::array<float, 9> full_position_array = ox::flatten(position_array);
            std::array<std::string, 11> string_positions;
            std::transform(
                full_position_array.begin(),
                full_position_array.end(),
                string_positions.begin(),
                [](float f) -> std::string {
                    return std::format("{:2f}", f);
                }
            );
            string_positions[9] = std::to_string(get_current_leader(game));
            string_positions[9] = std::to_string(game_state);
            print_csv_file(stage_file, string_positions);
        }
    }
}
