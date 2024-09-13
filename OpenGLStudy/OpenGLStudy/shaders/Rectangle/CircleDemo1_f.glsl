#version 330 core

uniform vec3      iScreenInfor;           // viewport resolution (in pixels)
uniform vec4      iMouse;                // mouse pixel coords. xy: current (if MLB down), zw: click

out vec4 mFragColor;
float sdCircle(in vec2 p, in float r)
{
    return length(p) - r;
}


void mainImage(out vec4 fragColor, in vec2 fragCoord)
{
    vec2 p = (2.0 * fragCoord - iScreenInfor.xy) / iScreenInfor.y;
    vec2 m = (2.0 * iMouse.xy - iScreenInfor.xy) / iScreenInfor.y;

    float d = sdCircle(p, 0.5);

    // coloring
    vec3 col = (d > 0.0) ? vec3(0.9, 0.6, 0.3) : vec3(0.65, 0.85, 1.0);
    col *= 1.0 - exp(-6.0 * abs(d));
    col *= 0.8 + 0.2 * cos(150.0 * d);
    col = mix(col, vec3(1.0), 1.0 - smoothstep(0.0, 0.01, abs(d)));

    if (iMouse.z > 0.001)
    {
        d = sdCircle(m, 0.5);
        col = mix(col, vec3(1.0, 1.0, 0.0), 1.0 - smoothstep(0.0, 0.005, abs(length(p - m) - abs(d)) - 0.0025));
        col = mix(col, vec3(1.0, 1.0, 0.0), 1.0 - smoothstep(0.0, 0.005, length(p - m) - 0.015));
    }

    fragColor = vec4(col, 1.0);
}
void main()
{
    mainImage(gl_FragColor, gl_FragCoord.xy);
}