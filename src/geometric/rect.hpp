#pragma once

#include "point.hpp"
#include "size.hpp"

template<typename PointT, typename SizeT = PointT>
struct Rect {
	Point2<PointT> pos{};
	Size2<SizeT> size{};
};
