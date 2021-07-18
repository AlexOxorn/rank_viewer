#pragma once

#include <process.hpp>

template<typename type = int> requires std::is_trivially_copyable_v<type>
type get_address(process& process, u32 address, u32 offset = 0) {
    type to_return;
    process.read_memory(address + offset, &to_return);
    return to_return;
}

template<typename type = int, int length = 3> requires std::is_trivially_copyable_v<type>
std::array<type, length> get_array_address(process& process, u32 address) {
    std::array<type, length> to_return{};
    process.read_memory(address, &to_return);
    return to_return;
}

#define GAME_VARIABLE(type, name, address) \
constexpr u64 name##_address = address;\
inline type get_##name(process& p) {\
    return get_address<type>(p, address);\
}

#define GAME_INDIRECT_VARIABLE(type, name, base, offset) \
inline type get_##name(process& p) {\
    return get_address<type>(p, get_##base(p), offset);\
}

#define GAME_VARIABLE_OFFSET(type, name, address, offset) \
inline type get_##name(process& p) {\
    return get_address<type>(p, address, get_##offset(p) * sizeof(type));\
}

#define GAME_ARRAY_VARIABLE(type, name, address, size) \
constexpr u64 name##_address = address;\
inline std::array<type, size> get_##name(process& p) {\
    return get_array_address<type, size>(p, address);\
}
