#include <sa2/rank_view.hpp>
#include <sa2/position_view.hpp>
#include <ox/formating.h>
#include <iostream>
#include <filesystem>

int main(int argc, char** argv) {
	int pid = -1;

	if (argc != 2) {
		return -1;
	}

	pid = atoi(argv[1]);

    std::filesystem::path dir = "./sa2_pos_dummp_test";
    sa2::print_position(dir, pid);
    // process game{pid};
    // while(true) {
    //     fmt::print("{}{}", ox::clear_screen{ox::escape::all}, ox::move_cursor{1, 1});
    //     auto position = sa2::get_p1_possition_mirror(game);
    //     fmt::print("{:g}\n{:g}\n{:g}", position.x, position.y, position.z);
    //     // auto position = sa2::get_p1_object_entity_ptr(game);
    //     // fmt::print("{:x}", static_cast<u32>(position));
    //     fflush(stdout);
    // }
}
