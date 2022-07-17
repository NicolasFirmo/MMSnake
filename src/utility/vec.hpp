#pragma once

template <typename T>
struct Vec2 {
	T x{}, y{};

	constexpr Vec2 &operator+=(const Vec2 &other) {
		x = other.x;
		y = other.y;
		return *this;
	}

	[[nodiscard]] constexpr Vec2 operator+(const Vec2 &other) const {
		return {.x = x + other.x, .y = y + other.y};
	}
	[[nodiscard]] constexpr Vec2 operator*(const T &value) const {
		return {.x = x * value, .y = y * value};
	}
};

template <typename T>
constexpr Vec2<T> operator*(const T &value, const Vec2<T> &vec) {
	return {.x = vec.x * value, .y = vec.x * value};
}