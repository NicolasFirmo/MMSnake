#pragma once

template <typename T>
struct Vec2 {
	union {
		struct {
			T x{}, y{};
		};
		struct {
			T w, h;
		};
	};

	Vec2 &operator+=(const Vec2 &other) {
		x = other.x;
		y = other.y;
		return *this;
	}

	Vec2 operator+(const Vec2 &other) { return {.x = x + other.x, .y = y + other.y}; }

	Vec2 operator*(T value) { return {.x = x * value, .y = y * value}; }
};