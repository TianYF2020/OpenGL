#version 330 core
layout(location = 0) in vec2 aPos;     // ����λ��
layout(location = 1) in vec2 aOffset;    // Բ��λ�õ�ƫ������ʵ�������ݣ�
layout(location = 2) in vec2 aSize;    // Բ��λ�õ�ƫ������ʵ�������ݣ�
layout(location = 3) in vec3 aColor;   // Բ�İ뾶��ʵ�������ݣ�
vec2 scale = vec2(1.0, 16.0 / 9.0);
out vec3 fillColor;
void main()
{
    // ���㶥�������λ��
    vec2 position = aPos * aSize * scale + aOffset;
    gl_Position = vec4(position, 0.0, 1.0);
    fillColor = aColor;
}
