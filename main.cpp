#include <sonic_heroes/rank_view.hpp>

int main(int argc, char** argv) {
	int pid = -1;

	if (argc != 2) {
		return -1;
	}

	pid = atoi(argv[1]);

    gc::sonic_heroes::display_ranks(pid);
}
