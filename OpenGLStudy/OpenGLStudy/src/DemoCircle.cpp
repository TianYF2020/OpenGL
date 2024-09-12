/* 引入相应的库 */
#include "DemoCircle.h"

C_DrawCircle::C_DrawCircle()
{
	CreatGLWindow(2560,1440);
}

C_DrawCircle::~C_DrawCircle()
{
	DestroyGLWindow();
}

void C_DrawCircle::CreatGLWindow(int width,int height)
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

void C_DrawCircle::DestroyGLWindow()
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



int C_DrawCircle::DrawCircle_Vertices()   //使用描点的方案来进行绘图
{
	std::vector<GLfloat> instanceData =
	{
	-0.0f, -0.f, 0.1f,  // 第一个圆的x, y位置和半径
	 0.5f, -0.5f, 0.2f,  // 第二个圆
	-0.5f,  0.5f, 0.2f,  // 第三个圆
	 0.5f,  0.5f, 0.1f,  // 第四个圆
	 0.0f,  0.0f, 0.3f   // 第五个圆
	};
	vector<GLfloat> circleVertices = generateCircleVertices(numSegments);
	ourShader = new Shader("./shaders/Circle/shader_v.glsl", "./shaders/Circle/shader_f.glsl");		// 相对路径

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, circleVertices.size() * sizeof(GLfloat), &circleVertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void*)(sizeof(GLfloat) * 0));
	glEnableVertexAttribArray(0);

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
	ourShader->Use();	// don't forget to activate/use the shader before setting uniforms!
	int fillColor = glGetUniformLocation(ourShader->Program, "fillColor");	// 找到着色器中 uniform 属性的名为"ourTexture"的纹理的索引
	glUniformMatrix3fv(fillColor,1,GL_FALSE, glm::value_ptr(circleColor));		// 告诉 OpenGL 的着色器采样器属于哪个纹理单元	

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
		glBindVertexArray(VAO);										// 解绑定 VAO
		glDrawArraysInstanced(GL_TRIANGLE_FAN, 0, numSegments + 2, instanceData.size() / 3);
		glBindVertexArray(0);									// 解绑定 VAO

		/* 交换缓冲 */
		glfwSwapBuffers(window);
	}
	DestroyGLWindow();
	return 0;
}




int C_DrawCircle::DrawCircle_GLSL()   //使用glsl进行绘图
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


int C_DrawCircle::DrawCircleSingle_GLSL()   //使用glsl进行绘图
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


int C_DrawCircle::DrawCircleGrid_GLSL()   //使用glsl进行绘图
{

	ourShader = new Shader("./shaders/Circle/Circle_v.glsl", "./shaders/Circle/CircleGrid_f.glsl");		// 相对路径  绘制普通的圆
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



int C_DrawCircle::DrawCircleGridPixel_GLSL()   //使用glsl进行绘图
{

	ourShader = new Shader("./shaders/Circle/Circle_v.glsl", "./shaders/Circle/CircleGridPixel_f.glsl");		// 相对路径  绘制普通的圆
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



// 生成圆形的顶点数据
vector<GLfloat> C_DrawCircle::generateCircleVertices(int numSegments)
{
	std::vector<GLfloat> vertices;
	// 添加圆心的顶点
	vertices.push_back(0.0f);
	vertices.push_back(0.0f);

	// 添加圆周上的顶点
	for (int i = 0; i <= numSegments; ++i)
	{
		GLfloat theta = 2.0f * 3.1415926f * GLfloat(i) / float(numSegments);
		GLfloat x = cosf(theta);
		GLfloat y = sinf(theta);
		vertices.push_back(x);
		vertices.push_back(y);
	}
	return vertices;
}


