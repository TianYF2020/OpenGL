#include "Common.h"

bool isDragging = false;
GLint WIDTH = 600, HEIGHT = 600;
// 声明一个记录鼠标位置的结构体





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
