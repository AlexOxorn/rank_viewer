namespace gc::sonic_heroes {
    constexpr int stall_time_milli = 2500;

    struct state {
        int level;
        int team;
        int mission;

        bool operator<=>(const state& other) const = default;
    };

    [[noreturn]] void display_ranks(int pid);
}
