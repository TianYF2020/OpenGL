#version 330 core

uniform vec3      iScreenInfor;           // viewport resolution (in pixels)
uniform vec4      iMouse;                // mouse pixel coords. xy: current (if MLB down), zw: click
out vec4 mFragColor;
vec2 coef = vec2(iScreenInfor.x / iScreenInfor.y, 1);
void mainImage(out vec4 fragColor, in vec2 fragCoord)
{
    vec3 color = vec3(1.0f, 1.0f, 1.0f);
    vec2 center = vec2(-0, 0)* coef;
    vec2 p = (2.0 * fragCoord - iScreenInfor.xy) * coef / iScreenInfor.xy;
    col = mix(col, vec3(1.0, 0.0, 0.0), 1.0 - smoothstep(0.0, 0.005, length(p - m) - 0.015));

    color = mix(color, vec3(1.0, 0.0, 0.0), 1.0 - step(0.05, abs(length(p -center))));
    fragColor = vec4(color, 1.0);

}

void main()
{
    mainImage(mFragColor, gl_FragCoord.xy);
}