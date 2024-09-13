/* 引入相应的库 */
#pragma once
#define GLEW_STATIC	

#include <iostream>
#include "Shader.h"
#include "GL\glew.h"					// 注：这一部分要根据个人情况进行设定
#include "GLFW\glfw3.h"
#include "SOIL2\stb_image.h"
#include "SOIL2\SOIL2.h"
#include "Common.h"
using namespace std;

class C_DrawRectangle
{
public:
	C_DrawRectangle();
	~C_DrawRectangle();
	void CreatGLWindow(int width, int height);
	void DestroyGLWindow();
	vector<GLfloat> generateCircleVertices(int numSegments);
	//这里区分使用顶点绘制和使用GLSL绘制，一旦切换，需要释放GPU重新分配
	int DrawRectangle_Vertices();	//使用描点的方案来进行绘图
	int DrawRectangle_GLSL();		//使用glsl进行绘图
	int DrawRectangleSingle_GLSL(); //使用glsl绘制单个圆
	int DrawRectangleGrid_GLSL();   //使用按照glsl进行绘制网格圆
	int DrawRectangleGridPixel_GLSL();   //使用glsl按照像素绘图
	Shader *ourShader = nullptr;
private:
	GLuint VAO, VBO,EBO, instanceVBO;
	int screenWidth, screenHeight;
	GLFWwindow* window = nullptr;
	double xpos, ypos;   //鼠标位置
};
