#ifndef RENDERER_H
#define RENDERER_H



#include "VAO.h"
#include "EBO.h"
#include "shaderClass.h"

class Renderer
{

public:


	void Draw(const VAO& va, const EBO& eb, const Shader& shader);
	void Clear() const;


private:

};



#endif