#include "Texture.h"


Texture::Texture(const std::string& path)
	: m_ID(0), m_FilePath(path), m_ImgBytes(nullptr), m_Width(0), m_BPP(0), m_Height(0),
	m_ModelMatrix(glm::mat4(1.0f))
{
	stbi_set_flip_vertically_on_load(true);
	m_ImgBytes = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 4);

	glGenTextures(1, &m_ID);
	glBindTexture(GL_TEXTURE_2D, m_ID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);


	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_ImgBytes);
	glBindTexture(GL_TEXTURE_2D, 0);

	if (m_ImgBytes)
		stbi_image_free(m_ImgBytes);

}

Texture::~Texture()
{
	glDeleteTextures(1, &m_ID);
}


void Texture::Bind(GLuint slot /*= 0*/) const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, m_ID);
}

void Texture::Unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

