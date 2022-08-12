#include "line_quad.h"

#include "utility/tracer.h"

LineQuad::LineQuad(const Point2<GLfloat>& pt0, const Point2<GLfloat>& pt1,
				   const GLfloat thickness) {
	profileTraceFunc();

	const auto rotate = []<typename T>(const Point2<T>& point, T angle) -> Point2<T> {
		return {.x = point.x * std::cos(angle) - point.y * std::sin(angle),
				.y = point.x * std::sin(angle) + point.y * std::cos(angle)};
	};

	const auto thicknessVec = rotate({thickness, 0}, std::atan2(pt1.x - pt0.x, pt1.y - pt0.y));

	vertex0.worldPt = {.x = pt1.x + thicknessVec.y - thicknessVec.x,
					   .y = pt1.y + thicknessVec.y + thicknessVec.x};
	vertex1.worldPt = {.x = pt0.x - thicknessVec.y - thicknessVec.x,
					   .y = pt0.y + thicknessVec.y - thicknessVec.x};
	vertex2.worldPt = {.x = pt0.x - thicknessVec.y + thicknessVec.x,
					   .y = pt0.y - thicknessVec.y - thicknessVec.x};
	vertex3.worldPt = {.x = pt1.x + thicknessVec.y + thicknessVec.x,
					   .y = pt1.y - thicknessVec.y + thicknessVec.x};

	const auto normalizedLength = length(pt0, pt1) / 2 / thickness;

	vertex0.modelPt = {.x = 1.0F + normalizedLength, .y = 1.0F};
	vertex1.modelPt = {.x = -1.0F - normalizedLength, .y = 1.0F};
	vertex2.modelPt = {.x = -1.0F - normalizedLength, .y = -1.0F};
	vertex3.modelPt = {.x = 1.0F + normalizedLength, .y = -1.0F};

	vertex0.modelLength = normalizedLength;
	vertex1.modelLength = normalizedLength;
	vertex2.modelLength = normalizedLength;
	vertex3.modelLength = normalizedLength;
}