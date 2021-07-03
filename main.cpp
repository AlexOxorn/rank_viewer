#include "memory/dolphin_process.hpp"
#include <rank.hpp>
#include <ox/formating.h>
#include <sonic_heroes/data_extractor.hpp>
#include <iostream>
#include <cstdlib>
#include <unistd.h>

constexpr int stall_time_milli = 2500;

struct LevelRankScores{
	int16_t Level;
	int16_t DRank;
	int16_t CRank;
	int16_t BRank;
	int16_t ARank;
};

struct state {
	int level;
	int team;
	int mission;

	bool operator==(state other) const {
		return level == other.level &&
				team == other.team &&
				mission == other.mission;
	}
};

int main(int argc, char** argv) {
	int pid = -1;

	if (argc != 2) {
		return -1;
	}

	pid = atoi(argv[1]);

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
			printf("%s%s", ox::format{ox::escape::reset}.c_str(), ox::escape_code<ox::escape::clear_screen>{ox::escape::all}.c_str());
			current = next;
			result = get_ranks(dolphin, current.level, current.team, current.mission, buffer);
			if((result & TIMED_LEVEL) != 0) {
				if((result & BOSS_LEVEL) != 0) {
					t_ranks = interpret_time_rank_data(dolphin, reinterpret_cast<boss_timed_stages *>(buffer), current.team);
				} else if ((result & EXTRA_MISSION) != 0) {
					t_ranks = interpret_time_rank_data(dolphin, reinterpret_cast<extra_timed_stages *>(buffer), current.team);
				} else {
					return -1;
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
