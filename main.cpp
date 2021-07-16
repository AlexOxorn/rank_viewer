#include <sa2/rank_view.hpp>
#include <sonic_heroes/rank_view.hpp>
#include <sa2/position_view.hpp>
#include <ox/formating.h>
#include <iostream>
#include <filesystem>

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

    gc::sonic_heroes::display_ranks(pid);

    //std::filesystem::path dir = argv[2];
    //sa2::print_position(dir, pid);
}
