#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "shaderClass.h"

class Texture
{

private:

	GLuint m_ID;
	std::string m_FilePath;
	unsigned char* m_ImgBytes;
	GLint m_Width, m_Height, m_BPP;

	glm::mat4 m_ModelMatrix;

public:

	Texture(const std::string& path);
	~Texture();

	void Bind(GLuint slot = 0) const;
	void Unbind() const;

	inline const glm::mat4& getModelMatrix() const { return m_ModelMatrix; }
	inline int getWidth() const { return m_Width; }
	inline int getHeight() const { return m_Height; }
};




#endif // TEXTURE_H
