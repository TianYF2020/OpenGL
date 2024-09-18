#include "DemoText.h"
#include <vector>
// 索引数组，用于定义两个三角形
std::vector<GLuint> indices = {
	0, 1, 2,  // 第一个三角形
	0, 2, 3   // 第二个三角形
};

C_DrawText::C_DrawText()
{
}

C_DrawText::~C_DrawText()
{
	DestroyGLWindow();
}

void C_DrawText::LoadFont(const char* fontPath)
{
	if (FT_Init_FreeType(&ft)) 
	{
		std::cerr << "ERROR::FREETYPE: 无法初始化FreeType库" << std::endl;
		return;
	}

	if (FT_New_Face(ft, fontPath, 0, &face)) {
		std::cerr << "ERROR::FREETYPE: 无法加载字体" << std::endl;
		return;
	}

	// 设置字体大小
	FT_Set_Pixel_Sizes(face, 0, 48);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // 禁用字节对齐限制
}

Character C_DrawText::LoadCharacter(wchar_t ch)
{
	// 如果字符已经存在，直接返回
	if (m_Characters.find(ch) != m_Characters.end()) {
		return m_Characters[ch];
	}

	// 加载字符
	if (FT_Load_Char(face, ch, FT_LOAD_RENDER)) {
		std::cerr << "ERROR::FREETYPE: 无法加载字符 " << ch << std::endl;
		return Character();
	}

	// 生成纹理
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		GL_RED,
		face->glyph->bitmap.width,
		face->glyph->bitmap.rows,
		0,
		GL_RED,
		GL_UNSIGNED_BYTE,
		face->glyph->bitmap.buffer
	);

	// 设置纹理选项
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// 保存字符数据
	Character character = {
		texture,
		glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
		glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
		face->glyph->advance.x
	};

	m_Characters.insert(std::pair<wchar_t, Character>(ch, character));
	return character;
}





void C_DrawText::CreatGLWindow(int width, int height)
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
		glewExperimental = GL_TRUE;		// Initialize GLEW to setup the OpenGL Function pointers
		glewInit();
		//文字的纹理
		glEnable(GL_CULL_FACE);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//开辟GPU内存
		glGenVertexArrays(1, &txtVAO);
		glGenBuffers(1, &txtVBO);
		glGenBuffers(1, &txtEBO);
	}
}

void C_DrawText::DestroyGLWindow()
{
	if (window != nullptr)
	{
		/* 释放资源 */
		glDeleteVertexArrays(1, &txtVAO);
		glDeleteBuffers(1, &txtVBO);
		glDeleteBuffers(1, &txtEBO);
		//glDeleteTextures(1, &texture);
		glfwTerminate();	// 结束
		window = nullptr;
	}
}

