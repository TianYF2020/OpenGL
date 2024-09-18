#pragma once

#pragma once
#define GLEW_STATIC	
#include <iostream>
#include "Shader.h"
#include "GL\glew.h"					// 注：这一部分要根据个人情况进行设定
#include "GLFW\glfw3.h"
#include "SOIL2\stb_image.h"
#include "SOIL2\SOIL2.h"
#include "Common.h"
#include "map"
#include "ft2build.h"
#include FT_FREETYPE_H
using namespace std;

// 一个结构体来表示单个字符的纹理数据
struct Character {
	GLuint TextureID;   // 字形纹理ID
	glm::ivec2 Size;    // 字形的尺寸
	glm::ivec2 Bearing; // 字形在基线上的偏移
	GLuint Advance;     // 下一个字形的水平偏移量
};

class C_DrawText
{
public:
	C_DrawText();
	~C_DrawText();
	void CreatGLWindow(int width, int height);
	void LoadFont(const char* fontPath);
	Character LoadCharacter(wchar_t ch);
	void RenderText(Shader* shader, std::wstring text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);
	void RenderTextNormalize(Shader* shader, std::wstring text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);
	int DrawText_Vertices();
	void DestroyGLWindow();
	Shader* ourShader = nullptr;
private:
	GLuint txtVAO, txtVBO, txtEBO;
	//int screenWidth = 1920, screenHeight = 1080;
	int screenWidth = 2560, screenHeight = 1440;
	GLFWwindow* window = nullptr;
	std::map<wchar_t, Character> m_Characters; // 字符集
	FT_Library ft;
	FT_Face face;
};

