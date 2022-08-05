#pragma once

#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable : 4100)
#endif

template <typename... T>
constexpr void debugLog(fmt::format_string<T...> fmt, T &&...args) {
	if constexpr (DEBUG)
		fmt::print(std::move(fmt), std::forward<T>(args)...);
	//fmt::print(fmt::fg(fmt::color::light_green), std::move(fmt), std::forward<T>(args)...); // solve this bug
}

#if defined(_MSC_VER)
#pragma warning(pop)
#endif
