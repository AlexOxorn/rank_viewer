#pragma once

#include <process.h>

template <typename type = int, std::convertible_to<u64> T>
requires std::is_trivially_copyable_v<type> type get_address(process& process, T address, u64 offset = 0) {
    type to_return;
    process.read_memory(address + offset, &to_return);
    return to_return;
}

template <typename type = int, int length = 3, std::convertible_to<u64> T>
requires std::is_trivially_copyable_v<type> std::array<type, length> get_array_address(process& process, T address) {
    std::array<type, length> to_return{};
    process.read_memory(address, &to_return);
    return to_return;
}

template <typename type = int, int length = 3>
requires std::is_trivially_copyable_v<type> type get_array_address_at(process& process, u32 address, unsigned index) {
    type to_return{};
    process.read_memory(address + (index * sizeof(type)), &to_return);
    return to_return;
}

#define GAME_VARIABLE(type, name, address) \
  constexpr u64 name##_address = address; \
  inline type get_##name(process& p) { return get_address<type>(p, address); }

#define GAME_INDIRECT_VARIABLE(type, name, base, offset) \
  inline type get_##name(process& p) { return get_address<type>(p, get_##base(p), offset); }

#define GAME_VARIABLE_OFFSET(type, name, address, offset) \
  inline type get_##name(process& p) { return get_address<type>(p, address, get_##offset(p) * sizeof(type)); }

#define GAME_ARRAY_VARIABLE(type, name, address, size) \
  constexpr u64 name##_address = address; \
  inline std::array<type, size> get_##name(process& p) { return get_array_address<type, size>(p, address); } \
  inline type get_##name##_at(process& p, unsigned index) { \
    return get_array_address_at<type, size>(p, address, index); \
  }
