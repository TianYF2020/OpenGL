/* ������Ӧ�Ŀ� */
#pragma once
#define GLEW_STATIC	

#include <iostream>
#include "Shader.h"
#include "GL\glew.h"					// ע����һ����Ҫ���ݸ�����������趨
#include "GLFW\glfw3.h"
#include "SOIL2\stb_image.h"
#include "SOIL2\SOIL2.h"
#include "Common.h"
using namespace std;

const int numSegments = 100; // Բ��ϸ�̶ֳ�

class C_DrawCircle
{
public:
	C_DrawCircle();
	~C_DrawCircle();
	void CreatGLWindow(int width, int height);
	void DestroyGLWindow();
	vector<GLfloat> generateCircleVertices(int numSegments);
	//��������ʹ�ö�����ƺ�ʹ��GLSL���ƣ�һ���л�����Ҫ�ͷ�GPU���·���
	int DrawCircle_Vertices();	//ʹ�����ķ��������л�ͼ
	int DrawCircle_GLSL();		//ʹ��glsl���л�ͼ
	int DrawCircleSingle_GLSL(); //ʹ��glsl���Ƶ���Բ
	int DrawCircleGrid_GLSL();   //ʹ�ð���glsl���л�������Բ
	int DrawCircleGridPixel_GLSL();   //ʹ��glsl�������ػ�ͼ
	Shader *ourShader = nullptr;
private:
	GLuint VAO, VBO,EBO, instanceVBO;
	int screenWidth, screenHeight;
	GLFWwindow* window = nullptr;
	double xpos, ypos;   //���λ��
};
