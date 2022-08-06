#pragma once

#include "utility/point.hpp"
#include "utility/rect.hpp"

#include "line_quad.h"

class Renderer {
public:
	static void init();
	static void shutdown();

	static void setViewport(const Rect<GLint, GLsizei>& rect);

	static void setDrawColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
	static void clear();

	static void beginBatch();
	static void endBatch();

	static void drawLine(const Point2<GLfloat>& point0, const Point2<GLfloat>& point1,
						 GLfloat thickness);

private:
	static GLuint vertexArrayId;
	static GLuint vertexBufferId;
	static GLuint indexBufferId;

	static constexpr GLsizei lineQuadsPerBatch	= 1000;
	static constexpr GLsizei indicesPerLineQuad = 6;
	static constexpr GLsizei indicesPerBatch	= lineQuadsPerBatch * indicesPerLineQuad;

	static LineQuad* lineQuadBuffer;
	static LineQuad* currentLineQuad;
	static GLsizei indexCount;
};