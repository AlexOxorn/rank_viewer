#include <sonic_heroes/rank_view.hpp>
#include <dolphin_process.hpp>
#include <rank.hpp>
#include <rankX.hpp>
#include <ox/formatting.h>
#include <sonic_heroes/data_extractor.hpp>
#include <fmt/core.h>
#include <iostream>
#include <ox/X11Test.h>

namespace gc::sonic_heroes {
    [[noreturn]] void display_ranks(int pid) {
        dolphin_process dolphin{pid};
        normal_stages prototype{};
        void* buffer = &prototype;

        std::array<rank_data, 4> s_ranks{};
        std::array<time_rank_data, 4> t_ranks{};

        state current{-1, -1, -1};
        int result = 0;

        while(true) {
            usleep(stall_time_milli);
            state next{get_current_stage(dolphin), get_current_team(dolphin), get_current_mission(dolphin)};
            std::cout << std::flush;

            if(next != current) {
                fmt::print("{}{}", ox::format{ox::escape::reset}, ox::clear_screen{ox::escape::all});
                current = next;
                result = get_ranks(dolphin, current.level, current.team, current.mission, buffer);
                if((result & TIMED_LEVEL) != 0) {
                    if((result & BOSS_LEVEL) != 0) {
                        t_ranks = interpret_time_rank_data(reinterpret_cast<boss_timed_stages *>(buffer), current.team);
                    } else if ((result & EXTRA_MISSION) != 0) {
                        t_ranks = interpret_time_rank_data(reinterpret_cast<extra_timed_stages *>(buffer), current.team);
                    }
                } else {
                    if((result & EXTRA_MISSION) != 0) {
                        s_ranks = interpret_score_rank_data(reinterpret_cast<extra_stages *>(buffer), current.team);
                    } else {
                        s_ranks = interpret_score_rank_data(reinterpret_cast<normal_stages *>(buffer), current.team);
                    }
                }
            }

            if (result == -1)
                continue;

            if ((result & TIMED_LEVEL) != 0) {
                std::array<u8, 3> time = get_current_time(dolphin);
                print_current_progress(t_ranks, {time[0] * 60 + time[1], ox::named_colors::grey50});
            } else {
                interpret_score(dolphin);
                print_current_progress(s_ranks, interpret_score(dolphin), 50000);
            }
        }
    }

    void display_ranksX(int pid) {
        dolphin_process dolphin{pid};
        normal_stages prototype{};
        void* buffer = &prototype;

        std::array<rank_data, 4> s_ranks{};
        std::array<time_rank_data, 4> t_ranks{};

        state current{-1, -1, -1};
        ox::X11Window rank_display{{10, 10}, {2160, 100}};
        int result = 0;

        rank_display.register_event_callback(ConfigureNotify, [](ox::X11Window<>& win) {
            XGetWindowAttributes(win.display, win.window, &win.attr);
            return true;
        });

        rank_display.register_continuous_callback([&](ox::X11Window<>& win) {
            state next{get_current_stage(dolphin), get_current_team(dolphin), get_current_mission(dolphin)};
            XFlush(win.display);

            if(next != current) {
                current = next;
                result = get_ranks(dolphin, current.level, current.team, current.mission, buffer);
                if((result & TIMED_LEVEL) != 0) {
                    return false;
                    if((result & BOSS_LEVEL) != 0) {
                        t_ranks = interpret_time_rank_data(reinterpret_cast<boss_timed_stages *>(buffer), current.team);
                    } else if ((result & EXTRA_MISSION) != 0) {
                        t_ranks = interpret_time_rank_data(reinterpret_cast<extra_timed_stages *>(buffer), current.team);
                    }
                } else {
                    if((result & EXTRA_MISSION) != 0) {
                        s_ranks = interpret_score_rank_data(reinterpret_cast<extra_stages *>(buffer), current.team);
                    } else {
                        s_ranks = interpret_score_rank_data(reinterpret_cast<normal_stages *>(buffer), current.team);
                    }
                }
            }

            if (result == -1)
                return false;

            if ((result & TIMED_LEVEL) != 0) {
                return false;
                std::array<u8, 3> time = get_current_time(dolphin);
                print_current_progress(t_ranks, {time[0] * 60 + time[1], ox::named_colors::grey50});
            } else {
                draw_score_progress(win, s_ranks, interpret_score(dolphin), 50000);
            }
            return false;
        });

        std::thread renderer{std::move(rank_display)};
        renderer.join();
    }
}
