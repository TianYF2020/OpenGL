///* 引入相应的库 */
//#define GLEW_STATIC	
//
//#include <iostream>
//#include "Shader.h"
//#include "GL\glew.h"					// 注：这一部分要根据个人情况进行设定
//#include "GLFW\glfw3.h"
//#include "SOIL2\stb_image.h"
//#include "SOIL2\SOIL2.h"
//#include "Common.h"
//using namespace std;
//int width, height;
//
////* (样例一：木板) 编写各顶点位置  + 读取纹理 */
//
////逆时针的在三维是正面，顺时针为背面
////GLfloat vertices_1[] =
////{
////	//position				// color				// texture coords(纹理坐标)
////	-1.0f, 1.0f, 0.0f,		1.0f, 0.0f, 0.0f,		0.0f, 1.0f		// 左上顶点		编号0
////	-1.0f, -1.0f, 0.0f,		0.0f, 1.0f, 0.0f,		0.0f, 0.0f,		// 左下顶点		编号1
////	1.0f, -1.0f, 0.0f,		0.0f, 0.0f, 1.0f,		1.0f, 0.0f,		// 右下顶点		编号2
////	1.0f, 1.0f, 0.0f,		1.0f, 1.0f, 1.0f,		1.0f, 1.0f,		// 右上顶点		编号3
////
////};
////
/////* 四个顶点的连接信息给出来 */
////GLuint indices_1[] =
////{
////	//3, 0, 2,		// 序号为 1、2、3 的顶点组合成一个三角形
////	//1, 2, 0,		// 序号为 0、1、3 的顶点组合成一个三角形
////	0, 1, 3,		// 序号为 1、2、3 的顶点组合成一个三角形
////	2, 3, 1,		// 序号为 0、1、3 的顶点组合成一个三角形
////};
//
//
////逆时针的在三维是正面，顺时针为背面
//GLfloat vertices_1[] =
//{
//	//position				// color				// texture coords(纹理坐标)
//	-1.0f, -1.0f, 0.0f,		0.0f, 1.0f, 0.0f,		0.0f, 0.0f,		// 左下顶点		编号1
//	1.0f, -1.0f, 0.0f,		0.0f, 0.0f, 1.0f,		1.0f, 0.0f,		// 右下顶点		编号2
//	1.0f, 1.0f, 0.0f,		1.0f, 1.0f, 1.0f,		1.0f, 1.0f,		// 右上顶点		编号3
//	-1.0f, 1.0f, 0.0f,		1.0f, 0.0f, 0.0f,		0.0f, 1.0f		// 左上顶点		编号0
//};
//
///* 四个顶点的连接信息给出来 */
//GLuint indices_1[] =
//{
//	1, 2, 0,		// 序号为 0、1、3 的顶点组合成一个三角形
//	3, 0, 2			// 序号为 1、2、3 的顶点组合成一个三角形
//};
//
//GLint WIDTH = 600, HEIGHT = 600;
//
//int testmain()
//{
//	glfwInit();
//	unsigned char* image = SOIL_load_image("./image/color.png", &width, &height, 0, SOIL_LOAD_RGBA);			// 获取图片
//	int screenWidth = width, screenHeight = height;
//	GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "Learn OpenGL Texture test", nullptr, nullptr);
//	glfwWindowHint(GLFW_DECORATED, GL_FALSE);   //没有边框和标题栏
//	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
//	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//	glfwSetMouseButtonCallback(window, mouse_button_callback);
//	glfwSetCursorPosCallback(window, cursor_position_callback);
//	glfwSetWindowAttrib(window, GLFW_DECORATED, GLFW_FALSE);
//	cout << "screenWidth = " << screenWidth << ", screenHeight = " << screenHeight << endl;
//	glfwMakeContextCurrent(window);
//	glewInit();
//
//	/* 将我们自己设置的着色器文本传进来 */
//
//	Shader ourShader = Shader("./shaders/Vexture/shader_v.glsl", "./shaders/Vexture/shader_f.glsl");		// 相对路径
//
//	/* 设置顶点缓冲对象(VBO) + 设置顶点数组对象(VAO) + 索引缓冲对象(EBO)  */
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
//	/* 设置链接顶点属性 */
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
//	glEnableVertexAttribArray(0);	// 通道 0 打开
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
//	glEnableVertexAttribArray(1);	// 通道 1 打开
//	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
//	glEnableVertexAttribArray(2);	// 通道 2 打开
//
//
//	/* 生成纹理 */
//	GLuint texture;
//	glGenTextures(1, &texture);
//	glBindTexture(GL_TEXTURE_2D, texture);
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);			// 读取图片信息
//	glGenerateMipmap(GL_TEXTURE_2D);	// 多层渐进纹理
//	SOIL_free_image_data(image);
//
//	/* 纹理环绕方式 */
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);	// S 坐标
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);	// T 坐标
//
//	/* 纹理过滤 */
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//	/* 纹理单元：下一节重点使用 */
//	ourShader.Use();	// don't forget to activate/use the shader before setting uniforms!
//	int textureLocation = glGetUniformLocation(ourShader.Program, "mTexture");	// 找到着色器中 uniform 属性的名为"ourTexture"的纹理的索引
//	glUniform1i(textureLocation, 0);		// 告诉 OpenGL 的着色器采样器属于哪个纹理单元	
//
//	/* draw loop 画图循环 */
//	while (!glfwWindowShouldClose(window))
//	{
//		/* 视口 + 时间 */
//		glViewport(0, 0, screenWidth, screenHeight);
//		glfwPollEvents();
//
//		/* 渲染 + 清除颜色缓冲 */
//		glClearColor(0.5f, 0.8f, 0.5f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT);
//
//		/* 生成纹理 */
//		glActiveTexture(GL_TEXTURE0);			// 激活 0 号纹理单元。最多 16 个通道
//		glBindTexture(GL_TEXTURE_2D, texture);	// 绑定这个纹理到当前激活的纹理目标			
//
//		/* 绘制图形 */
//		ourShader.Use();
//		glBindVertexArray(VAO);									// 绑定 VAO
//		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);				// 绑定 EBO
//		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);	// 画两个三角形 从第0个顶点开始 一共画6次
//		glBindVertexArray(0);									// 解绑定 VAO
//		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);				// 解绑定 EBO
//		glBindTexture(GL_TEXTURE_2D, 0);						// 解绑定 纹理
//
//		/* 交换缓冲 */
//		glfwSwapBuffers(window);
//	}
//
//	/* 释放资源 */
//	glDeleteVertexArrays(1, &VAO);
//	glDeleteBuffers(1, &VBO);
//	glDeleteBuffers(1, &EBO);
//
//	glfwTerminate();	// 结束
//	return 0;
//}
