#version 330 core

uniform vec3      iScreenInfor;           // viewport resolution (in pixels)
uniform vec4      iMouse;                // mouse pixel coords. xy: current (if MLB down), zw: click
out vec4 mFragColor;
//�����ó��ⲿ����
int hSize =5;                                      //�ж��ٸ������ⲿ������
int vSize = 5;                                      //�ж��ٸ������ⲿ������
float radius = 50;                                  //Բ�����أ����ⲿ������
float fontSize = 5;                                 //����߿��С
vec3 circleColor = vec3(1.0, 0.0, 0.0);             //����Բ�����ɫ
vec3 circleBorderColor = vec3(0.0, 0.0, 0.0);       //����Բ�߿����ɫ

//�������
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