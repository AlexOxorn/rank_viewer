#include <sonic_heroes/rank_view.hpp>
#include <dolphin_process.hpp>
#include <rank.hpp>
#include <rankX.hpp>
#include <ox/formatting.h>
#include <sonic_heroes/data_extractor.hpp>
#include <fmt/core.h>
#include <iostream>
#include <ox/canvas.h>

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
        using namespace std::chrono_literals;

        dolphin_process dolphin{pid};
        normal_stages prototype{};
        void* buffer = &prototype;
        std::array<rank_data, 4> s_ranks{};
        std::array<time_rank_data, 4> t_ranks{};
        state current{-1, -1, -1};
        int result = 0;

        SDL_Event e;
        ox::sdl_instance rank_display{"Sonic Hereos Ranks", true, {1920, 100}, {10, 10}};
        const std::chrono::milliseconds render_sleep = 16ms;
        bool quit = false;

        rank_display.load_text("Time Bonus", rank_font, rank_font_size, "Time Bonus");
        rank_display.load_text("Speed Score", rank_font, rank_font_size, "Speed Score");
        rank_display.load_text("Fly Score", rank_font, rank_font_size, "Fly Score");
        rank_display.load_text("Power Score", rank_font, rank_font_size, "Power Score");
        rank_display.load_text("Under 90s Bonus", rank_font, rank_font_size, "90s Bonus");

        while(!quit) {
            ox::sdl_check_error();
            auto now = std::chrono::steady_clock::now();
            auto end = now + render_sleep;
            while(SDL_PollEvent( &e )) {
                switch (e.type) {
                case SDL_QUIT:
                    quit = true;
                    continue;
                }
            }
            state next{get_current_stage(dolphin), get_current_team(dolphin), get_current_mission(dolphin)};
            rank_display.redraw();

            if(next != current) {
                current = next;
                result = get_ranks(dolphin, current.level, current.team, current.mission, buffer);
                if((result & TIMED_LEVEL) != 0) {
                    if((result & BOSS_LEVEL) != 0) {
                        t_ranks = interpret_time_rank_data(reinterpret_cast<boss_timed_stages *>(buffer), current.team);
                        load_requirement_text(rank_display, t_ranks);
                    } else if ((result & EXTRA_MISSION) != 0) {
                        t_ranks = interpret_time_rank_data(reinterpret_cast<extra_timed_stages *>(buffer), current.team);
                        load_requirement_text(rank_display, t_ranks);
                    }
                } else {
                    if((result & EXTRA_MISSION) != 0) {
                        s_ranks = interpret_score_rank_data(reinterpret_cast<extra_stages *>(buffer), current.team);
                        load_requirement_text(rank_display, s_ranks);
                    } else {
                        s_ranks = interpret_score_rank_data(reinterpret_cast<normal_stages *>(buffer), current.team);
                        load_requirement_text(rank_display, s_ranks);
                    }
                }
            }

            if (result == -1) {
                std::this_thread::sleep_until(end);
                continue;
            }

            if ((result & TIMED_LEVEL) != 0) {
                std::array<u8, 3> time = get_current_time(dolphin);
                draw_time_progress(rank_display, t_ranks, {time[0] * 60 + time[1], ox::named_colors::grey50});
            } else {
                draw_score_progress(rank_display, s_ranks, interpret_score(dolphin), 50000);
            }
            std::this_thread::sleep_until(end);
        }
    }
}
