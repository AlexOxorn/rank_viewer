#include <fmt/core.h>
#include <process.h>

#include <sa2/rank_view.hpp>
#include <jsr/variables.hpp>

#ifdef DOLPHIN_PROCESSES
  #include <sonic_heroes/rank_view.hpp>
  #include <sonic_colors/rank_view.hpp>
  #include <shadow/rank_view.hpp>
#endif

#ifdef UNLEASHED_PROCESSES
  #include <unleashed/rank_view.hpp>
#endif

#include <cstdio>
#include <execinfo.h>
#include <csignal>
#include <cstdlib>
#include <unistd.h>

void handler(int sig) {
    void* array[10];

    // get void*'s for all entries on the stack
    auto size = backtrace(array, 10);

    // print out all the frames to stderr
    fprintf(stderr, "Error: signal %d:\n", sig);
    backtrace_symbols_fd(array, size, STDERR_FILENO);
    exit(1);
}

int main(int argc, char** argv) {
    signal(SIGSEGV, handler);
    using namespace std::string_view_literals;

    if (argc < 3) {
        exit(-1);
    }

    int pid = std::stoi(argv[2]);
    void (*display_func)(int) = nullptr;

    if ("sa2"sv == argv[1])
        display_func = sa2::display_ranksX;
#ifdef UNLEASHED_PROCESSES
    else if ("unleashed"sv == argv[1]) {
        display_func = unleashed::display_ranksX;
    }
#endif
#ifdef DOLPHIN_PROCESSES
    else if ("heroes"sv == argv[1])
        display_func = gc::sonic_heroes::display_ranksX;
    else if ("shadow"sv == argv[1])
        display_func = gc::shadow::display_ranksX;
    else if ("colors"sv == argv[1] || "colours"sv == argv[1])
        display_func = gc::sonic_colors::display_ranksX;
#endif

    if (!display_func) {
        printf("Hello World\n");
        exit(-1);
    }

    display_func(pid);
}
