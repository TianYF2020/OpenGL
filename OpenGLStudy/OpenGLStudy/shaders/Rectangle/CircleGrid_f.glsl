#version 330 core

uniform vec3      iScreenInfor;           // viewport resolution (in pixels)
uniform vec4      iMouse;                // mouse pixel coords. xy: current (if MLB down), zw: click
out vec4 mFragColor;
//�����ó��ⲿ����
int hSize = 5;                                      //�ж��ٸ������ⲿ������
int vSize = 5;                                      //�ж��ٸ������ⲿ������
float radius = 0.1;                                 //Բ�İ뾶�����ⲿ������
float fontSize = 5;                                 //����߿��С
vec3 circleColor = vec3(1.0, 0.0, 0.0);             //����Բ�����ɫ
vec3 circleBorderColor = vec3(0.0, 0.0, 0.0);       //����Բ�߿����ɫ

//�������
vec2 coef = vec2(1.0, iScreenInfor.y / iScreenInfor.x); //�����������ŵ�                  
float fontSizeScale = fontSize / iScreenInfor.x;                    //����߿��С
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