#include <iostream>
#include <stdio.h>

#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stb/stb_image.h>

#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Debug.h"
#include "shaderClass.h"
#include "Render.h"
#include "Texture.h"
#include "Camera.h"



bool init();

GLFWwindow* window = nullptr;


int main()
{
	if (!init()) {
		return -1;
	}





	GLfloat vertices[] =
	{ //     COORDINATES     /        COLORS          /    TexCoordss   /        NORMALS       //
		-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,      0.0f, -1.0f, 0.0f, // Bottom side
		-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 1.0f,      0.0f, -1.0f, 0.0f, // Bottom side
		 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 1.0f,      0.0f, -1.0f, 0.0f, // Bottom side
		 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 1.0f, 0.0f,      0.0f, -1.0f, 0.0f, // Bottom side

		-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,     -0.8f, 0.5f,  0.0f, // Left Side
		-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 1.0f, 0.0f,     -0.8f, 0.5f,  0.0f, // Left Side
		 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 0.5f, 1.0f,     -0.8f, 0.5f,  0.0f, // Left Side

		-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 1.0f, 0.0f,      0.0f, 0.5f, -0.8f, // Non-facing side
		 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 0.0f,      0.0f, 0.5f, -0.8f, // Non-facing side
		 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 0.5f, 1.0f,      0.0f, 0.5f, -0.8f, // Non-facing side

		 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 0.0f,      0.8f, 0.5f,  0.0f, // Right side
		 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 1.0f, 0.0f,      0.8f, 0.5f,  0.0f, // Right side
		 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 0.5f, 1.0f,      0.8f, 0.5f,  0.0f, // Right side

		 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 1.0f, 0.0f,      0.0f, 0.5f,  0.8f, // Facing side
		-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,      0.0f, 0.5f,  0.8f, // Facing side
		 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 0.5f, 1.0f,      0.0f, 0.5f,  0.8f  // Facing side
	};

	// Indices for vertices order
	GLuint indices[] =
	{
		0, 1, 2, // Bottom side
		0, 2, 3, // Bottom side
		4, 6, 5, // Left side
		7, 9, 8, // Non-facing side
		10, 12, 11, // Right side
		13, 15, 14 // Facing side
	};

	GLfloat lightVertices[] =
	{ //     COORDINATES     //
		-0.1f, -0.1f,  0.1f,
		-0.1f, -0.1f, -0.1f,
		 0.1f, -0.1f, -0.1f,
		 0.1f, -0.1f,  0.1f,
		-0.1f,  0.1f,  0.1f,
		-0.1f,  0.1f, -0.1f,
		 0.1f,  0.1f, -0.1f,
		 0.1f,  0.1f,  0.1f
	};

	GLuint lightIndices[] =
	{
		0, 1, 2,
		0, 2, 3,
		0, 4, 7,
		0, 7, 3,
		3, 7, 6,
		3, 6, 2,
		2, 6, 5,
		2, 5, 1,
		1, 5, 4,
		1, 4, 0,
		4, 5, 6,
		4, 6, 7
	};



	{


		VAO VAO1;
		VAO1.Bind();

		VBO VBO1(vertices, sizeof(vertices));
		VBO1.Unbind();

		EBO EBO1(indices, sizeof(indices));

		VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
		VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
		VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
		VAO1.LinkAttrib(VBO1, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));

		// Shader program initialization
		Shader shaderProgram("resources/base.shader");


		shaderProgram.Bind();
		Renderer renderer;
		Texture png("resources/brick.png");
		shaderProgram.SetUniform1f("u_Texture", 0);

		

		VAO1.Unbind();
		VBO1.Unbind();
		EBO1.Unbind();
		shaderProgram.Unbind();



		// Shader for light cube
		Shader lightShader("resources/light.shader");
		// Generates Vertex Array Object and binds it
		VAO lightVAO;
		lightVAO.Bind();
		// Generates Vertex Buffer Object and links it to vertices
		VBO lightVBO(lightVertices, sizeof(lightVertices));
		// Generates Element Buffer Object and links it to indices
		EBO lightEBO(lightIndices, sizeof(lightIndices));
		// Links VBO attributes such as coordinates and colors to VAO
		lightVAO.LinkAttrib(lightVBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
		// Unbind all to prevent accidentally modifying them
		lightVAO.Unbind();
		lightVBO.Unbind();
		lightEBO.Unbind();

		glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, -1.0f);
		glm::mat4 lightModel = glm::mat4(1.0f);
		lightModel = glm::translate(lightModel, lightPos);


		glm::vec3 pyramidPos = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::mat4 pyramidModel = glm::mat4(1.0f);
		pyramidModel = glm::translate(pyramidModel, pyramidPos);


		lightShader.Bind();
		lightShader.SetUniformMat4f("model", lightModel);
		lightShader.SetUniformVec4f("lightColor", lightColor);
		shaderProgram.Bind();
		shaderProgram.SetUniformMat4f("model", pyramidModel);
		shaderProgram.SetUniformVec4f("lightColor", lightColor);
		shaderProgram.SetUniformVec3f("lightPos", lightPos);

		glm::vec4 testVec(0, 0, 0, 0);

		glEnable(GL_DEPTH_TEST);
		glCullFace(GL_BACK);

		glm::vec3 camPos(0.0f, 1.0f , 3.0f);
		shaderProgram.SetUniformVec3f("camPos", camPos);

		Camera cam(800, 800, camPos);

		glm::mat4 base(1.0f);

		// Main while loop
		while (!glfwWindowShouldClose(window))
		{
			// identity matrix palceholder
			glm::mat4 model(1.0f);
			glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			// Handles camera inputs
			cam.Inputs(window);
			cam.updateMatrix(45.0f, 0.1f, 100.0f, model);


			shaderProgram.Bind();
			shaderProgram.SetUniformVec3f("camPos", cam.GetPos());
			cam.Matrix(shaderProgram, "camMatrix");
			png.Bind();
			VAO1.Bind();
			glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);


			cam.updateMatrix(45.0f, 0.1f, 100.0f, base);


			lightShader.Bind();
			cam.Matrix(lightShader, "camMatrix");
			lightVAO.Bind();
			glDrawElements(GL_TRIANGLES, sizeof(lightIndices) / sizeof(int), GL_UNSIGNED_INT, 0);


			glfwSwapBuffers(window);
			glfwPollEvents();
		}



		// notice theres an extra scope because we have ~ cleanups in our classes that call gl frees after we terminate
		// which we have no active context
	}

	// Delete window before ending the program
	glfwDestroyWindow(window);


	// Terminate GLFW before ending the program
	glfwTerminate();

	
	return 0;
}


bool init()
{

	bool success = true;


	// Initialize GLFW
	glfwInit();


	// Tell GLFW what version of OpenGL we are using 
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a GLFWwindow object of 800 by 800 pixels, naming it "YoutubeOpenGL"
	window = glfwCreateWindow(800, 800, "XUlTRA3D", NULL, NULL);
	// Error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		success = false;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);

	//Load GLAD so it configures OpenGL
	gladLoadGL();

	std::cout << glGetString(GL_VERSION) << std::endl;

	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
	glViewport(0, 0, 800, 800);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);



	return success;
}

