#pragma once

#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable : 4100)
#endif

template <typename... T>
constexpr void debugLog(const std::string_view &fmt, T &&...args) {
	if constexpr (DEBUG)
		fmt::print(fmt::fg(fmt::color::green), fmt, std::forward<T>(args)...);
}

#if defined(_MSC_VER)
#pragma warning(pop)
#endif

template <class T>
concept Stringable = requires(T a) {
	{ a.toString() } -> std::convertible_to<std::string>;
};

template <Stringable T>
struct fmt::formatter<T> : fmt::formatter<std::string> {
	auto format(const T &a, fmt::format_context &ctx) {
		return fmt::format_to(ctx.out(), "{}", a.toString());
	}
};