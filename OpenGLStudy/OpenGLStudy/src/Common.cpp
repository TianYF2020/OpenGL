#include "Common.h"
#include <GLFW/glfw3.h>


bool isDragging = false;

// ����һ����¼���λ�õĽṹ��
struct 
{
    double x, y;
} mousePos;

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

// ������
int main() 
{
    // ��ʼ��GLFW
    if (!glfwInit()) 
    {
        return -1;
    }

    // ����һ���ޱ߿򴰿�
    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
    GLFWwindow* window = glfwCreateWindow(800, 600, "GLFW Drag Window", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    // ���ô���λ�ûص�����
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);

    glfwMakeContextCurrent(window);

    // ��ѭ��
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
