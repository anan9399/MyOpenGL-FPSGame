#version 330 core
in vec2 TexCoord;
out vec4 FragColor;

uniform sampler2D texture01;

void main()
  {

      FragColor =texture(texture01,TexCoord);
    // FragColor =vec4(1.0f, 0.5f, 0.2f, 1.0f);
  }