void C_DrawText::RenderText(Shader* shader, std::wstring text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color)
{
	// 激活着色器并设置颜色
	shader->Use();
	glUniform3f(glGetUniformLocation(shader->Program, "textColor"), color.x, color.y, color.z);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(txtVAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, txtEBO);				// 绑定 EBO
	// 遍历文本中的每个字符
	std::wstring::const_iterator c;
	for (c = text.begin(); c != text.end(); c++) {
		// 加载或获取字符数据
		Character ch = LoadCharacter(*c);

		GLfloat xpos = x + ch.Bearing.x * scale;  // 绘制电
		GLfloat ypos = y - (ch.Size.y - ch.Bearing.y) * scale;
		GLfloat w = ch.Size.x * scale;
		GLfloat h = ch.Size.y * scale;
		//http://learnopengl.com/img/in-practice/glyph_offset.png
		// 更新VBO中的顶点数据
		GLfloat vertices[4][4] = {
			{ xpos,     ypos + h,   0.0f, 0.0f },   // 左上
			{ xpos,     ypos,       0.0f, 1.0f },   // 左下
			{ xpos + w, ypos,       1.0f, 1.0f },   // 右下
			{ xpos + w, ypos + h,   1.0f, 0.0f }    // 右上
		};
		// 渲染字符纹理
		glBindTexture(GL_TEXTURE_2D, ch.TextureID);

		// 更新顶点数据并绘制
		glBindBuffer(GL_ARRAY_BUFFER, txtVBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// 绘制字符
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// 更新X位置到下一个字符
		x += (ch.Advance >> 6) * scale; // advance是1/64像素
	}

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void C_DrawText::RenderTextNormalize(Shader* shader, std::wstring text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color)
{
	// 激活着色器并设置颜色
	shader->Use();
	glUniform3f(glGetUniformLocation(shader->Program, "textColor"), color.x, color.y, color.z);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(txtVAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, txtEBO);				// 绑定 EBO
	// 遍历文本中的每个字符
	std::wstring::const_iterator c;
	for (c = text.begin(); c != text.end(); c++)
	{
		// 加载或获取字符数据
		Character ch = LoadCharacter(*c);

		GLfloat xpos = (x + (ch.Bearing.x * scale) / screenWidth) * 2.0f - 1.0f;
		GLfloat ypos = (y - (ch.Size.y - ch.Bearing.y) * scale / screenHeight)* 2.0f - 1.0;

		GLfloat w = ch.Size.x * scale / screenWidth * 2.0f;
		GLfloat h = ch.Size.y * scale / screenHeight * 2.0f;

		// 更新VBO中的顶点数据
		GLfloat vertices[4][4] = {
			{ xpos,     ypos + h,   0.0f, 0.0f },   // 左上
			{ xpos,     ypos,       0.0f, 1.0f },   // 左下
			{ xpos + w, ypos,       1.0f, 1.0f },   // 右下
			{ xpos + w, ypos + h,   1.0f, 0.0f }    // 右上
		};

		// 渲染字符纹理
		glBindTexture(GL_TEXTURE_2D, ch.TextureID);

		// 更新顶点数据并绘制
		glBindBuffer(GL_ARRAY_BUFFER, txtVBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// 绘制字符
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// 更新X位置到下一个字符
		x += (ch.Advance >> 6) * scale/ screenWidth; // advance是1/64像素
	}

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

int C_DrawText::DrawText_Vertices()   //使用描点的方案来进行绘图
{
	CreatGLWindow(screenWidth, screenHeight);
	ourShader = new Shader("./shaders/Text/shader_v.glsl", "./shaders/Text/shader_f.glsl");		// 相对路径


	// 设置投影矩阵
	//glm::mat4 projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f); // NDC 范围
	glm::mat4 projection = glm::ortho(0.0f, float(screenWidth), 0.0f, float(screenHeight));
	//glm::mat4 projection = glm::ortho(-float(screenWidth / 2), float(screenWidth/2), -float(screenHeight)/2, float(screenHeight)/2);
	ourShader->Use();
	glUniformMatrix4fv(glGetUniformLocation(ourShader->Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	/* 视口 + 时间 */
	glViewport(0, 0, screenWidth, screenHeight);
	// 使用迭代器遍历 map
	for (auto it = m_Characters.begin(); it != m_Characters.end(); ++it) {
		glDeleteTextures(1, &it->second.TextureID);
	}
	m_Characters.clear();
	LoadFont("./fonts/simsun.ttc");

	// 设置VAO和VBO
	glBindVertexArray(txtVAO);
	glBindBuffer(GL_ARRAY_BUFFER, txtVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 4 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, txtEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		/* 渲染 + 清除颜色缓冲 */
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		//RenderText(ourShader, L"中文,你好 hellow", 500, 500, 1.0f, glm::vec3(1.0, 0.0f, 0.0f));
		//RenderText(ourShader, L"中文,你好 hellow", screenWidth / 2.0, screenHeight/2.0, 1.0f, glm::vec3(1.0, 0.0f, 0.0f));
		RenderTextNormalize(ourShader, L"中文,你好 hellow", 0.0, 0.0, 1.0f, glm::vec3(1.0, 0.0f, 0.0f));
		/* 交换缓冲 */
		glfwSwapBuffers(window);
	}
	DestroyGLWindow();
	return 0;
}


