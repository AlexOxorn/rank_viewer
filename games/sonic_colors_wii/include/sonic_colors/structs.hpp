#pragma once

#include <ox/types.h>
#include <ox/bytes.h>
#include <cstddef>
#include <array>
#include <cstdio>
#include <bit>

namespace gc::sonic_colors {
    template <typename T, int Size = sizeof(T)>
    T endian_swap(T thing) {
        if constexpr (Size == 1) {
            return thing;
        } else if constexpr (Size == 2) {
            return std::bit_cast<T>(bswap(std::bit_cast<unsigned short>(thing)));
        } else if constexpr (Size == 4) {
            return std::bit_cast<T>(bswap(std::bit_cast<unsigned int>(thing)));
        } else if constexpr (Size == 8) {
            return std::bit_cast<T>(bswap(std::bit_cast<unsigned long>(thing)));
        }
        else return T{};
    }

// #define es endian_swap

//     unsigned char RSO1[] = {
//             0x73,
//             0x74,
//             0x67,
//             0x31,
//             0x31,
//             0x30,
//             0x00,
//             0x00,
//             0x00,
//             0x00,
//             0x00,
//             0x00,
//             0x00,
//             0x00,
//             0x00,
//             0x00,
//             0x73,
//             0x74,
//             0x67,
//             0x31,
//             0x31,
//             0x30,
//             0x00,
//             0x00,
//             0x00,
//             0x00,
//             0x00,
//             0x00,
//             0x00,
//             0x00,
//             0x00,
//             0x00,
//             0x73,
//             0x74,
//             0x67,
//             0x31,
//             0x31,
//             0x30,
//             0x00,
//             0x00,
//             0x00,
//             0x00,
//             0x00,
//             0x00,
//             0x00,
//             0x00,
//             0x00,
//             0x00,
//             0x00,
//             0x00,
//             0x00,
//             0x00,
//             0x00,
//             0x00,
//             0x00,
//             0x00,
//             0x00,
//             0x00,
//             0x00,
//             0x00,
//             0x00,
//             0x00,
//             0x00,
//             0x00,
//             0xC6,
//             0x3A,
//             0x9B,
//             0x5C,
//             0x44,
//             0xC4,
//             0xFD,
//             0xCB,
//             0x46,
//             0x84,
//             0x98,
//             0xFB,
//             0xC3,
//             0x1F,
//             0x33,
//             0x33,
//             0x00,
//             0x00,
//             0x00,
//             0x00,
//             0x00,
//             0x00,
//             0x00,
//             0x00,
//             0x00,
//             0x00,
//             0x00,
//             0x00,
//             0x80,
//             0xAE,
//             0x2C,
//             0xC0,
//             0x00,
//             0x00,
//             0x00,
//             0x02,
//             0x00,
//             0x00,
//             0x00,
//             0x02,
//             0x00,
//             0x00,
//             0x00,
//             0x01,
//             0x00,
//             0x00,
//             0x00,
//             0x07,
//             0x00,
//             0x00,
//             0x00,
//             0x00,
//             0x00,
//             0x00,
//             0x00,
//             0x00,
//             0x00,
//             0x00,
//             0x00,
//             0x00,
//             0x00,
//             0x00,
//             0x00,
//             0x00,
//             0x00,
//             0x00,
//             0x00,
//             0x00,
//             0x80,
//             0xAE,
//             0x2C,
//             0xE0,
//             0x00,
//             0x00,
//             0x00,
//             0x00,
//             0x00,
//             0x00,
//             0x00,
//             0x00,
//             0x00,
//             0x00,
//             0x00,
//             0x00,
//             0x00,
//             0x00,
//             0x00,
//             0x00,
//             0x00,
//             0x00,
//             0x00,
//             0x00,
//             0x3F,
//             0x91,
//             0x11,
//             0x11,
//             0x20,
//             0x00,
//             0x00,
//             0x00,
//             0x3C,
//             0x88,
//             0x88,
//             0x89,
//             0x40,
//             0x00,
//             0x00,
//             0x00,
//             0x62,
//             0x67,
//             0x6D,
//             0x5F,
//             0x73,
//             0x74,
//             0x67,
//             0x31,
//             0x31,
//             0x30,
//             0x5F,
//             0x72,
//             0x73,
//             0x6F,
//             0x00,
//             0x00,
//             0x00,
//             0x00,
//             0x00,
//             0x00,
//             0x00,
//             0x00,
//             0x00,
//             0x00,
//             0x00,
//             0x00,
//             0x00,
//             0x00,
//             0x00,
//             0x00,
//             0x00,
//             0x00,
//             0x00,
//             0x11,
//             0x8C,
//             0x30,
//             0x00,
//             0x0C,
//             0x35,
//             0x00,
//             0x00,
//             0x09,
//             0xEB,
//             0x10,
//             0x00,
//             0x06,
//             0xDD,
//             0xD0,
//             0x00,
//             0x04,
//             0xE2,
//             0x00,
//             0x00,
//             0x00,
//             0x04,
//             0x4C,
//             0x00,
//             0x04,
//             0x45,
//             0xC0,
//             0x00,
//             0x03,
//             0x34,
//             0x50,
//             0x00,
//             0x02,
//             0xC6,
//             0xF0,
//             0x00,
//             0x00,
//             0xDA,
//             0xC0,
//             0x00,
//             0x00,
//             0x6D,
//             0x60,
//             0x72,
//             0x65,
//             0x73,
//             0x75,
//             0x6C,
//             0x74,
//             0x5F,
//             0x30,
//             0x31,
//             0x5F,
//             0x72,
//             0x73,
//             0x6F,
//             0x5F,
//             0x61,
//             0x63,
//             0x74,
//             0x31,
//             0x00,
//             0x00,
//             0x00,
//             0x00,
//             0x00,
//             0x00,
//             0x00,
//             0x00,
//             0x00,
//             0x00,
//             0x00,
//             0x00,
//             0x00,
//             0x00
//     };

//     unsigned char RSO2[] = {
//             0x73, 0x74, 0x67, 0x31, 0x33, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x73, 0x74, 0x67, 0x31, 0x31, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x73, 0x74, 0x67, 0x31, 0x31, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x45, 0xC4, 0x04, 0x00, 0xC3, 0xCE, 0x00, 0x00, 0x41, 0xAF, 0x5C, 0x29, 0x42, 0xB4, 0x00, 0x00, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x00, 0x80, 0xAE, 0x2D, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xAE, 0x2D, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3F, 0x91, 0x11, 0x11, 0x20, 0x00, 0x00, 0x00, 0x3C, 0x88, 0x88, 0x89, 0x40, 0x00, 0x00, 0x00, 0x62, 0x67, 0x6D, 0x5F, 0x73, 0x74, 0x67, 0x31, 0x32, 0x30, 0x5F, 0x72, 0x73, 0x6F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11, 0x8C, 0x30, 0x00, 0x0A, 0xAE, 0x60, 0x00, 0x08, 0x64, 0x70, 0x00, 0x06, 0x1A, 0x80, 0x00, 0x04, 0xE2, 0x00, 0x00, 0x00, 0x04, 0x4C, 0x00, 0x04, 0x45, 0xC0, 0x00, 0x03, 0x34, 0x50, 0x00, 0x02, 0xC6, 0xF0, 0x00, 0x00, 0xDA, 0xC0, 0x00, 0x00, 0x6D, 0x60, 0x72, 0x65, 0x73, 0x75, 0x6C, 0x74, 0x5F, 0x30, 0x31, 0x5F, 0x72, 0x73, 0x6F, 0x5F, 0x61, 0x63, 0x74, 0x32, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
//     };

//     unsigned char RSO3[] = {
//             0x73, 0x74, 0x67, 0x31, 0x32, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x73, 0x74, 0x67, 0x31, 0x32, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x73, 0x74, 0x67, 0x31, 0x32, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x90, 0x00, 0x00, 0xBE, 0xD1, 0xEB, 0x85, 0x45, 0xF3, 0x20, 0x00, 0xC3, 0x34, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x05, 0x42, 0x48, 0x00, 0x00, 0x80, 0xAE, 0x2D, 0x40, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xAE, 0x2D, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3F, 0x91, 0x11, 0x11, 0x20, 0x00, 0x00, 0x00, 0x3C, 0x88, 0x88, 0x89, 0x40, 0x00, 0x00, 0x00, 0x62, 0x67, 0x6D, 0x5F, 0x73, 0x74, 0x67, 0x31, 0x33, 0x30, 0x5F, 0x72, 0x73, 0x6F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x13, 0xD6, 0x20, 0x00, 0x0C, 0xF8, 0x50, 0x00, 0x09, 0xEB, 0x10, 0x00, 0x06, 0xDD, 0xD0, 0x00, 0x07, 0x18, 0x68, 0x00, 0x00, 0x04, 0xB0, 0x00, 0x06, 0xDD, 0xD0, 0x00, 0x05, 0x26, 0x5C, 0x00, 0x04, 0x76, 0x94, 0x00, 0x01, 0x5F, 0x90, 0x00, 0x00, 0xAF, 0xC8, 0x72, 0x65, 0x73, 0x75, 0x6C, 0x74, 0x5F, 0x30, 0x31, 0x5F, 0x72, 0x73, 0x6F, 0x5F, 0x61, 0x63, 0x74, 0x33, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
//     };

//     unsigned char RSO4[] = {
//             0x73, 0x74, 0x67, 0x31, 0x34, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x73, 0x74, 0x67, 0x31, 0x31, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x73, 0x74, 0x67, 0x31, 0x31, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC6, 0x1C, 0x40, 0x9A, 0x44, 0x34, 0x0E, 0x14, 0x45, 0x8F, 0x44, 0x3D, 0x42, 0xB4, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x05, 0x42, 0x48, 0x00, 0x00, 0x80, 0xAE, 0x2D, 0x80, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xAE, 0x2D, 0xA0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3F, 0x91, 0x11, 0x11, 0x20, 0x00, 0x00, 0x00, 0x3C, 0x88, 0x88, 0x89, 0x40, 0x00, 0x00, 0x00, 0x62, 0x67, 0x6D, 0x5F, 0x73, 0x74, 0x67, 0x31, 0x34, 0x30, 0x5F, 0x72, 0x73, 0x6F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0xF8, 0x50, 0x00, 0x07, 0xA1, 0x20, 0x00, 0x06, 0x1A, 0x80, 0x00, 0x03, 0xD0, 0x90, 0x00, 0x02, 0x49, 0xF0, 0x00, 0x00, 0x03, 0xE8, 0x00, 0x02, 0x49, 0xF0, 0x00, 0x01, 0xB7, 0x74, 0x00, 0x01, 0x7C, 0xDC, 0x00, 0x00, 0x75, 0x30, 0x00, 0x00, 0x3A, 0x98, 0x72, 0x65, 0x73, 0x75, 0x6C, 0x74, 0x5F, 0x30, 0x31, 0x5F, 0x72, 0x73, 0x6F, 0x5F, 0x61, 0x63, 0x74, 0x34, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
//     };

//     unsigned char RSOBoss[] = {
//             0x73, 0x74, 0x67, 0x31, 0x39, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x73, 0x74, 0x67, 0x31, 0x39, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x73, 0x74, 0x67, 0x31, 0x39, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC3, 0x0C, 0x00, 0x00, 0x40, 0xA0, 0x00, 0x00, 0x43, 0x34, 0x00, 0x00, 0x01, 0x01, 0x00, 0x06, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x80, 0xAE, 0x2E, 0x40, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xAE, 0x2E, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3F, 0x91, 0x11, 0x11, 0x20, 0x00, 0x00, 0x00, 0x3C, 0x88, 0x88, 0x89, 0x40, 0x00, 0x00, 0x00, 0x62, 0x67, 0x6D, 0x5F, 0x62, 0x6F, 0x73, 0x73, 0x5F, 0x63, 0x6F, 0x72, 0x65, 0x62, 0x6F, 0x73, 0x73, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1E, 0x84, 0x80, 0x00, 0x1A, 0xB3, 0xF0, 0x00, 0x14, 0x99, 0x70, 0x00, 0x0F, 0x42, 0x40, 0x00, 0x0F, 0x42, 0x40, 0x00, 0x00, 0x13, 0x88, 0x00, 0x0F, 0x42, 0x40, 0x00, 0x0B, 0x71, 0xB0, 0x00, 0x09, 0xEB, 0x10, 0x00, 0x03, 0x0D, 0x40, 0x00, 0x01, 0x86, 0xA0, 0x72, 0x65, 0x73, 0x75, 0x6C, 0x74, 0x5F, 0x30, 0x31, 0x5F, 0x72, 0x73, 0x6F, 0x5F, 0x62, 0x6F, 0x73, 0x73, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
//     };

