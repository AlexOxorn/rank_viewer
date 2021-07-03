#include <sonic_heroes/rank_view.hpp>

namespace gc::sonic_heroes {
    void display_ranks(int pid) {
        dolphin_process dolphin{pid};
    	normal_stages prototype{};
    	void* buffer = &prototype;

    	std::array<rank_data, 4> s_ranks{};
    	std::array<time_rank_data, 4> t_ranks{};


    	state current{-1, -1, -1};
    	int result = 0;

    	while(true) {
    		usleep(stall_time_milli);
    		state next{get_level(dolphin), get_team(dolphin), get_mission(dolphin)};
            std::cout << std::flush;

    		if(next != current) {
                fmt::print("{}{}", ox::format{ox::escape::reset}, ox::clear_screen{ox::escape::all});
    			current = next;
    			result = get_ranks(dolphin, current.level, current.team, current.mission, buffer);
    			if((result & TIMED_LEVEL) != 0) {
    				if((result & BOSS_LEVEL) != 0) {
    					t_ranks = interpret_time_rank_data(dolphin, reinterpret_cast<boss_timed_stages *>(buffer), current.team);
    				} else if ((result & EXTRA_MISSION) != 0) {
    					t_ranks = interpret_time_rank_data(dolphin, reinterpret_cast<extra_timed_stages *>(buffer), current.team);
    				}
    			} else {
    				if((result & EXTRA_MISSION) != 0) {
    					s_ranks = interpret_score_rank_data(dolphin, reinterpret_cast<extra_stages *>(buffer), current.team);
    				} else {
    					s_ranks = interpret_score_rank_data(dolphin, reinterpret_cast<normal_stages *>(buffer), current.team);
    				}
    			}
    		}

    		if (result == -1)
    			continue;

    		if ((result & TIMED_LEVEL) != 0) {
    			std::array<u8, 3> time = get_time(dolphin);
    			print_current_progress(t_ranks, {time[0] * 60 + time[1], ox::format{ox::escape::background_white, ox::escape::white}});
    		} else {
    			interpret_score(dolphin);
    			print_current_progress(s_ranks, interpret_score(dolphin), 50000);
    		}
    	}
    }
}
