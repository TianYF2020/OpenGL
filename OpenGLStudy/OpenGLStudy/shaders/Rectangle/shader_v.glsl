#version 330 core
layout(location = 0) in vec2 aPos;       // Բ�Ķ���λ��
layout(location = 1) in vec2 aOffset;    // ���ε�ƫ������ʵ�������ݣ�
layout(location = 2) in vec2 aWidth;     // ���εĴ���ʵ�������ݣ�
layout(location = 3) in vec3 aColor;     // ���ε���ɫ��ʵ�������ݣ�
vec2 scale = vec2(1.0, 16.0/9.0);
out vec3 fColor;
void main()
{
    // ���㶥�������λ��
    vec2 position = aPos * aWidth*2 * scale + aOffset;
    gl_Position = vec4(position, 0.0, 1.0);
    fColor = aColor;
}
