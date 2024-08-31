// 片段着色器，应用Gamma校正
#version 330 core
in vec3 Color;
in vec2 TexCoord;
out vec4 FragColor;
uniform sampler2D mTexture;
uniform bool applyGamma = false;
uniform float gamma = 1.0;

void main() 
{
    //vec3 color = texture(mTexture, TexCoord).rgb;
    //if (applyGamma) 
    //{
    //    color.rgb = pow(color.rgb, vec3(1.0 / 1.0));
    //}
    //FragColor = vec4(color,1.0f);
    
    FragColor = texture(mTexture, TexCoord);
    
}