/* ������Ӧ�Ŀ� */
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

// ����Բ�εĶ�������
std::vector<GLfloat> generateCircleBorderVertices(int numSegments)
{
	std::vector<GLfloat> vertices;
	// ���Բ���ϵĶ���
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
	glfwWindowHint(GLFW_DECORATED, GL_FALSE);   //û�б߿�ͱ�����
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
	-0.0f, -0.0f, 0.5f,  // ��һ��Բ��x, yλ�úͰ뾶
	 0.5f, -0.5f, 0.4f,  // �ڶ���Բ
	-0.5f,  0.5f, 0.2f,  // ������Բ
	 0.5f,  0.5f, 0.3f,  // ���ĸ�Բ
	 0.0f,  0.0f, 0.5f   // �����Բ
	};

	vector<GLfloat> circleVertices = generateCircleBorderVertices(numSegments);

	Shader ourShader = Shader("./shaders/Circle/shader_v.glsl", "./shaders/Circle/shader_f.glsl");		// ���·��

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
	// ��VBO����������
	glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
	glBufferData(GL_ARRAY_BUFFER, instanceData.size() * sizeof(GLfloat), &instanceData[0], GL_STATIC_DRAW);

	// ����λ�õ�ʵ�������ԣ�λ����ƫ��Ϊ0�ĵط���
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribDivisor(1, 1); // ÿ��ʵ��ʹ��һ��λ��

	// ���ð뾶��ʵ�������ԣ��뾶��ƫ��Ϊ2*sizeof(float)�ĵط���
	glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	glVertexAttribDivisor(2, 1); // ÿ��ʵ��ʹ��һ���뾶

	glm::vec3 circleColor(1.0f, 0.0f, 0.0f);
	/* ����Ԫ����һ���ص�ʹ�� */
	ourShader.Use();	// don't forget to activate/use the shader before setting uniforms!
	int fillColor = glGetUniformLocation(ourShader.Program, "fillColor");	// �ҵ���ɫ���� uniform ���Ե���Ϊ"ourTexture"�����������
	glUniformMatrix3fv(fillColor, 1, GL_FALSE, glm::value_ptr(circleColor));		// ���� OpenGL ����ɫ�������������ĸ�����Ԫ	

	/* draw loop ��ͼѭ�� */
	while (!glfwWindowShouldClose(window))
	{
		/* �ӿ� + ʱ�� */
		glViewport(0, 0, screenWidth, screenHeight);
		glfwPollEvents();

		/* ��Ⱦ + �����ɫ���� */
		glClearColor(1.0f, 0.8f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		/* ����ͼ�� */
		ourShader.Use();
		glBindVertexArray(VAO);										// ��� VAO
		glDrawArraysInstanced(GL_LINE_LOOP, 0, numSegments + 1, instanceData.size() / 3);
		glBindVertexArray(0);									// ��� VAO
		glBindTexture(GL_TEXTURE_2D, 0);						// ��� ����

		/* �������� */
		glfwSwapBuffers(window);
	}

	/* �ͷ���Դ */
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &instanceVBO);
	glfwTerminate();	// ����
	return 0;
}
