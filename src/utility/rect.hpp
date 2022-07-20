#pragma once
#include "utility/size.hpp"
#include "utility/point.hpp"

template <typename PointT, typename SizeT = PointT>
struct Rect {
	Point2<PointT> pos{};
	Size2<SizeT> size{};
};