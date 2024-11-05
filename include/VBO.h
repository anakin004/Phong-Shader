#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include <glad/glad.h>

class VBO
{
public:	
	GLuint m_ID;

	VBO(GLfloat* vertecies, GLsizeiptr size);
	~VBO();

	void Bind() const;
	void Unbind() const;


};


#endif