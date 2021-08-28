#include <dolphin_process.hpp>
#include <ox/formating.h>
#include <fmt/core.h>
#include <common.hpp>
#include <iostream>
#include <filesystem>

#include <sa2/rank_view.hpp>
#include <sa2/position_view.hpp>
#include <sonic_heroes/position_view.hpp>
#include <sonic_heroes/rank_view.hpp>
#include <sonic_heroes/variables.hpp>

#include <cstdio>
#include <execinfo.h>
#include <csignal>
#include <cstdlib>
#include <string>
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

    if (argc < 2) {
        return -1;
    }

    int pid = std::stoi(argv[1]);

    sa2::display_ranks(pid);
}
