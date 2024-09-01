#version 330 core

uniform vec3      iScreenInfor;           // viewport resolution (in pixels)
uniform vec4      iMouse;                // mouse pixel coords. xy: current (if MLB down), zw: click
out vec4 mFragColor;

//可外部传参
float radius = 0.1;                                 //圆的半径
vec2  center = vec2(0, 0);                          //定义圆心坐标
vec3  circleColor = vec3(1.0, 0.0, 0.0);            //定义圆填充颜色
vec3  circleBorderColor = vec3(0.0, 0.0, 0.0);      //定义圆边框的颜色
float fontSize = 5;

vec2 coef = vec2(1.0, iScreenInfor.y/iScreenInfor.x); //计算缩放比例
vec2 centerScale = center * coef;                   //按照比例缩放的圆心坐标               
float fontSizeScale = fontSize / iScreenInfor.x;    //定义边框大小

void mainImage(out vec4 fragColor, in vec2 fragCoord)
{
    //vec3 color = vec3(0.0f, 0.0f, 0.0f);
    vec2 p = (2.0 * fragCoord - iScreenInfor.xy) * coef / iScreenInfor.xy;
    float distance = length(p - centerScale);
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