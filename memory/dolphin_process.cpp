#include "dolphin_process.hpp"
#include <vector>
#include <ranges>
#include <algorithm>
#include <ranges>
#include <filesystem>
#include <fstream>

dolphin_process::dolphin_process(int _pid) : process{_pid} {
    std::ifstream maps_file{ proc_dir / "maps"};
    std::string line;

    bool mem1_found = false;
    while (getline(maps_file, line)) {
        std::vector<std::string> line_data;
        std::string token;
        std::stringstream ss(line);
        while (getline(ss, token, ' ')) {
            if (!token.empty())
                line_data.push_back(token);
        }

        if (line_data.size() < 3)
          continue;

        bool found_dolphin_shared_meme = false;
        for (const auto& str : line_data){
            if (str.starts_with("/dev/shm/dolphinmem") || str.starts_with("/dev/shm/dolphin-emu")) {
                found_dolphin_shared_meme = true;
                break;
            }
        }

        if (!found_dolphin_shared_meme)
            continue;

        u32 offset = 0;
        std::string offset_string("0x" + line_data[2]);
        offset = std::stoul(offset_string, nullptr, 16);
        if (offset != 0 && offset != 0x2040000)
            continue;

        u64 firstAddress = 0;
        u64 SecondAddress = 0;
        int indexDash = line_data[0].find('-');
        std::string first_address_sring("0x" + line_data[0].substr(0, indexDash));
        std::string second_address_string("0x" + line_data[0].substr(indexDash + 1));

        firstAddress = std::stoul(first_address_sring, nullptr, 16);
        SecondAddress = std::stoul(second_address_string, nullptr, 16);

        if (SecondAddress - firstAddress == 0x4000000 && offset == 0x2040000) {
            mem2_address = firstAddress;
            mem2_present = true;
            if (mem1_found)
                break;
        }

        if (SecondAddress - firstAddress == 0x2000000 && offset == 0x0) {
            emu_ram_address = firstAddress;
            mem1_found = true;
        }
    }
}

int dolphin_process::read_memory_raw(i64 address, void* buffer, size_t size, int length) {
    if (address > dolphin_process::gc_memory_start) {
        address -= dolphin_process::gc_memory_start;
    }
    i64 ram_address = emu_ram_address + address;
    return process::read_memory_raw(ram_address, buffer, size, length);
}

int dolphin_process::write_memory_raw(i64 address, void* buffer, size_t size, int length) {
    if (address > dolphin_process::gc_memory_start) {
        address -= dolphin_process::gc_memory_start;
    }
    i64 ram_address = emu_ram_address + address;
    return process::write_memory_raw(ram_address, buffer, size, length);
}
