#pragma once

#include <process.h>

template <typename type = int, std::convertible_to<u64> T>
requires std::is_trivially_copyable_v<type>
type get_address(process& process, T address, u64 offset = 0) {
    type to_return;
    process.read_memory(address + offset, &to_return);
    return to_return;
}

template <typename type = int, int length = 3, std::convertible_to<u64> T>
requires std::is_trivially_copyable_v<type>
std::array<type, length> get_array_address(process& process, T address) {
    std::array<type, length> to_return{};
    process.read_memory(address, &to_return);
    return to_return;
}

template <typename type = int, int length = 3, std::convertible_to<u64> T>
requires std::is_trivially_copyable_v<type>
type get_array_address_at(process& process, T address, unsigned index) {
    type to_return{};
    process.read_memory(address + (index * sizeof(type)), &to_return);
    return to_return;
}

#define GAME_VARIABLE(type, name, address) \
    constexpr u64 name##_address = address; \
    inline type get_##name(process& p) { \
        return get_address<type>(p, address); \
    }

#define GAME_INDIRECT_VARIABLE(type, name, base, offset) \
    inline type get_##name(process& p) { \
        return get_address<type>(p, get_##base(p), offset); \
    } \
    inline u64 name##_address(process& p) { \
        return get_##base(p) + offset; \
    } \
    inline std::optional<type> safe_get_##name(process& p) { \
        auto _base = get_##base(p); \
        if (!_base) \
            return std::nullopt; \
        return get_address<type>(p, _base, offset); \
    }

#define GAME_INDIRECT_ARRAY(type, name, base, offset, size) \
    inline std::array<type, size> get_##name(process& p) { \
        return get_array_address<type, size>(p, get_##base(p) + offset); \
    } \
    inline std::optional<std::array<type, size>> safe_get_##name(process& p) { \
        auto _base = get_##base(p); \
        if (!_base) \
            return std::nullopt; \
        return get_array_address<type, size>(p, _base + offset); \
    } \
    inline type get_##name##_at(process& p, unsigned index) { \
        return get_array_address_at<type, size>(p, get_##base(p) + offset, index); \
    } \
    inline std::optional<type> safe_get_##name##_at(process& p, unsigned index) { \
        auto _base = get_##base(p); \
        if (!_base) \
            return std::nullopt; \
        return get_array_address_at<type, size>(p, _base + offset, index); \
    } \
    inline u64 name##_address(process& p) { \
        return get_##base(p) + offset; \
    }

#define GAME_VARIABLE_OFFSET(type, name, address, offset) \
    inline type get_##name(process& p) { \
        return get_address<type>(p, address, get_##offset(p) * sizeof(type)); \
    }

#define GAME_ARRAY_VARIABLE(type, name, address, size) \
    constexpr u64 name##_address = address; \
    inline std::array<type, size> get_##name(process& p) { \
        return get_array_address<type, size>(p, address); \
    } \
    inline type get_##name##_at(process& p, unsigned index) { \
        return get_array_address_at<type, size>(p, address, index); \
    }
