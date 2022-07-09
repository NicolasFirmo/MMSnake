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
};