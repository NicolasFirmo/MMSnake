#include "line_quad.h"

LineQuad::LineQuad(const Point2<GLfloat> &pt0, const Point2<GLfloat> &pt1, GLfloat thickness)
	: vertex0({{}, {1.0F + thickness, thickness}, thickness}),
	  vertex1({{}, {-1.0F - thickness, thickness},  thickness}),
	  vertex2({{}, {-1.0F - thickness, -thickness},  thickness}),
	  vertex3({{}, {1.0F + thickness, -thickness},  thickness}) {
	const auto rotate = []<typename T>(const Point2<T> &point, T angle) -> Point2<T> {
		return {.x = point.x * std::cos(angle) - point.y * std::sin(angle),
				.y = point.x * std::sin(angle) + point.y * std::cos(angle)};
	};

	auto thicknessVec = rotate({thickness, 0}, std::atan2(pt1.x - pt0.x, pt1.y - pt0.y));

	vertex0.worldPt = {.x = pt1.x + thicknessVec.y - thicknessVec.x,
					   .y = pt1.y + thicknessVec.y + thicknessVec.x};
	vertex1.worldPt = {.x = pt0.x - thicknessVec.y - thicknessVec.x,
					   .y = pt0.y + thicknessVec.y - thicknessVec.x};
	vertex2.worldPt = {.x = pt0.x - thicknessVec.y + thicknessVec.x,
					   .y = pt0.y - thicknessVec.y - thicknessVec.x};
	vertex3.worldPt = {.x = pt1.x + thicknessVec.y + thicknessVec.x,
					   .y = pt1.y - thicknessVec.y + thicknessVec.x};
}
