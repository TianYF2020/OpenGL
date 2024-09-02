#version 330 core
layout(location = 0) in vec2 aPos;       // 圆的顶点位置
layout(location = 1) in vec2 aOffset;    // 圆心位置的偏移量（实例化数据）
layout(location = 2) in float aRadius;   // 圆的半径（实例化数据）
vec2 scale = vec2(1.0, 16.0 / 9.0);
void main()
{
    // 计算顶点的最终位置
    vec2 position = aPos * aRadius * scale + aOffset;
    gl_Position = vec4(position, 0.0, 1.0);
}
