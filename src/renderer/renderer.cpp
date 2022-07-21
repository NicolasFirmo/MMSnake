#include "renderer.h"

// TEST
#include "utility/point.hpp"

Shader Renderer::shader{};

void Renderer::init() {
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	// TODO(Nicolas): move shader compilation and creation to somewhere else
	shader = {"basic"};

	// TODO(Nicolas): move buffer initialization to somewhere else
	GLfloat thickness = 0.05F;
	Point2<GLfloat> p0{.x = -0.75F, .y = -0.5F};
	Point2<GLfloat> p1{.x = 0.75F, .y = 0.5F};

	const auto rotate = []<typename T>(const Point2<T> &point, T angle) -> Point2<T> {
		return {.x = point.x * std::cos(angle) - point.y * std::sin(angle),
				.y = point.x * std::sin(angle) + point.y * std::cos(angle)};
	};

	auto thicknessVector = rotate({thickness, 0}, std::atan2(p1.x - p0.x, p1.y - p0.y));

	Point2<GLfloat> p2{.x = p0.x - thicknessVector.y + thicknessVector.x,
					   .y = p0.y - thicknessVector.y - thicknessVector.x};
	Point2<GLfloat> p3{.x = p0.x - thicknessVector.y - thicknessVector.x,
					   .y = p0.y + thicknessVector.y - thicknessVector.x};
	Point2<GLfloat> p4{.x = p1.x + thicknessVector.y + thicknessVector.x,
					   .y = p1.y - thicknessVector.y + thicknessVector.x};
	Point2<GLfloat> p5{.x = p1.x + thicknessVector.y - thicknessVector.x,
					   .y = p1.y + thicknessVector.y + thicknessVector.x};

	GLfloat rectVertices[]{
		p2.x, p2.y, -1.0F - thickness, -thickness, thickness,
		p3.x, p3.y, -1.0F - thickness, thickness,  thickness,
		p4.x, p4.y, 1.0F + thickness,  -thickness, thickness,
		p5.x, p5.y, 1.0F + thickness,  thickness,  thickness,
	};
	GLuint rectIndicies[] = {
		0,
		1,
		2,
		3,
	};

	GLuint vaoId;
	glGenVertexArrays(1, &vaoId);
	glBindVertexArray(vaoId);

	GLuint rectVerticesBufferId;
	glGenBuffers(1, &rectVerticesBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, rectVerticesBufferId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rectVertices), rectVertices, GL_STATIC_DRAW);

	GLuint rectIndiciesBufferId;
	glGenBuffers(1, &rectIndiciesBufferId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rectIndiciesBufferId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(rectIndicies), rectIndicies, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 5, (void *)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 5,
						  (void *)(sizeof(GLfloat) * 2));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 5,
						  (void *)(sizeof(GLfloat) * 4));
}

void Renderer::setViewport(const Rect<GLint, GLsizei> &rect) {
	const auto [x, y] = rect.pos;
	const auto [w, h] = rect.size;
	glViewport(x, y, w, h);
}

void Renderer::setDrawColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) {
	glClearColor(red, green, blue, alpha);
}

void Renderer::clear() {
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::renderFrame() {
	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, nullptr);
}
