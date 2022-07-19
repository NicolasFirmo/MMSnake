#pragma once

#ifdef PLATFORM_WINDOWS
#define debugBreak() __debugbreak()
#elif defined PLATFORM_UNIX
#define debugBreak() raise(SIGTRAP)
#else
#error Only Windows and Unix Supported for now!
#endif