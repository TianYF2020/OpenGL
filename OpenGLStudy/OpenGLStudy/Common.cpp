#include "Common.h"
using namespace std;
bool isDragging = false;
GLint WIDTH = 600, HEIGHT = 600;
// ����һ����¼���λ�õĽṹ��


/* ��д��������Ϣ */
vector<GLfloat> vertices_Screen =
{
    //position				// color				// texture coords(��������)
    1.0f, 1.0f, 0.0f,		// ���϶���		���0
    1.0f, -1.0f, 0.0f,		// ���¶���		���1
    -1.0f, -1.0f, 0.0f,		// ���¶���		���2
    -1.0f, 1.0f, 0.0f,		// ���϶���		���3
};

/* �ĸ������������Ϣ������ */
vector<GLuint> indices_Screen =
{
    0, 1, 3,		// ���Ϊ 0��1��3 �Ķ�����ϳ�һ��������
    1, 2, 3			// ���Ϊ 1��2��3 �Ķ�����ϳ�һ��������
};

MousePosition mousePos;
// ���ڴ�С��λ�øı�Ļص�����
void framebuffer_size_callback(GLFWwindow* window, int width, int height) 
{
    glViewport(0, 0, width, height);
}

// ��갴���¼��Ļص�����
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
        glfwTerminate();	// ����
    }
}

// ����ƶ��¼��Ļص�����
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) 
{
    if (isDragging) 
    {
        int windowX, windowY;
        glfwGetWindowPos(window, &windowX, &windowY);
        glfwSetWindowPos(window, windowX + (int)(xpos - mousePos.x), windowY + (int)(ypos - mousePos.y));
    }
}
