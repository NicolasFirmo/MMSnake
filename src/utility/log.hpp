#pragma once

template <typename... T>
constexpr void debugLog(fmt::format_string<T...> fmt, T &&...args) {
	if constexpr (DEBUG)
		fmt::print(std::move(fmt), std::forward<T>(args)...);
}