#pragma once

#include <process.hpp>

template<typename type = int> requires std::is_trivially_copyable_v<type>
type get_address(process& process, u32 address) {
    type to_return;
    process.read_memory(address, &to_return);
    return to_return;
}

template<typename type = int, int length = 3> requires std::is_trivially_copyable_v<type>
std::array<type, length> get_array_address(process& process, u32 address) {
    std::array<type, length> to_return{};
    process.read_memory(address, &to_return);
    return to_return;
}
