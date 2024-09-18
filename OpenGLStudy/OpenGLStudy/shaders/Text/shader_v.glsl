#version 330 core
layout(location = 0) in vec4 vertex; // (x, y, z, w) 顶点位置和纹理坐标
out vec2 TexCoords; // 传递到片段着色器的纹理坐标

uniform mat4 projection; // 投影矩阵

void main() 
{
    //gl_Position = projection * vec4(vertex.xy, 0.0, 1.0); // 计算顶点位置
    gl_Position = vec4(vertex.xy, 0.0, 1.0); // 计算顶点位置
    TexCoords = vec2(vertex.z, vertex.w); // 传递纹理坐标
    //TexCoords = vertex.zw; // 传递纹理坐标
}
