#version 330 core
//uniform vec3 fillColor = vec3(1.0f,1.0f,1.0f);     // �Ӷ�����ɫ�����յ�Ƭ��λ��
in vec3 fillColor;
out vec4 FragColor;
void main()
{
    FragColor = vec4(fillColor, 1.0f);
}