#version 330 core
layout(location = 0) in vec4 vertex; // (x, y, z, w) ����λ�ú���������
out vec2 TexCoords; // ���ݵ�Ƭ����ɫ������������

uniform mat4 projection; // ͶӰ����

void main() 
{
    //gl_Position = projection * vec4(vertex.xy, 0.0, 1.0); // ���㶥��λ��
    gl_Position = vec4(vertex.xy, 0.0, 1.0); // ���㶥��λ��
    TexCoords = vec2(vertex.z, vertex.w); // ������������
    //TexCoords = vertex.zw; // ������������
}
