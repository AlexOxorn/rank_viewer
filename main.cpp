#include <sa2/rank_view.hpp>
#include <ox/formating.h>
#include <iostream>

int main(int argc, char** argv) {
	int pid = -1;

	if (argc != 2) {
		return -1;
	}

	pid = atoi(argv[1]);

    // sa2::display_ranks(pid);
    using namespace sa2;
    process p{pid};
    while(true) {
        float_vector pos = sa2::get_player1_position(p);
        fmt::print("{}", ox::clear_screen{ox::escape::all});
        fmt::print("{}{:g}", ox::move_cursor{1, 0}, pos.x);
        fmt::print("{}{:g}", ox::move_cursor{2, 0}, pos.y);
        fmt::print("{}{:g}", ox::move_cursor{3, 0}, pos.z);
        std::cout << std::flush;
    }
}
