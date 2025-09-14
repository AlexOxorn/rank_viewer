//
// Created by alexoxorn on 3/17/25.
//

#ifndef RANK_VIEWER_UNLEASHED_PROCESS_H
#define RANK_VIEWER_UNLEASHED_PROCESS_H

#include "ox/types.h"
#include "ox/bytes.h"
#include "native_process.hpp"
#include <bit>
#include <iostream>
#include <stdio.h>
#include <cinttypes>
#include <fstream>

namespace UNIX {
    class unleashed_process : public native_process {
        intptr_t _werehog_address;

        constexpr static u64 head = 0x100000000;
        using native_process::native_process;
    public:
        unleashed_process(int _pid) : native_process(_pid) {
            // GET OFFSET FROM EXE
            auto exe_path = proc_dir / "exe";
            auto extraction_command = std::format("nm {} | grep WerehogAddress | c++filt", exe_path.c_str());
            intptr_t werehog_file_offset;

            FILE* pipe = popen(extraction_command.c_str(), "r");
            if (!pipe) {
                std::cerr << "Couldn't start command." << std::endl;
                exit(-1);
            }

            int res = fscanf(pipe, "%lx", &werehog_file_offset);
            if (res != 1) {
                std::cerr << "Error Reading Output" << std::endl;
                exit(-1);
            }

            pclose(pipe);

            // GET MAPPED ADDRESS OF EXE
            auto map_path = proc_dir / "maps";

            std::fstream map_file(map_path.c_str(), std::ios::in);
            std::string map_line;
            _werehog_address = 0;
            while (std::getline(map_file, map_line)) {
                if (!map_line.contains("UnleashedRecomp"))
                    continue;
                sscanf(map_line.c_str(), "%lx", &_werehog_address);
                break;
            }

            if (_werehog_address == 0) {
                std::cerr << "Failed To Find Map" << std::endl;
                exit(-1);
            }

            _werehog_address += werehog_file_offset;
        }

        [[nodiscard]] bool wrong_endian([[maybe_unused]] u64 addr) const override {
            return (std::endian::native != std::endian::big); // and (addr < 0x100000000);
        }
        size_t read_memory_raw(u64 address, void* buffer, size_t size, int length) override;
        u64 werehog_address() { return _werehog_address; }
    };
} // namespace UNIX
#endif // RANK_VIEWER_UNLEASHED_PROCESS_H
