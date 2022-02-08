#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;
layout (location = 2) in vec3 aNormal;

out vec2 TexCoords;
out float height;
out vec3 FragPos;
out vec3 Normal;
out float visibility;

const float density = 0.007;
const float gradient = 1.5;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec4 plane;

void main()
{
    TexCoords = aTexCoords;    
    height = aPos.y;

    vec4 worldPosition =  model * vec4(aPos, 1.0);
    FragPos = vec3(model * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(model))) * aNormal;	
    gl_Position = projection * view * worldPosition;

    gl_ClipDistance[0]=dot(worldPosition,plane);

    vec4 positionToCam = view * worldPosition;
    float dist = length(positionToCam.xyz);
    visibility = exp(-pow((dist * density),gradient));
    visibility = clamp(visibility,0.0,1.0);
}