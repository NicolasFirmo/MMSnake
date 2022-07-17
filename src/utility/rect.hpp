#pragma once
#include "utility/size.hpp"
#include "utility/vec.hpp"

template <typename T>
struct Rect {
	Vec2<T> pos{};
	Size2<T> size{};
};