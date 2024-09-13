#version 330 core

uniform vec3      iScreenInfor;           // viewport resolution (in pixels)
uniform vec4      iMouse;                // mouse pixel coords. xy: current (if MLB down), zw: click
out vec4 mFragColor;
//可设置成外部参数
int hSize =5;                                      //行多少个，可外部传参数
int vSize = 5;                                      //列多少个，可外部传参数
float radius = 50;                                  //圆的像素，可外部传参数
float fontSize = 5;                                 //定义边框大小
vec3 circleColor = vec3(1.0, 0.0, 0.0);             //定义圆填充颜色
vec3 circleBorderColor = vec3(0.0, 0.0, 0.0);       //定义圆边框的颜色

//计算参数
vec2 areaSize = vec2(iScreenInfor.x / vSize,iScreenInfor.y / hSize);

void mainImage(out vec4 fragColor, in vec2 fragCoord)
{
    vec2 center = floor(fragCoord / areaSize)* areaSize + areaSize*0.5;
    float distance = length(fragCoord - center);
    if (distance > radius)
    {
        discard;
    }
    else
    {
        vec3 color = circleColor;
        color = mix(color, circleBorderColor, step(radius - fontSize, distance));
        fragColor = vec4(color, 1.0);
    }
}

void main()
{
    mainImage(mFragColor, gl_FragCoord.xy);
}