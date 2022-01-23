//
// Created by alexoxorn on 2022-01-23.
//

#ifndef RANK_VIEWER_PROCESS_H
#define RANK_VIEWER_PROCESS_H

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#elif __unix__

  #include "../unix/native_process.hpp"
  #include "../unix/dolphin_process.hpp"
using native_process = UNIX::native_process;
using dolphin_process = UNIX::dolphin_process;

#endif

using process = abstract_process;

#endif // RANK_VIEWER_PROCESS_H
