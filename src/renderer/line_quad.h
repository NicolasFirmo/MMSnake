#pragma once

#include "utility/point.hpp"

struct LineQuad {
	struct Vertex {
		Point2<GLfloat> worldPt;
		Point2<GLfloat> modelPt;
		GLfloat modelLength;
	};

	LineQuad() = default;
	LineQuad(const Point2<GLfloat> &pt0, const Point2<GLfloat> &pt1, GLfloat thickness);

	Vertex vertex0;
	Vertex vertex1;
	Vertex vertex2;
	Vertex vertex3;
};
