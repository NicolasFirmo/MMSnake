#pragma once

template <typename T>
struct Point2 {
	T x{}, y{};

	constexpr Point2 &operator+=(const Point2 &other) {
		x = other.x;
		y = other.y;
		return *this;
	}

	[[nodiscard]] constexpr Point2 operator+(const Point2 &other) const {
		return {.x = x + other.x, .y = y + other.y};
	}

	[[nodiscard]] constexpr Point2 operator-(const Point2 &other) const {
		return {.x = x - other.x, .y = y - other.y};
	}
	[[nodiscard]] constexpr Point2 operator*(const T &value) const {
		return {.x = x * value, .y = y * value};
	}
};

template <typename T>
constexpr Point2<T> operator*(const T &value, const Point2<T> &vec) {
	return {.x = vec.x * value, .y = vec.x * value};
}