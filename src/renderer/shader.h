#pragma once
class Shader {
public:
	struct ShaderType {
		GLenum type;
		const char *extension;
	};

	static constexpr std::array<ShaderType, 2> shaderTypes = {
		ShaderType{  GL_VERTEX_SHADER, "vert"},
		ShaderType{GL_FRAGMENT_SHADER, "frag"},
	};

	Shader() = default;
	Shader(const std::string &name);

	void bind();

private:
	static GLuint compileShader(GLenum type, const GLchar *source);
	static std::string loadShaderSource(std::string_view name, std::string_view extension);

	GLuint id_{0};
};
