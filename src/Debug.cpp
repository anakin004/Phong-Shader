#include "Debug.h"


void ClearGl()
{
	GLenum err;
	while (err = glGetError());
}

bool GetError(const char* function, const char* file, int line)
{
	GLenum error = glGetError();

	if (error != GL_NO_ERROR)
	{
		std::cout << "[OpenGL Error] : " << error << " line: " << line << ", Function: " << file << " from: " << function << std::endl;
		return false;
	}

	return true;
}
