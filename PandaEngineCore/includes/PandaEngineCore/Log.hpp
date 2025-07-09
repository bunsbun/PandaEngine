#pragma once

#include "spdlog/spdlog.h"
#include <iostream>

namespace PandaEngine
{

#ifdef NDEBUG
#define LOG_INFO(...)//c++ 20 __VA_OPT__
#define LOG_WARN(...)
#define LOG_ERROR(...)
#define LOG_CRIT(...)

#else

#define LOG_INFO(...)  spdlog::info        (__VA_ARGS__)//c++ 20 __VA_OPT__
#define LOG_WARN(...)  spdlog::warn        (__VA_ARGS__)
#define LOG_ERROR(...) spdlog::error       (__VA_ARGS__)
#define LOG_CRIT(...)  spdlog::critical    (__VA_ARGS__)


#endif // NDEBUG
}