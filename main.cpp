#include <dolphin_process.hpp>
#include <ox/formating.h>
#include <fmt/core.h>
#include <common.hpp>
#include <iostream>
#include <filesystem>

#include <sa2/rank_view.hpp>
#include <sa2/position_view.hpp>
#include <sonic_heroes/rank_view.hpp>
#include <sonic_heroes/variables.hpp>

#include <stdio.h>
#include <execinfo.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>


void handler(int sig) {
  void *array[10];
  size_t size;

  // get void*'s for all entries on the stack
  size = backtrace(array, 10);

  // print out all the frames to stderr
  fprintf(stderr, "Error: signal %d:\n", sig);
  backtrace_symbols_fd(array, size, STDERR_FILENO);
  exit(1);
}

int main(int argc, char** argv) {
    signal(SIGSEGV, handler);
    int pid = -1;

    if (argc < 2) {
        return -1;
    }

    pid = atoi(argv[1]);

    // gc::sonic_heroes::display_ranks(pid);

    dolphin_process game{pid};
    while (true) {
        float_vector spd = gc::sonic_heroes::get_lead_position(game);
        fmt::print("{}", ox::move_cursor{1, 1});
        fmt::print("{}x: {:g}\n", ox::clear_line{ox::escape::all}, spd.x);
        fmt::print("{}y: {:g}\n", ox::clear_line{ox::escape::all}, spd.y);
        fmt::print("{}z: {:g}\n", ox::clear_line{ox::escape::all}, spd.z);
    }
}