    struct time_bonus {
        i32 base;
        i32 penalty;
    };

    struct stage_data {
        char stageName[16];         // 0
        char stageData1[16];        // 16
        char stageData2[16];        // 32
        u8 blank30[16];             // 48
        float startX;               // 64
        float startY;               // 68
        float startZ;               // 72
        float startTheta;           // 76
        union {                     // 80
            struct {
                bool is2D;          // 80
                char blankB1_;      // 81
                char blankB2_;      // 82
                u8 LoadingScreen;   // 83
                char blankB4_;      // 84
                char blankB5_;      // 85
                char blankB6_;      // 86
                u8 start_action;    // 87
                float start_speed;  // 88
            };
            char blankB0[12];
        };
        u32 unknown_pointer_BC;     // 92
        u32 unknown_int_C0;         // 96
        u32 unknown_int_C4;         // 100
        u32 unknown_int_C8;         // 104
        u32 unknown_int_CC;         // 108
        u8 blankD0[20];             // 112
        u32 unknown_pointer_E4;     // 132
        u8 blankE8[20];             // 136
        float unknown_float_FC;     // 156
        u32 unknown_flag_00;        // 160
        float unknown_float_04;     // 164
        u32 unknown_flag_08;        // 168
        char background_music[0x20];// 172
        i32 rank_requirements[4];   // 192
        time_bonus time_bonus_data; // 208
        i32 no_miss_bonus[5];       // 216
        char result_background[0x20];// 236

