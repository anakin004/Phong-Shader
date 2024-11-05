#pragma once
#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include<glad/glad.h>

class EBO
{
public:
	// ID reference of Elements Buffer Object
	GLuint m_ID;
	// Constructor that generates a Elements Buffer Object and links it to indices
	EBO(GLuint* indices, GLsizeiptr size);
	// Deletes the EBO
	~EBO();

	// Binds the EBO
	void Bind() const;
	// Unbinds the EBO
	void Unbind() const;
	
};

#endif