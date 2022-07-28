#pragma once

template <typename T>
struct Point2 {
	T x{}, y{};

	template <typename OtherT>
	constexpr operator Point2<OtherT>() const {
		return {.x = static_cast<OtherT>(x), .y = static_cast<OtherT>(y)};
	}

	[[nodiscard]] static constexpr Point2 fromPolar(const T &magnitude, const T &angle) {
		return {.x = magnitude * std::cos(angle), .y = magnitude * std::sin(angle)};
	}

	constexpr Point2 &operator+=(const Point2 &other) {
		x += other.x;
		y += other.y;
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
constexpr Point2<T> operator*(const T &value, const Point2<T> &point) {
	return {.x = point.x * value, .y = point.x * value};
}

template <typename T>
constexpr T length2(const Point2<T> &pt0, const Point2<T> &pt1 = {0, 0}) {
	const auto [x, y] = pt0 - pt1;
	return x * x + y * y;
}

template <typename T>
T length(const Point2<T> &pt0, const Point2<T> &pt1 = {0, 0}) {
	return std::sqrt(length2(pt0, pt1));
}
