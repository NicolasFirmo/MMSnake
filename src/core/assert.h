#pragma once

#include "utility/log.hpp"
#include "utility/file_path.h"

#include "core/debug_break.h"

#ifdef PLATFORM_WINDOWS
static constexpr auto srcDir = "src\\"sv;
#elif PLATFORM_UNIX
static constexpr auto srcDir = "src/"sv;
#else
#error Only Windows and Unix Supported for now!
#endif

#ifndef NDEBUG
#define debugAssert(x, message)                                                                    \
	if (!(x)) {                                                                                    \
		static constexpr auto location = std::source_location::current();                          \
		static constexpr auto fileName = getRelativePath(location.file_name(), srcDir);            \
		static constexpr auto functionName = location.function_name();                             \
		static constexpr auto line = location.line();                                              \
		debugLog("assertion falied at {}:{}: {}\n\t on {}: {}\n", fileName, line, message,         \
				 functionName, #x);                                                                \
		debugBreak();                                                                              \
	}
#else
#define debugAssert(x, message) x
#endif // !NDEBUG
