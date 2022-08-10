#pragma once

#include "geometric/matrix.hpp"

class Shader {
public:
	struct ShaderType {
		GLenum type;
		const char* extension;
	};

	static constexpr std::array<ShaderType, 2> shaderTypes = {
		ShaderType{  GL_VERTEX_SHADER, "vert"},
		ShaderType{GL_FRAGMENT_SHADER, "frag"},
	};

	Shader() = default;
	Shader(const std::string& name);

	~Shader();

	Shader(const Shader&) = delete;
	Shader(Shader&& other);
	Shader& operator=(const Shader&) = delete;
	Shader& operator=(Shader&& other);

	void bind();

	void setUniformMatrix4(const std::string_view& name, const Matrix4<GLfloat>& matrix);

private:
	static GLuint compileShader(GLenum type, const GLchar* source);
	std::string loadShaderSource(std::string_view name, std::string_view extension);
	std::string parseSource(std::ifstream& file);

	void loadUniformLocations();

	GLuint id_{0};

	struct Uniform {
		std::string name;
		GLint location;
	};
	std::vector<Uniform> uniforms_;
};