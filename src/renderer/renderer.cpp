#include "renderer.h"

#include "utility/point.hpp"
#include "utility/tracer.h"

GLuint Renderer::vertexArrayId	= 0;
GLuint Renderer::vertexBufferId = 0;
GLuint Renderer::indexBufferId	= 0;

LineQuad *Renderer::lineQuadBuffer	= nullptr;
LineQuad *Renderer::currentLineQuad = nullptr;
GLsizei Renderer::indexCount		= 0;

void Renderer::init() {
	profileTraceFunc();

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	glGenVertexArrays(1, &vertexArrayId);
	glBindVertexArray(vertexArrayId);

	glGenBuffers(1, &vertexBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(LineQuad) * lineQuadsPerBatch, nullptr, GL_DYNAMIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, sizeof(LineQuad::Vertex::worldPt) / sizeof(GLfloat), GL_FLOAT,
						  GL_FALSE, sizeof(LineQuad::Vertex),
						  reinterpret_cast<void *>(offsetof(LineQuad::Vertex, worldPt)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, sizeof(LineQuad::Vertex::modelPt) / sizeof(GLfloat), GL_FLOAT,
						  GL_FALSE, sizeof(LineQuad::Vertex),
						  reinterpret_cast<void *>(offsetof(LineQuad::Vertex, modelPt)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, sizeof(LineQuad::Vertex::modelLength) / sizeof(GLfloat), GL_FLOAT,
						  GL_FALSE, sizeof(LineQuad::Vertex),
						  reinterpret_cast<void *>(offsetof(LineQuad::Vertex, modelLength)));

	std::array<GLuint, indicesPerBatch> rectIndicies;
	for (GLuint i = 0, offset = 0; i < rectIndicies.size(); i += indicesPerLineQuad, offset += 4) {
		rectIndicies[i + 0] = 0 + offset;
		rectIndicies[i + 1] = 1 + offset;
		rectIndicies[i + 2] = 2 + offset;

		rectIndicies[i + 3] = 2 + offset;
		rectIndicies[i + 4] = 3 + offset;
		rectIndicies[i + 5] = 0 + offset;
	}

	glGenBuffers(1, &indexBufferId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesPerBatch, rectIndicies.data(), GL_STATIC_DRAW);

	lineQuadBuffer = new LineQuad[lineQuadsPerBatch];
}

void Renderer::shutdown() {
	profileTraceFunc();

	glDeleteVertexArrays(1, &vertexArrayId);
	glDeleteBuffers(1, &vertexBufferId);
	glDeleteBuffers(1, &indexBufferId);

	delete[] lineQuadBuffer;
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

void Renderer::beginBatch() {
	currentLineQuad = lineQuadBuffer;
	indexCount		= 0;
}

void Renderer::endBatch() {
	profileTraceFunc();

	GLsizeiptr size = (GLubyte *)currentLineQuad - (GLubyte *)lineQuadBuffer;
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
	glBufferSubData(GL_ARRAY_BUFFER, 0, size, lineQuadBuffer);

	glBindVertexArray(vertexArrayId);
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);
}

void Renderer::drawLine(const Point2<GLfloat> &pt0, const Point2<GLfloat> &pt1, GLfloat thickness) {
	LineQuad lineQuad{pt0, pt1, thickness};
	*currentLineQuad = lineQuad;
	++currentLineQuad;
	indexCount += indicesPerLineQuad;

	if (indexCount >= indicesPerBatch) {
		endBatch();
		beginBatch();
	}
}
