#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>
#include <unordered_map>



struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};


ShaderProgramSource get_file_contents(const char* filename);

class Shader
{

	public:
		GLuint m_ID;

		Shader(const char* filename);
		~Shader();

		void SetUniform1f(const std::string& uni_name, const float val);
		void SetUniform1i(const std::string& uni_name, const GLint val);
		void SetUniformMat4f(const std::string& uni_name, const glm::mat4& matrix);
		void SetUniformVec4f(const std::string& uni_name, const glm::vec4& vector);
		void SetUniformVec3f(const std::string& uni_name, const glm::vec3& vector);
		GLint getUniform(const std::string& uni_name);
			
		void Bind() const;
		void Unbind() const;
		void compileErrors(unsigned int shader, const char* type);

	private:
		std::unordered_map<std::string, GLint> m_UniformLocationCache;
};

#endif