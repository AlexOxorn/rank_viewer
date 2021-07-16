#include <sa2/position_view.hpp>
#include <ox/common.h>
#include <chrono>
#include <thread>

namespace sa2 {
    using namespace std::literals::chrono_literals;
    struct state {
        int level;
    };
    constexpr auto stall_time = 100ms;

    void print_position(std::filesystem::path dir, int pid) {
        process game{pid};

        int current_level = -1;
        ox::file stage_file = nullptr;

        while(true) {
            std::cout << std::flush;
            std::this_thread::sleep_for(stall_time);
            int next_level = get_current_level(game);

            if(next_level != current_level) {
                if(stage_file) {
                    fmt::print("closing file\n");
                    stage_file = nullptr;
                }
                current_level = next_level;
                auto temp_index = stage_index.find(current_level);
                std::string file_name = std::to_string(current_level) + ".csv";
                std::filesystem::path outfile_path = dir / file_name;
                if (temp_index != stage_index.end()) {
                    fmt::print("opening file: {}\n", outfile_path.c_str());
                    stage_file = ox::file{
                        outfile_path.c_str(),
                        "w"
                    };
                }
            }

            if (!stage_file)
                continue;

            if (get_full_time(game).total_centiseconds() <= 0)
                continue;

            float_vector position = get_p1_possition_mirror(game);
            std::array<float, 3> position_array = ox::c_to_std_array(position.data);
            std::array<std::string, 3> string_positions;
            std::transform(
                position_array.begin(),
                position_array.end(),
                string_positions.begin(),
                [](float f) -> std::string {
                    return fmt::format("{:2f}", f);
                }
            );
            print_csv_file(stage_file, string_positions);
        }
    }
}
