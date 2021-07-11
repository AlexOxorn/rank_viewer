#include <sa2/rank_view.hpp>

namespace sa2 {
    struct state {
        int level;
        int mission;
        int character;

        bool operator==(state other) const {
            return level == other.level &&
                    mission == other.mission;
        }
    };
    constexpr int stall_time_milli = 2500;

    void display_ranks(int pid) {
        process game{pid};
    	stage_score_rank prototype{};
    	void* buffer = &prototype;

    	std::array<rank_data, 4> s_ranks{};
    	std::array<time_rank_data, 4> t_ranks{};

    	state current{-1, -1};
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
    				t_ranks = interpret_time_rank_data(game, reinterpret_cast<stage_time_rank *>(buffer));
    			} else {
    				s_ranks = interpret_score_rank_data(game, reinterpret_cast<stage_score_rank *>(buffer));
    			}
    		}

    		if (result == -1)
    			continue;

    		if ((result & TIMED_LEVEL) != 0) {
    			minute_second time = get_time(game);
    			print_current_progress(t_ranks, {time.total_seconds(), ox::format{ox::escape::background_white, ox::escape::white}});
    		} else {
    			interpret_score(game);
    			print_current_progress(s_ranks, interpret_score(game), 10000);
    		}
    	}
    }
}
