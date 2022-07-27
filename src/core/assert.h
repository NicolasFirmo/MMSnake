#pragma once

#include "utility/log.hpp"
#include "utility/file_path.h"

#include "core/debug_break.h"

#ifdef PLATFORM_WINDOWS
static constexpr auto srcDirName = "src\\";
#elif PLATFORM_UNIX
static constexpr auto srcDirName = "src/";
#else
#error Only Windows and Unix Supported for now!
#endif

#ifndef NDEBUG
#define debugAssert(x, message)                                                                    \
	if (!(x)) {                                                                                    \
		static constexpr auto location	   = std::source_location::current();                      \
		static constexpr auto fileName	   = getRelativePath(location.file_name(), srcDirName);    \
		static constexpr auto functionName = location.function_name();                             \
		static constexpr auto line		   = location.line();                                      \
		debugLog("assertion falied on line {} of {} in {}\n\t{}\n", line, functionName, fileName,  \
				 message);                                                                         \
		debugBreak();                                                                              \
	}
#else
#ifdef PLATFORM_UNIX
#define debugAssert(x, message) _Pragma ("GCC diagnostic push") _Pragma ("GCC diagnostic ignored \"-Wunused-value\"") x; _Pragma ("GCC diagnostic pop")
#else
#define debugAssert(x, message) x
#endif // !PLATFORM_UNIX
#endif // !NDEBUG
