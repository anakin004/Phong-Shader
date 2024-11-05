#ifndef CAMERA_H
#define CAMERA_H
#define GLM_ENABLE_EXPERIMENTAL

#include <iostream>
#include <stdio.h>

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>

#include "shaderClass.h"
#include "Texture.h"


class Camera
{
public:
	Camera(int width, int height, glm::vec3& position);


	void Matrix(Shader& shader, const char* uniform);
	void Inputs(GLFWwindow* window);
	void updateMatrix(float FOVdeg, float nearPlane, float farPlane, glm::mat4& model);

	glm::vec3& GetPos() { return m_Position; };

	
private:

	glm::vec3 m_Position;
	glm::vec3 m_Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 m_Up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 m_CameraMatrix;

	int m_Width;
	int m_Height;

	bool m_FirstClick = false;
	float m_Speed = 0.01f;
	float m_Sensitivity = 100.0f;


};



#endif