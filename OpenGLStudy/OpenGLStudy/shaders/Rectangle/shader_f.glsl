#version 330 core
//uniform vec3 fillColor = vec3(1.0f,1.0f,1.0f);     // 从顶点着色器接收的片段位置
in vec3 fillColor;
out vec4 FragColor;
void main()
{
    FragColor = vec4(fillColor, 1.0f);
}