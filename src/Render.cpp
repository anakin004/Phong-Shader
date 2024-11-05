#include "Render.h"
#include "Debug.h"



void Renderer::Clear() const
{
	// Specify the color of the background
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	// Clean the back buffer and assign the new color to it
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


void Renderer::Draw(const VAO& va, const EBO& eb, const Shader& shader)
{
	// acitvate and get uniform can both happen above while loop since when we activate it we dont need
	// to keep activating it, as it stays in use until otherwise specified
	// Tell OpenGL which Shader Program we want to use

	shader.Bind();
	eb.Bind();
	va.Bind();

	// Draw the triangles
	GlCall(glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, 0));

}

