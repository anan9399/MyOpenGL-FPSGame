#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D screenTexture;
uniform float lowhp;

void main()
{ 

    FragColor = texture(screenTexture, TexCoords);
   // float average = 0.2126 * FragColor.r + 0.7152 * FragColor.g + 0.0722 * FragColor.b;
    //FragColor = vec4(average, average, average, 1.0);
   // FragColor = vec4(1.0f,0.0f,1.0f,1.0f);
}