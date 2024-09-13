/* 引入相应的库 */
#include "DemoRectangle.h"

C_DrawRectangle::C_DrawRectangle()
{
	CreatGLWindow(2560, 1440);
}

C_DrawRectangle::~C_DrawRectangle()
{
	DestroyGLWindow();
}

/* 编写各顶点信息 */
vector<GLfloat> vertices_Rectangle =
{
	//position				// color				// texture coords(纹理坐标)
	1.0f, 0.0f, 0.0f,		// 右上顶点		编号0
	1.0f, -1.0f, 0.0f,		// 右下顶点		编号1
	0.0f, -1.0f, 0.0f,		// 左下顶点		编号2
	0.0f, 0.0f, 0.0f		// 左上顶点		编号3

};

void C_DrawRectangle::CreatGLWindow(int width, int height)
{
	if (window == nullptr)
	{
		glfwInit();
		screenWidth = width;
		screenHeight = height;
		window = glfwCreateWindow(screenWidth, screenHeight, "Learn OpenGL Texture test", nullptr, nullptr);
		glfwWindowHint(GLFW_DECORATED, GL_FALSE);   //没有边框和标题栏
		glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
		glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
		glfwSetMouseButtonCallback(window, mouse_button_callback);
		glfwSetCursorPosCallback(window, cursor_position_callback);
		glfwSetWindowAttrib(window, GLFW_DECORATED, GLFW_FALSE);
		cout << "screenWidth = " << screenWidth << ", screenHeight = " << screenHeight << endl;
		glfwMakeContextCurrent(window);
		glewInit();
		//开辟GPU内存
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &instanceVBO);
		glGenBuffers(1, &EBO);
	}
}

void C_DrawRectangle::DestroyGLWindow()
{
	if (window != nullptr)
	{
		/* 释放资源 */
		glfwTerminate();	// 结束
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
		glDeleteBuffers(1, &instanceVBO);
		window = nullptr;
	}
}



int C_DrawRectangle::DrawRectangle_Vertices()   //使用描点的方案来进行绘图
{
	std::vector<GLfloat> instanceData =
	{
		//起始坐标x,y,width,height,color(R,G,B)
		0.0f, 0.0f,		0.1f, 0.1f,		1.0f, 0.0f, 0.0f,	// 第一个矩形
		0.5f, -0.5f,	0.2f, 0.1f,		0.0f, 1.0f, 0.0f,	// 第二个矩形
		-0.5f, 0.5f,	0.2f, 0.2f,		0.0f, 0.0f, 1.0f, 	// 第三个矩形
		0.5f,  0.5f,	0.1f, 0.2f,		1.0f, 1.0f, 0.0f, 	// 第四个矩形
		-1.0f,  1.0f,	0.5f, 0.5f,		0.0f, 1.0f,	1.0f, 	// 第五个矩形
	};
			
	ourShader = new Shader("./shaders/Rectangle/shader_v.glsl", "./shaders/Rectangle/shader_f.glsl");		// 相对路径

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ARRAY_BUFFER, vertices_Rectangle.size()*sizeof(GLfloat), &vertices_Rectangle[0], GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_Screen.size() * sizeof(GLuint), &indices_Screen[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// 绑定VBO并传递数据
	glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
	glBufferData(GL_ARRAY_BUFFER, instanceData.size() * sizeof(GLfloat), &instanceData[0], GL_STATIC_DRAW);

	// 设置位置的实例化属性（位置在偏移为0的地方）
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (void*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glVertexAttribDivisor(1, 1); // 每个实例使用一个位置

	// 设置位置的实例化属性（位置在偏移为0的地方）
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	glVertexAttribDivisor(2, 1); // 每个实例使用一个位置

	// 设置半径的实例化属性（半径在偏移为2*sizeof(float)的地方）
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (void*)(4 * sizeof(GLfloat)));
	glEnableVertexAttribArray(3);
	glVertexAttribDivisor(3, 1); // 每个实例使用一个半径

	/* 纹理单元：下一节重点使用 */
	ourShader->Use();	// don't forget to activate/use the shader before setting uniforms!
	/* 视口 + 时间 */
	glViewport(0, 0, screenWidth, screenHeight);

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		/* 渲染 + 清除颜色缓冲 */
		glClearColor(1.0f, 0.8f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		/* 绘制图形 */
		ourShader->Use();
		glBindVertexArray(VAO);									// 解绑定 VAO
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);				// 绑定 EBO
		glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, instanceData.size() / 7+1);
		glBindVertexArray(0);									// 解绑定 VAO
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);				// 解绑定 EBO
										

		/* 交换缓冲 */
		glfwSwapBuffers(window);
	}
	DestroyGLWindow();
	return 0;
}




