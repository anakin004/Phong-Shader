#ifndef DEBUG_H
#define DEBUG_H

#include <GLFW/glfw3.h>
#include <iostream>
#include <stdio.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


#define ASSERT(x) if (!(x)) __debugbreak();

#define GlCall(x) ClearGl();\
				  x;\
				  ASSERT(GetError(#x, __FILE__, __LINE__ ));



void ClearGl();

bool GetError(const char* function, const char* file, int line);

#endif