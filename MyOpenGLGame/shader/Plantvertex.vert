#version 330 core
layout (location = 0) in vec3 aPos;					
//layout (location = 1) in vec3 aColor;		
layout (location = 1) in vec2 aTexCoord;	
layout (location = 2) in vec3 aNormal;

layout (location = 3) in mat4 instanceMatrix;

out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPos;
out float visibility;

const float density = 0.007;
const float gradient = 1.5;


uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec4 plane;

void main()
{
  // gl_ClipDistance[0]=-1;
  	vec4 worldPosition =  instanceMatrix * vec4(aPos, 1.0);

	 //gl_ClipDistance[0]=dot(worldPosition,plane);

    FragPos = vec3(instanceMatrix * vec4(aPos, 1.0));
     Normal = mat3(transpose(inverse(instanceMatrix/2))) * aNormal;	
    TexCoord = aTexCoord;    
    gl_Position = projection * view * worldPosition;

    	
	vec4 positionToCam = view * worldPosition;
    float dist = length(positionToCam.xyz);
    visibility = exp(-pow((dist * density),gradient));
    visibility = clamp(visibility,0.0,1.0);
}