        void endian_swap() {
            ox::bswap(&startX);
            ox::bswap(&startY);
            ox::bswap(&startZ);
            ox::bswap(&startTheta);
            ox::bswap(&time_bonus_data.base);
            ox::bswap(&time_bonus_data.penalty);
            for(auto & i : rank_requirements)
                ox::bswap(&i);
            for(auto & i : no_miss_bonus)
                ox::bswap(&i);
        }
    };

    

    /*
    void print_data(stage_data a) {
        printf("stage name %s\n", a.stageName);
        printf("stage data1 %s\n", a.stageData1);
        printf("stage data2 %s\n", a.stageData2);
        printf("unknown 0x30:\n\t");
        for(auto b : a.blank30)
            printf("%x, ", b);
        printf("\nstart pos: %.2f %.2f %.2f %.2f\n", endian_swap(a.startX), endian_swap(a.startY), endian_swap(a.startZ), endian_swap(a.startTheta));
        printf("unknown 0xB0:\n\t");
        for(auto b : a.blankB0)
            printf("%x, ", b);
        printf("\nPointer 1: %x\n", endian_swap(a.unknown_pointer_BC));
        printf("int 1: %08x\n", es(a.unknown_int_C0));
        printf("int 2: %08x\n", es(a.unknown_int_C4));
        printf("int 3: %08x\n", es(a.unknown_int_C8));
        printf("int 4: %08x\n", es(a.unknown_int_CC));
        printf("unknown 0xD0:\n\t");
        for(auto b : a.blankD0)
            printf("%x, ", b);
        printf("\nPointer 2: %x\n", endian_swap(a.unknown_pointer_E4));
        printf("unknown 0xD0:\n\t");
        for(auto b : a.blankE8)
            printf("%x, ", b);
        printf("\nunknown float 1: %.4f\n", endian_swap(a.unknown_float_FC));
        printf("unknown flag %08x\n", es(a.unknown_flag_00));
        printf("unknown float 2: %.4f\n", endian_swap(a.unknown_float_04));
        printf("unknown flag %08x\n", es(a.unknown_flag_08));
        printf("BGM: %s\n", a.background_music);
        printf("Rank Requirements:\n");
        for(auto b : a.rank_requirements)
            printf("\t%d\n", es(b));
        printf("max time bonus: %d\n", endian_swap(a.max_timebonus));
        printf("time bonus penalty: %d\n", endian_swap(a.timebonus_penalty));
        printf("No Miss Bonus:\n");
        for(auto b : a.no_miss_bonus)
            printf("\t%d\n", es(b));
        printf("Result BGM: %s\n", a.result_background);
    }

    int print_data_shit() {
        static_assert(sizeof(stage_data) == sizeof(RSO1));
        print_data(std::bit_cast<stage_data>(RSO1));
        printf("==========================================\n");
        print_data(std::bit_cast<stage_data>(RSO2));
        printf("==========================================\n");
        print_data(std::bit_cast<stage_data>(RSO3));
        printf("==========================================\n");
        print_data(std::bit_cast<stage_data>(RSO4));
        printf("==========================================\n");
        print_data(std::bit_cast<stage_data>(RSOBoss));
        return 0;
    }
     */


}

#undef es