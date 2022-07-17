#include "screen.h"

#include "utility/log.hpp"

Size2<GLsizei> Screen::size{};
GLFWwindow *Screen::window = nullptr;

bool Screen::init(const char *title, const Size2<GLsizei> &size) {
	Screen::size = size;

	glfwSetErrorCallback([](int error, const char *description) {
		fmt::print(stderr, "GLFW error ({}): {}", error, description);
	});

	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(size.w, size.h, title, NULL, NULL);
	glfwMakeContextCurrent(window);
	if (!window) {
		fmt::print(stderr, "Failed to create GLFW window");
		shutdown();
		return false;
	}

	glfwSwapInterval(1); // vsync

	if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress)) {
		fmt::print(stderr, "Failed to initialize OpenGL context");
		shutdown();
		return false;
	}

	debugLog("OpenGL info:\n");
	debugLog("	Vendor: {:s}\n", reinterpret_cast<const char *>(glGetString(GL_VENDOR)));
	debugLog("	Renderer: {:s}\n", reinterpret_cast<const char *>(glGetString(GL_RENDERER)));
	debugLog("	Version: {:s}\n", reinterpret_cast<const char *>(glGetString(GL_VERSION)));

	glViewport(0, 0, size.w, size.h);

	// TODO(Nicolas): move shader compilation and creation to somewhere else
	auto programId = glCreateProgram();

	const GLchar *vertexShaderSource =
		"#version 460 core\n"
		"\n"
		"layout(location = 0) in vec4 position;\n"
		"\n"
		"void main(){\n"
		"	gl_Position = position;\n"
		"}\n"
		"\n";

	const GLchar *fragmentShaderSource =
		"#version 460 core\n"
		"\n"
		"layout(location = 0) out vec4 color;\n"
		"\n"
		"void main(){\n"
		"	color = vec4(1.0, 1.0, 1.0, 1.0);\n"
		"}\n"
		"\n";

	auto compileShader = [](auto type, const GLchar *source) {
		auto shaderId = glCreateShader(type);
		glShaderSource(shaderId, 1, &source, nullptr);
		glCompileShader(shaderId);

		auto success = GL_TRUE;
		glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
		if (!success) {
			GLchar message[1024];
			glGetShaderInfoLog(shaderId, sizeof(message), nullptr, message);
			fmt::print(stderr, "Failed to compile {}shader: {}",
					   type == GL_VERTEX_SHADER	  ? "vertex " :
					   type == GL_FRAGMENT_SHADER ? "fragment " :
													"",
					   message);
			glDeleteShader(shaderId);
		}

		return shaderId;
	};
	auto vertexShaderId = compileShader(GL_VERTEX_SHADER, vertexShaderSource);
	auto fragmentShaderId = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

	glAttachShader(programId, vertexShaderId);
	glAttachShader(programId, fragmentShaderId);

	glLinkProgram(programId);
	glValidateProgram(programId);

	glDeleteShader(vertexShaderId);
	glDeleteShader(fragmentShaderId);

	glUseProgram(programId);

	// TODO(Nicolas): move buffer initialization to somewhere else
	GLfloat rectVertices[] = {
		.5F, .5F, -.5F, .5F, -.5F, -.5F, .5F, -.5F,
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
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 2, (void *)0);

	return true;
}
void Screen::shutdown() {
	glfwTerminate();
}

void Screen::pollEvents() {
	glfwPollEvents();
}

void Screen::setDrawColor(const GLfloat red, const GLfloat green, const GLfloat blue,
						  const GLfloat alpha) {
	glClearColor(red, green, blue, alpha);
}

void Screen::clear() {
	glClear(GL_COLOR_BUFFER_BIT);
}

void Screen::drawRect(const Rect<GLfloat> &rect) {
	// TODO(Nicolas)
}

void Screen::setTitle(const char *title) {
	glfwSetWindowTitle(window, title);
}

void Screen::show() {
	glDrawElements(GL_LINE_LOOP, 4, GL_UNSIGNED_INT, nullptr);
	glfwSwapBuffers(window);
}