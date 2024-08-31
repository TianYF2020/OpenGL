///* ������Ӧ�Ŀ� */
//#define GLEW_STATIC	
//
//#include <iostream>
//#include "Shader.h"
//#include "GL\glew.h"					// ע����һ����Ҫ���ݸ�����������趨
//#include "GLFW\glfw3.h"
//#include "SOIL2\stb_image.h"
//#include "SOIL2\SOIL2.h"
//#include "Common.h"
//using namespace std;
//int width, height;
//
////* (����һ��ľ��) ��д������λ��  + ��ȡ���� */
//
////��ʱ�������ά�����棬˳ʱ��Ϊ����
////GLfloat vertices_1[] =
////{
////	//position				// color				// texture coords(��������)
////	-1.0f, 1.0f, 0.0f,		1.0f, 0.0f, 0.0f,		0.0f, 1.0f		// ���϶���		���0
////	-1.0f, -1.0f, 0.0f,		0.0f, 1.0f, 0.0f,		0.0f, 0.0f,		// ���¶���		���1
////	1.0f, -1.0f, 0.0f,		0.0f, 0.0f, 1.0f,		1.0f, 0.0f,		// ���¶���		���2
////	1.0f, 1.0f, 0.0f,		1.0f, 1.0f, 1.0f,		1.0f, 1.0f,		// ���϶���		���3
////
////};
////
/////* �ĸ������������Ϣ������ */
////GLuint indices_1[] =
////{
////	//3, 0, 2,		// ���Ϊ 1��2��3 �Ķ�����ϳ�һ��������
////	//1, 2, 0,		// ���Ϊ 0��1��3 �Ķ�����ϳ�һ��������
////	0, 1, 3,		// ���Ϊ 1��2��3 �Ķ�����ϳ�һ��������
////	2, 3, 1,		// ���Ϊ 0��1��3 �Ķ�����ϳ�һ��������
////};
//
//
////��ʱ�������ά�����棬˳ʱ��Ϊ����
//GLfloat vertices_1[] =
//{
//	//position				// color				// texture coords(��������)
//	-1.0f, -1.0f, 0.0f,		0.0f, 1.0f, 0.0f,		0.0f, 0.0f,		// ���¶���		���1
//	1.0f, -1.0f, 0.0f,		0.0f, 0.0f, 1.0f,		1.0f, 0.0f,		// ���¶���		���2
//	1.0f, 1.0f, 0.0f,		1.0f, 1.0f, 1.0f,		1.0f, 1.0f,		// ���϶���		���3
//	-1.0f, 1.0f, 0.0f,		1.0f, 0.0f, 0.0f,		0.0f, 1.0f		// ���϶���		���0
//};
//
///* �ĸ������������Ϣ������ */
//GLuint indices_1[] =
//{
//	1, 2, 0,		// ���Ϊ 0��1��3 �Ķ�����ϳ�һ��������
//	3, 0, 2			// ���Ϊ 1��2��3 �Ķ�����ϳ�һ��������
//};
//
//GLint WIDTH = 600, HEIGHT = 600;
//
//int testmain()
//{
//	glfwInit();
//	unsigned char* image = SOIL_load_image("./image/color.png", &width, &height, 0, SOIL_LOAD_RGBA);			// ��ȡͼƬ
//	int screenWidth = width, screenHeight = height;
//	GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "Learn OpenGL Texture test", nullptr, nullptr);
//	glfwWindowHint(GLFW_DECORATED, GL_FALSE);   //û�б߿�ͱ�����
//	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
//	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//	glfwSetMouseButtonCallback(window, mouse_button_callback);
//	glfwSetCursorPosCallback(window, cursor_position_callback);
//	glfwSetWindowAttrib(window, GLFW_DECORATED, GLFW_FALSE);
//	cout << "screenWidth = " << screenWidth << ", screenHeight = " << screenHeight << endl;
//	glfwMakeContextCurrent(window);
//	glewInit();
//
//	/* �������Լ����õ���ɫ���ı������� */
//
//	Shader ourShader = Shader("./shaders/Vexture/shader_v.glsl", "./shaders/Vexture/shader_f.glsl");		// ���·��
//
//	/* ���ö��㻺�����(VBO) + ���ö����������(VAO) + �����������(EBO)  */
//	GLuint VAO, VBO, EBO;
//	glGenVertexArrays(1, &VAO);
//	glGenBuffers(1, &VBO);
//	glGenBuffers(1, &EBO);
//	glBindVertexArray(VAO);
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_1), vertices_1, GL_STATIC_DRAW);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_1), indices_1, GL_STATIC_DRAW);
//
//	/* �������Ӷ������� */
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
//	glEnableVertexAttribArray(0);	// ͨ�� 0 ��
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
//	glEnableVertexAttribArray(1);	// ͨ�� 1 ��
//	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
//	glEnableVertexAttribArray(2);	// ͨ�� 2 ��
//
//
//	/* �������� */
//	GLuint texture;
//	glGenTextures(1, &texture);
//	glBindTexture(GL_TEXTURE_2D, texture);
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);			// ��ȡͼƬ��Ϣ
//	glGenerateMipmap(GL_TEXTURE_2D);	// ��㽥������
//	SOIL_free_image_data(image);
//
//	/* �����Ʒ�ʽ */
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);	// S ����
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);	// T ����
//
//	/* ������� */
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//	/* ����Ԫ����һ���ص�ʹ�� */
//	ourShader.Use();	// don't forget to activate/use the shader before setting uniforms!
//	int textureLocation = glGetUniformLocation(ourShader.Program, "mTexture");	// �ҵ���ɫ���� uniform ���Ե���Ϊ"ourTexture"�����������
//	glUniform1i(textureLocation, 0);		// ���� OpenGL ����ɫ�������������ĸ�����Ԫ	
//
//	/* draw loop ��ͼѭ�� */
//	while (!glfwWindowShouldClose(window))
//	{
//		/* �ӿ� + ʱ�� */
//		glViewport(0, 0, screenWidth, screenHeight);
//		glfwPollEvents();
//
//		/* ��Ⱦ + �����ɫ���� */
//		glClearColor(0.5f, 0.8f, 0.5f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT);
//
//		/* �������� */
//		glActiveTexture(GL_TEXTURE0);			// ���� 0 ������Ԫ����� 16 ��ͨ��
//		glBindTexture(GL_TEXTURE_2D, texture);	// �����������ǰ���������Ŀ��			
//
//		/* ����ͼ�� */
//		ourShader.Use();
//		glBindVertexArray(VAO);									// �� VAO
//		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);				// �� EBO
//		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);	// ������������ �ӵ�0�����㿪ʼ һ����6��
//		glBindVertexArray(0);									// ��� VAO
//		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);				// ��� EBO
//		glBindTexture(GL_TEXTURE_2D, 0);						// ��� ����
//
//		/* �������� */
//		glfwSwapBuffers(window);
//	}
//
//	/* �ͷ���Դ */
//	glDeleteVertexArrays(1, &VAO);
//	glDeleteBuffers(1, &VBO);
//	glDeleteBuffers(1, &EBO);
//
//	glfwTerminate();	// ����
//	return 0;
//}
