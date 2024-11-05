#include "Camera.h"
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>


Camera::Camera(int width, int height, glm::vec3& position)
	: m_Width(width), m_Height(height), m_Position(position), m_CameraMatrix(glm::mat4(1.0f))
{

}

void Camera::updateMatrix(float FOVdeg, float nearPlane, float farPlane, glm::mat4& model)
{

	// initlializing view and projection mats
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	// Makes camera look in the right direction from the right position
	view = glm::lookAt(m_Position, m_Position + m_Orientation, m_Up);
	// Adds perspective to the scene
	projection = glm::perspective(glm::radians(FOVdeg), (float)m_Width / m_Height, nearPlane, farPlane);

	// Sets new camera matrix
	m_CameraMatrix = projection * view * model;


}

void Camera::Matrix(Shader& shader, const char* uniform)
{
	// Exports camera matrix
	shader.SetUniformMat4f("camMatrix", m_CameraMatrix);
}


void Camera::Inputs(GLFWwindow* window)
{
	// Handles key inputs
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		m_Position += m_Speed * m_Orientation;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		m_Position += m_Speed * -glm::normalize(glm::cross(m_Orientation, m_Up));
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		m_Position += m_Speed * -m_Orientation;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		m_Position += m_Speed * glm::normalize(glm::cross(m_Orientation, m_Up));
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		m_Position += m_Speed * m_Up;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		m_Position += m_Speed * -m_Up;
	}




	// Handles mouse inputs
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		// Hides mouse cursor
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

		// Prevents camera from jumping on the first click
		if (m_FirstClick)
		{
			glfwSetCursorPos(window, (m_Width / 2), (m_Height / 2));
			m_FirstClick = false;
		}

		// Stores the coordinates of the cursor
		double mouseX;
		double mouseY;
		// Fetches the coordinates of the cursor
		glfwGetCursorPos(window, &mouseX, &mouseY);


		// Normalizes and shifts the coordinates of the cursor such that they begin in the middle of the screen
		// and then "transforms" them into degrees 
		// rotX being rotation about the x-axis, so use right hand rule for refrence
		// same goes for rotY, we rotate about the x axis
		float rotX = m_Sensitivity * (float)(mouseY - (m_Height / 2)) / m_Height;
		float rotY = m_Sensitivity * (float)(mouseX - (m_Width / 2)) / m_Width;

		// Rotates the Orientation left and right
		m_Orientation = glm::rotate(m_Orientation, glm::radians(-rotY), m_Up);

		// up and down
		glm::vec3 newOrientation = glm::rotate(m_Orientation, glm::radians(rotX), glm::normalize(glm::cross(m_Up, m_Orientation)));

		if (abs(glm::angle(newOrientation, m_Up) - glm::radians(90.0f)) <= glm::radians(85.0f))
		{
			m_Orientation = newOrientation;
		}

		// Sets mouse cursor to the middle of the screen so that it doesn't end up roaming around
		glfwSetCursorPos(window, (m_Width / 2), (m_Height / 2));
	}

	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
	{
		// Unhides cursor since camera is not looking around anymore
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		// Makes sure the next time the camera looks around it doesn't jump
		m_FirstClick = true;
	}
}