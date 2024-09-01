#version 330 core

uniform vec3      iScreenInfor;           // viewport resolution (in pixels)
uniform vec4      iMouse;                // mouse pixel coords. xy: current (if MLB down), zw: click
out vec4 mFragColor;

//���ⲿ����
float radius = 0.1;                                 //Բ�İ뾶
vec2  center = vec2(0, 0);                          //����Բ������
vec3  circleColor = vec3(1.0, 0.0, 0.0);            //����Բ�����ɫ
vec3  circleBorderColor = vec3(0.0, 0.0, 0.0);      //����Բ�߿����ɫ
float fontSize = 5;

vec2 coef = vec2(1.0, iScreenInfor.y/iScreenInfor.x); //�������ű���
vec2 centerScale = center * coef;                   //���ձ������ŵ�Բ������               
float fontSizeScale = fontSize / iScreenInfor.x;    //����߿��С

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