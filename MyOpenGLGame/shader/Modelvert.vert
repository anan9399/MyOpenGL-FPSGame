#version 330 core		
layout (location = 0) in vec3 aPos;					
//layout (location = 1) in vec3 aColor;		
layout (location = 1) in vec2 aTexCoord;	
layout (location = 2) in vec3 aNormal;

//out vec4 vertexColor;			
out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPos;
out float visibility;

const float density = 0.007;
const float gradient = 1.5;

//uniform mat4 transform;
uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projectMat;

uniform vec4 plane;

//uniform vec3 offset[10];

void main()											
{							
	//modelMat=offset[gl_instanceID];
	vec4 worldPosition =  modelMat * vec4(aPos, 1.0);
    gl_Position =  projectMat * viewMat * worldPosition;	
	//gl_ClipDistance[0]=dot(worldPosition,plane);

	FragPos = (modelMat * vec4(aPos.xyz, 1.0f)).xyz;
	Normal=mat3(transpose(inverse(modelMat))) * aNormal;
	//vertexColor = vec4(aColor.x, aColor.y, aColor.z, 1.0);		
	TexCoord=aTexCoord;
	
	vec4 positionToCam = viewMat * worldPosition;
    float dist = length(positionToCam.xyz);
    visibility = exp(-pow((dist * density),gradient));
    visibility = clamp(visibility,0.0,1.0);
}