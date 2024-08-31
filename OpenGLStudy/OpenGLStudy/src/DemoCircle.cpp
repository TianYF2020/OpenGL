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
std::vector<float> generateCircleVertices(int numSegments) 
{
	std::vector<float> vertices;
	// ���Բ�ĵĶ���
	vertices.push_back(0.0f);
	vertices.push_back(0.0f);

	// ���Բ���ϵĶ���
	for (int i = 0; i <= numSegments; ++i) 
	{
		float theta = 2.0f * 3.1415926f * float(i) / float(numSegments);
		float x = cosf(theta);
		float y = sinf(theta);
		vertices.push_back(x);
		vertices.push_back(y);
	}
	return vertices;
}



int testCircle()   //ʹ�����ķ��������л�ͼ
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

	std::vector<float> instanceData = 
	{
	-0.0f, -0.f, 0.1f,  // ��һ��Բ��x, yλ�úͰ뾶
	 0.5f, -0.5f, 0.2f,  // �ڶ���Բ
	-0.5f,  0.5f, 0.2f,  // ������Բ
	 0.5f,  0.5f, 0.1f,  // ���ĸ�Բ
	 0.0f,  0.0f, 0.3f   // �����Բ
	};

	vector<GLfloat> circleVertices = generateCircleVertices(numSegments);

	Shader ourShader = Shader("./shaders/Circle/shader_v.glsl", "./shaders/Circle/shader_f.glsl");		// ���·��

	GLuint VAO,VBO;
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
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribDivisor(1, 1); // ÿ��ʵ��ʹ��һ��λ��

	// ���ð뾶��ʵ�������ԣ��뾶��ƫ��Ϊ2*sizeof(float)�ĵط���
	glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(2);
	glVertexAttribDivisor(2, 1); // ÿ��ʵ��ʹ��һ���뾶

	glm::vec3 circleColor(1.0f, 0.0f, 0.0f);
	/* ����Ԫ����һ���ص�ʹ�� */
	ourShader.Use();	// don't forget to activate/use the shader before setting uniforms!
	int fillColor = glGetUniformLocation(ourShader.Program, "fillColor");	// �ҵ���ɫ���� uniform ���Ե���Ϊ"ourTexture"�����������
	glUniformMatrix3fv(fillColor,1,GL_FALSE, glm::value_ptr(circleColor));		// ���� OpenGL ����ɫ�������������ĸ�����Ԫ	

	/* draw loop ��ͼѭ�� */
	while (!glfwWindowShouldClose(window))
	{
		/* �ӿ� + ʱ�� */
		//glViewport(0, 0, screenWidth, screenHeight);
		glfwPollEvents();

		/* ��Ⱦ + �����ɫ���� */
		glClearColor(1.0f, 0.8f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	

		/* ����ͼ�� */
		ourShader.Use();
		glBindVertexArray(VAO);										// ��� VAO
		glDrawArraysInstanced(GL_TRIANGLE_FAN, 0, numSegments + 2, instanceData.size() / 3);
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


/* ��д��������Ϣ */
GLfloat vertices_Screen[] =
{
	//position				// color				// texture coords(��������)
	1.0f, 1.0f, 0.0f,		// ���϶���		���0
	1.0f, -1.0f, 0.0f,		// ���¶���		���1
	-1.0f, -1.0f, 0.0f,		// ���¶���		���2
	-1.0f, 1.0f, 0.0f,		// ���϶���		���3
};

/* �ĸ������������Ϣ������ */
GLuint indices_Screen[] =
{
	0, 1, 3,		// ���Ϊ 0��1��3 �Ķ�����ϳ�һ��������
	1, 2, 3			// ���Ϊ 1��2��3 �Ķ�����ϳ�һ��������
};


////��ʱ�������ά�����棬˳ʱ��Ϊ����
//GLfloat vertices_Screen[] =
//{
//	//position			
//	-1.0f, -1.0f, 0.0f,		// ���¶���		���1
//	1.0f, -1.0f, 0.0f,		// ���¶���		���2
//	1.0f, 1.0f, 0.0f,		// ���϶���		���3
//	-1.0f, 1.0f, 0.0f		// ���϶���		���0
//};
//
///* �ĸ������������Ϣ������ */
//GLuint indices_Screen[] =
//{
//	1, 2, 0,		// ���Ϊ 0��1��3 �Ķ�����ϳ�һ��������
//	3, 0, 2			// ���Ϊ 1��2��3 �Ķ�����ϳ�һ��������
//};


int testCircleGLSL()   //ʹ��glsl���л�ͼ
{
	glfwInit();
	int screenWidth = 1920, screenHeight = 1080;
	GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "Learn OpenGL Texture test", nullptr, nullptr);
	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
	//glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	//glfwSetMouseButtonCallback(window, mouse_button_callback);
	//glfwSetCursorPosCallback(window, cursor_position_callback);
	//glfwSetWindowAttrib(window, GLFW_DECORATED, GLFW_FALSE);
	cout << "screenWidth = " << screenWidth << ", screenHeight = " << screenHeight << endl;
	glfwMakeContextCurrent(window);
	glewInit();

	/* �������Լ����õ���ɫ���ı������� */
																				
	Shader ourShader = Shader("./shaders/Circle/Circle_v.glsl", "./shaders/Circle/Circle_f.glsl");		// ���·��

	/* ���ö��㻺�����(VBO) + ���ö����������(VAO) + �����������(EBO)  */
	GLuint VAO, VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_Screen), vertices_Screen, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_Screen), indices_Screen, GL_STATIC_DRAW);

	/* �������Ӷ������� */
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);	// ͨ�� 0 ��

	glm::vec3 screenSize(screenWidth, screenHeight, 1.0f);
	/* ����Ԫ����һ���ص�ʹ�� */
	ourShader.Use();	
	int screenInfor = glGetUniformLocation(ourShader.Program, "iScreenInfor");	
	glUniform3fv(screenInfor, 1, glm::value_ptr(screenSize)); 

	glm::vec4  mousePosition;
	int mouse = glGetUniformLocation(ourShader.Program, "iMouse");
	double xpos, ypos;
	/* draw loop ��ͼѭ�� */
	while (!glfwWindowShouldClose(window))
	{
		/* �ӿ� + ʱ�� */
		glViewport(0, 0, screenWidth, screenHeight);
		glfwPollEvents();

		/* ��Ⱦ + �����ɫ���� */
		glClearColor(0.0f, 0.5f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);	

		int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
		if (state == GLFW_PRESS) {

			// ������������
			glfwGetCursorPos(window, &xpos, &ypos);
			mousePosition = glm::vec4(xpos, ypos, 1.0f, 0.0f);
			glUniform4fv(mouse, 1, glm::value_ptr(mousePosition));
		}
		glUniform4fv(mouse, 1, glm::value_ptr(mousePosition));
		/* ����ͼ�� */
		ourShader.Use();
		glBindVertexArray(VAO);									// �� VAO
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);				// �� EBO
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);	// ������������ �ӵ�0�����㿪ʼ һ����6��
		glBindVertexArray(0);									// ��� VAO
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);				// ��� EBO

		/* �������� */
		glfwSwapBuffers(window);
	}

	/* �ͷ���Դ */
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	glfwTerminate();	// ����
	return 0;
}



