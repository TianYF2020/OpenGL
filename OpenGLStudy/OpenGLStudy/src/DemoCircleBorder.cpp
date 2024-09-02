/* 引入相应的库 */
#define GLEW_STATIC	

#include <iostream>
#include "Shader.h"
#include "GL\glew.h"					// 注：这一部分要根据个人情况进行设定
#include "GLFW\glfw3.h"
#include "SOIL2\stb_image.h"
#include "SOIL2\SOIL2.h"
#include "Common.h"
using namespace std;

const int numSegments = 100; // 圆的细分程度

// 生成圆形的顶点数据
std::vector<GLfloat> generateCircleBorderVertices(int numSegments)
{
	std::vector<GLfloat> vertices;
	// 添加圆周上的顶点
	for (int i = 0; i <= numSegments; ++i)
	{
		GLfloat theta = 2.0f * 3.1415926f * GLfloat(i) / GLfloat(numSegments);
		GLfloat x = cosf(theta);
		GLfloat y = sinf(theta);
		vertices.push_back(x);
		vertices.push_back(y);
	}
	return vertices;
}



int testCircleBorder()
{
	glfwInit();
	int screenWidth, screenHeight;
	GLFWwindow* window = glfwCreateWindow(2560, 1440, "Learn OpenGL Texture test", nullptr, nullptr);
	glfwWindowHint(GLFW_DECORATED, GL_FALSE);   //没有边框和标题栏
	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetCursorPosCallback(window, cursor_position_callback);
	glfwSetWindowAttrib(window, GLFW_DECORATED, GLFW_FALSE);
	cout << "screenWidth = " << screenWidth << ", screenHeight = " << screenHeight << endl;
	glfwMakeContextCurrent(window);
	glewInit();

	std::vector<GLfloat> instanceData =
	{
	-0.0f, -0.0f, 0.5f,  // 第一个圆的x, y位置和半径
	 0.5f, -0.5f, 0.4f,  // 第二个圆
	-0.5f,  0.5f, 0.2f,  // 第三个圆
	 0.5f,  0.5f, 0.3f,  // 第四个圆
	 0.0f,  0.0f, 0.5f   // 第五个圆
	};

	vector<GLfloat> circleVertices = generateCircleBorderVertices(numSegments);

	Shader ourShader = Shader("./shaders/Circle/shader_v.glsl", "./shaders/Circle/shader_f.glsl");		// 相对路径

	GLuint VAO, VBO;
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, circleVertices.size() * sizeof(GLfloat), &circleVertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void*)(sizeof(GLfloat) * 0));
	glEnableVertexAttribArray(0);
	GLuint instanceVBO;
	glGenBuffers(1, &instanceVBO);
	// 绑定VBO并传递数据
	glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
	glBufferData(GL_ARRAY_BUFFER, instanceData.size() * sizeof(GLfloat), &instanceData[0], GL_STATIC_DRAW);

	// 设置位置的实例化属性（位置在偏移为0的地方）
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribDivisor(1, 1); // 每个实例使用一个位置

	// 设置半径的实例化属性（半径在偏移为2*sizeof(float)的地方）
	glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	glVertexAttribDivisor(2, 1); // 每个实例使用一个半径

	glm::vec3 circleColor(1.0f, 0.0f, 0.0f);
	/* 纹理单元：下一节重点使用 */
	ourShader.Use();	// don't forget to activate/use the shader before setting uniforms!
	int fillColor = glGetUniformLocation(ourShader.Program, "fillColor");	// 找到着色器中 uniform 属性的名为"ourTexture"的纹理的索引
	glUniformMatrix3fv(fillColor, 1, GL_FALSE, glm::value_ptr(circleColor));		// 告诉 OpenGL 的着色器采样器属于哪个纹理单元	

	/* draw loop 画图循环 */
	while (!glfwWindowShouldClose(window))
	{
		/* 视口 + 时间 */
		glViewport(0, 0, screenWidth, screenHeight);
		glfwPollEvents();

		/* 渲染 + 清除颜色缓冲 */
		glClearColor(1.0f, 0.8f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		/* 绘制图形 */
		ourShader.Use();
		glBindVertexArray(VAO);										// 解绑定 VAO
		glDrawArraysInstanced(GL_LINE_LOOP, 0, numSegments + 1, instanceData.size() / 3);
		glBindVertexArray(0);									// 解绑定 VAO
		glBindTexture(GL_TEXTURE_2D, 0);						// 解绑定 纹理

		/* 交换缓冲 */
		glfwSwapBuffers(window);
	}

	/* 释放资源 */
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &instanceVBO);
	glfwTerminate();	// 结束
	return 0;
}