int C_DrawRectangle::DrawRectangle_GLSL()   //使用glsl进行绘图
{
	/* 将我们自己设置的着色器文本传进来 */
	if (ourShader != nullptr)
	{
		delete ourShader;
	}
	ourShader = new  Shader("./shaders/Circle/Circle_v.glsl", "./shaders/Circle/Circle_f.glsl");		// 相对路径  绘制普通的圆
	//Shader ourShader = Shader("./shaders/Circle/Circle_v.glsl", "./shaders/Circle/CircleGrid_f.glsl");		// 相对路径  多区域绘图
	//Shader ourShader = Shader("./shaders/Circle/Circle_v.glsl", "./shaders/Circle/CircleDemo1_f.glsl");		// 相对路径 绘制圆+鼠标画圆
	/* 设置顶点缓冲对象(VBO) + 设置顶点数组对象(VAO) + 索引缓冲对象(EBO)  */

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ARRAY_BUFFER, vertices_Screen.size() * sizeof(GLfloat), &vertices_Screen[0], GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_Screen.size() * sizeof(GLuint), &indices_Screen[0], GL_STATIC_DRAW);

	/* 设置链接顶点属性 */
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);	// 通道 0 打开

	glm::vec3 screenSize(screenWidth, screenHeight, 1.0f);
	/* 纹理单元：下一节重点使用 */
	ourShader->Use();
	int screenInfor = glGetUniformLocation(ourShader->Program, "iScreenInfor");
	glUniform3fv(screenInfor, 1, glm::value_ptr(screenSize));

	glm::vec4  mousePosition;
	int mouse = glGetUniformLocation(ourShader->Program, "iMouse");
	/* draw loop 画图循环 */

		/* 视口 + 时间 */
	glViewport(0, 0, screenWidth, screenHeight);
	glfwPollEvents();

	/* 渲染 + 清除颜色缓冲 */
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
	if (state == GLFW_PRESS) {

		// 鼠标左键被按下
		glfwGetCursorPos(window, &xpos, &ypos);
		mousePosition = glm::vec4(xpos, screenHeight - ypos, 1.0f, 0.0f);
		glUniform4fv(mouse, 1, glm::value_ptr(mousePosition));
	}

	while (!glfwWindowShouldClose(window))
	{
		glUniform4fv(mouse, 1, glm::value_ptr(mousePosition));
		/* 绘制图形 */
		ourShader->Use();
		glBindVertexArray(VAO);									// 绑定 VAO
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);				// 绑定 EBO
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);	// 画两个三角形 从第0个顶点开始 一共画6次
		glBindVertexArray(0);									// 解绑定 VAO
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);				// 解绑定 EBO

		/* 交换缓冲 */
		glfwSwapBuffers(window);
	}
	DestroyGLWindow();
	return 0;

}


int C_DrawRectangle::DrawRectangleSingle_GLSL()   //使用glsl进行绘图
{

	ourShader = new Shader("./shaders/Circle/Circle_v.glsl", "./shaders/Circle/Circle_f.glsl");		// 相对路径  绘制普通的圆
	//Shader ourShader = Shader("./shaders/Circle/Circle_v.glsl", "./shaders/Circle/CircleGrid_f.glsl");		// 相对路径  多区域绘图
	//Shader ourShader = Shader("./shaders/Circle/Circle_v.glsl", "./shaders/Circle/CircleDemo1_f.glsl");		// 相对路径 绘制圆+鼠标画圆
	/* 设置顶点缓冲对象(VBO) + 设置顶点数组对象(VAO) + 索引缓冲对象(EBO)  */

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ARRAY_BUFFER, vertices_Screen.size() * sizeof(GLfloat), &vertices_Screen[0], GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_Screen.size() * sizeof(GLuint), &indices_Screen[0], GL_STATIC_DRAW);

	/* 设置链接顶点属性 */
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);	// 通道 0 打开

	glm::vec3 screenSize(screenWidth, screenHeight, 1.0f);
	/* 纹理单元：下一节重点使用 */
	ourShader->Use();
	int screenInfor = glGetUniformLocation(ourShader->Program, "iScreenInfor");
	glUniform3fv(screenInfor, 1, glm::value_ptr(screenSize));

	glm::vec4  mousePosition;
	int mouse = glGetUniformLocation(ourShader->Program, "iMouse");

	while (!glfwWindowShouldClose(window))
	{
		/* 视口 + 时间 */
		glViewport(0, 0, screenWidth, screenHeight);
		glfwPollEvents();

		/* 渲染 + 清除颜色缓冲 */
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		/* 绘制图形 */
		ourShader->Use();
		glBindVertexArray(VAO);									// 绑定 VAO
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);				// 绑定 EBO
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);	// 画两个三角形 从第0个顶点开始 一共画6次
		glBindVertexArray(0);									// 解绑定 VAO
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);				// 解绑定 EBO

		/* 交换缓冲 */
		glfwSwapBuffers(window);
	}
	DestroyGLWindow();
	return 0;

}
	
