//
// Created by alexoxorn on 2022-01-23.
//

#ifndef RANK_VIEWER_PROCESS_H
#define RANK_VIEWER_PROCESS_H

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
  #include "../windows/native_process.hpp"
  #define NATIVE_PROCESSES
using native_process = WINDOWS::native_process;
#elif __unix__
  #include "../unix/native_process.hpp"
  #include "../unix/dolphin_process.hpp"
  #include "../unix/unleashed_process.hpp"
  #define NATIVE_PROCESSES
  #define DOLPHIN_PROCESSES
  #define UNLEASHED_PROCESSES
using native_process = UNIX::native_process;
using unleashed_process = UNIX::unleashed_process;
using dolphin_process = UNIX::dolphin_process;

#endif

using process = abstract_process;

#endif // RANK_VIEWER_PROCESS_H
