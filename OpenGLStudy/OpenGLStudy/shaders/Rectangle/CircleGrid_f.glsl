#version 330 core

uniform vec3      iScreenInfor;           // viewport resolution (in pixels)
uniform vec4      iMouse;                // mouse pixel coords. xy: current (if MLB down), zw: click
out vec4 mFragColor;
//可设置成外部参数
int hSize = 5;                                      //行多少个，可外部传参数
int vSize = 5;                                      //列多少个，可外部传参数
float radius = 0.1;                                 //圆的半径，可外部传参数
float fontSize = 5;                                 //定义边框大小
vec3 circleColor = vec3(1.0, 0.0, 0.0);             //定义圆填充颜色
vec3 circleBorderColor = vec3(0.0, 0.0, 0.0);       //定义圆边框的颜色

//计算参数
vec2 coef = vec2(1.0, iScreenInfor.y / iScreenInfor.x); //用来比例缩放的                  
float fontSizeScale = fontSize / iScreenInfor.x;                    //定义边框大小
vec2 areaSize = vec2(1.0f / hSize, 1.0f / vSize);

void mainImage(out vec4 fragColor, in vec2 fragCoord)
{
    //vec3 color = vec3(0.0f, 0.0f, 0.0f);
    vec2 pNormal = fragCoord / iScreenInfor.xy;
    vec2 p = (2.0 * fragCoord - iScreenInfor.xy) * coef / iScreenInfor.xy;
   
    vec2 center = floor(pNormal / areaSize)* areaSize * 2 - vec2(1,1) + areaSize;
    center = center * coef;
    float distance = length(p - center);
    if (distance > radius)
    {
        discard;
    }
    else
    {
        vec3 color = circleColor;
        color = mix(color, circleBorderColor, step(radius - fontSizeScale, distance));
        fragColor = vec4(color, 1.0);
    }
}

void main()
{
    mainImage(mFragColor, gl_FragCoord.xy);
}