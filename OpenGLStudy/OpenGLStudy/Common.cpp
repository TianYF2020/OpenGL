#include "Common.h"
using namespace std;
bool isDragging = false;
GLint WIDTH = 600, HEIGHT = 600;
// 声明一个记录鼠标位置的结构体


/* 编写各顶点信息 */
vector<GLfloat> vertices_Screen =
{
    //position				// color				// texture coords(纹理坐标)
    1.0f, 1.0f, 0.0f,		// 右上顶点		编号0
    1.0f, -1.0f, 0.0f,		// 右下顶点		编号1
    -1.0f, -1.0f, 0.0f,		// 左下顶点		编号2
    -1.0f, 1.0f, 0.0f,		// 左上顶点		编号3
};

/* 四个顶点的连接信息给出来 */
vector<GLuint> indices_Screen =
{
    0, 1, 3,		// 序号为 0、1、3 的顶点组合成一个三角形
    1, 2, 3			// 序号为 1、2、3 的顶点组合成一个三角形
};

MousePosition mousePos;
// 窗口大小和位置改变的回调函数
void framebuffer_size_callback(GLFWwindow* window, int width, int height) 
{
    glViewport(0, 0, width, height);
}

// 鼠标按键事件的回调函数
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) 
{
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        if (action == GLFW_PRESS) {
            isDragging = true;
            glfwGetCursorPos(window, &mousePos.x, &mousePos.y);
        }
        else if (action == GLFW_RELEASE) {
            isDragging = false;
        }
    }
    else if(button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
        glfwTerminate();	// 结束
    }
}

// 鼠标移动事件的回调函数
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) 
{
    if (isDragging) 
    {
        int windowX, windowY;
        glfwGetWindowPos(window, &windowX, &windowY);
        glfwSetWindowPos(window, windowX + (int)(xpos - mousePos.x), windowY + (int)(ypos - mousePos.y));
    }
}
