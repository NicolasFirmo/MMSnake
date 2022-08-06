#include "shader.h"

#include "utility/tracer.h"

Shader::Shader(const std::string& name) {
	profileTraceFunc();

	id_ = glCreateProgram();

	std::array<GLuint, std::size(shaderTypes)> shaderIds{0};

	auto curerntShaderId = shaderIds.begin();
	for (auto&& [type, extension] : shaderTypes) {
		auto shaderSrc = loadShaderSource(name, extension);
		if (shaderSrc.empty())
			continue;

		*curerntShaderId = compileShader(type, shaderSrc.c_str());

		glAttachShader(id_, *curerntShaderId);

		++curerntShaderId;
	}

	glLinkProgram(id_);
	glValidateProgram(id_);

	for (auto&& shaderId : shaderIds)
		if (shaderId != 0)
			glDeleteShader(shaderId);
}

Shader::~Shader() {
	profileTraceFunc();

	if (id_)
		glDeleteProgram(id_);
}

Shader::Shader(Shader&& other) : id_(other.id_) {
	other.id_ = 0;
}

Shader& Shader::operator=(Shader&& other) {
	id_		  = other.id_;
	other.id_ = 0;

	return *this;
}

std::string Shader::loadShaderSource(std::string_view name, std::string_view extension) {
	profileTraceFunc();

	using namespace std::string_literals;
	std::string fileName =
		"assets/shaders/"s + name.data() + '/' + name.data() + '.' + extension.data() + ".glsl";

	std::ifstream file{fileName};

	if (!file.is_open()) {
		fmt::print(stderr, "{}.{}.glsl not found!\n", name, extension);
		return "";
	}

	std::string src;

	file.seekg(0, std::ios::end);
	src.reserve(file.tellg());
	file.seekg(0, std::ios::beg);

	src.assign(std::istreambuf_iterator<GLchar>(file), std::istreambuf_iterator<GLchar>());

	return src;
}

GLuint Shader::compileShader(GLenum type, const GLchar* source) {
	profileTraceFunc();

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

void Shader::bind() {
	glUseProgram(id_);
}