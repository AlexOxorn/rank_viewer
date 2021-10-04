#include <sa2/rank_view.hpp>
#include <dolphin_process.hpp>
#include <rank.hpp>
#include <rankX.hpp>
#include <ox/formatting.h>
#include <ox/X11Test.h>
#include <sa2/data_extractor.hpp>
#include <fmt/core.h>

namespace sa2 {
    struct state {
        int level;
        int mission;
        int character;

        auto operator<=>(const state& other) const = default;
    };
    constexpr int stall_time_milli = 2500;

    [[noreturn]] void display_ranks(int pid) {
        process game{pid};
        stage_score_rank prototype{};
        void* buffer = &prototype;

        std::array<rank_data, 4> s_ranks{};
        std::array<time_rank_data, 4> t_ranks{};

        state current{-1, -1, -1};
        int result = 0;

        while(true) {
            usleep(stall_time_milli);
            state next{get_current_level(game), get_current_mission(game), get_current_character(game)};
            std::cout << std::flush;

            if(next != current) {
                fmt::print("{}{}", ox::format{ox::escape::reset}, ox::clear_screen{ox::escape::all});
                current = next;
                result = get_ranks(game, current.level, current.mission, current.character, buffer);
                if((result & TIMED_LEVEL) != 0) {
                    t_ranks = interpret_time_rank_data(reinterpret_cast<stage_time_rank *>(buffer));
                } else {
                    s_ranks = interpret_score_rank_data(reinterpret_cast<stage_score_rank *>(buffer));
                }
            }

            if (result == -1)
                continue;

            if ((result & TIMED_LEVEL) != 0) {
                minute_second time = get_time(game);
                print_current_progress(t_ranks, {time.total_seconds(), {{0xFF, 0xFF, 0xFF}}, {{0xFF, 0xFF, 0xFF}}});
            } else {
                interpret_score(game);
                print_current_progress(s_ranks, interpret_score(game), 10000);
            }
        }
    }

//    void display_ranksX(int pid) {
//        process game{pid};
//        stage_score_rank prototype{};
//        void* buffer = &prototype;
//
//        std::array<rank_data, 4> s_ranks{};
//        std::array<time_rank_data, 4> t_ranks{};
//
//        state current{-1, -1, -1};
//        ox::X11Window rank_display{{10, 10}, {1080, 100}};
//        int result = 0;
//
//        rank_display.register_event_callback(ConfigureNotify, [](ox::X11Window<>& win) {
//            XGetWindowAttributes(win.display, win.window, &win.attr);
//            return true;
//        });
//
//        rank_display.register_continuous_callback([&](ox::X11Window<>& win) {
//            state next{get_current_level(game), get_current_mission(game), get_current_character(game)};
//            XFlush(win.display);
//
//            if(next != current) {
//                current = next;
//                result = get_ranks(game, current.level, current.mission, current.character, buffer);
//                if((result & TIMED_LEVEL) != 0) {
//                    fmt::print("Timed continue\n");
//                    return false;
////                    t_ranks = interpret_time_rank_data(reinterpret_cast<stage_time_rank *>(buffer));
//                } else {
//                    s_ranks = interpret_score_rank_data(reinterpret_cast<stage_score_rank *>(buffer));
//                }
//            }
//
//            if (result == -1)
//                return false;
//
//            if ((result & TIMED_LEVEL) != 0) {
//                return false;
//                minute_second time = get_time(game);
//                print_current_progress(t_ranks, {time.total_seconds(), ox::named_colors::grey50});
//            } else {
//                draw_score_progress(win, s_ranks, interpret_score(game), 10000);
//            }
//            return false;
//        });
//
//        rank_display();
//    }
}
