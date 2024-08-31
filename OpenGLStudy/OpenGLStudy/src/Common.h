#pragma once

#include <stdio.h>
#include <GLFW/glfw3.h>
#include"glm.hpp"
#include"gtc/matrix_transform.hpp"
#include"gtc/type_ptr.hpp"
#include <vector>


typedef struct mousePos_t
{
	double x, y;
}MousePosition;

extern bool isDragging;
extern MousePosition mousePos;
extern GLint WIDTH, HEIGHT;


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);


int testmain();
int testCircle();
int testCircleBorder();
int testCircleGLSL();   //使用glsl进行绘图