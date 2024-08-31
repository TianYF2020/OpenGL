#version 330 core

uniform vec3      iScreenInfor;           // viewport resolution (in pixels)
uniform vec4      iMouse;                // mouse pixel coords. xy: current (if MLB down), zw: click
uniform float radius;
uniform vec3 fillcolor;
uniform uint hSize;
uniform uint hSize;
out vec4 mFragColor;
float sdCircle(in vec2 p, in float r)
{
    return length(p) - r;
}


void mainImage(out vec4 fragColor, in vec2 fragCoord)
{

    vec3 color;
    vec2 size = iScreenInfor.xy;
    vec2 coeff = size /iScreenInfor.y;
    //vec2 p = (2.0 * fragCoord - iScreenInfor.xy) / iScreenInfor.y;
    ////vec2 m = (2.0 * iMouse.xy - iScreenInfor.xy) / iScreenInfor.y;
    //vec2 m = (2.0 * vec2(400,400) - iScreenInfor.xy) / iScreenInfor.y;
    //float d = sdCircle(p, 0.2);





    ////// coloring
    ////vec3 color = (d > 0.0) ? vec3(0.9, 0.6, 0.3) : vec3(0.65, 0.85, 1.0);
    ////color *= 1.0 - exp(-6.0 * abs(d));
    ////color *= 0.8 + 0.2 * cos(150.0 * d);
    ////color = mix(color, vec3(1.0), 1.0 - smoothstep(0.0, 0.01, abs(d)));

    ////if (iMouse.z > 0.001)
    ////{
    ////    d = sdCircle(m, 0.5);
    ////    color = mix(color, vec3(1.0, 1.0, 0.0), 1.0 - smoothstep(0.0, 0.005, abs(length(p - m) - abs(d)) - 0.0025));
    ////    color = mix(color, vec3(1.0, 0.0, 0.0), 1.0 - smoothstep(0.0, 0.005, length(p - m) - 0.015));
    ////}
   

    ////color = mix(color, vec3(1.0,0.0,0.0), 1.0 - smoothstep(0, 0.2, abs(d)));
    //color = mix(color, vec3(1.0,0.0,0.0), 1.0 - step(0.8, abs(length(p))));
    ////d = sdCircle(m, 0.5);
    ////color = mix(color, vec3(1.0, 1.0, 0.0), 1.0 - smoothstep(0.0, 0.005, abs(length(p - m) - abs(d)) - 0.0025));
    ////color = mix(color, vec3(1.0, 0.0, 0.0), 1.0 - smoothstep(0.0, 0.05, length(p - m) - 0.15));

    vec2 p = fragCoord * 2 / size * coeff;


    //vec2   vec2 secreenSize p = fragCoord * 2 / vec2(iScreenInfor.x, iScreenInfor.y);
    vec2 pInt = floor(p / 0.4) * 0.4 +0.2;

    color = mix(color, vec3(1.0, 0.0, 0.0), 1.0 - step(0.05, abs(length(p - pInt))));
    fragColor = vec4(color, 1.0);

}

void main()
{
    mainImage(mFragColor, gl_FragCoord.xy);
}