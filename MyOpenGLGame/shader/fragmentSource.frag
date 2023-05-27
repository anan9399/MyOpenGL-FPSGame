#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in float height;
in vec3 FragPos;
in vec3 Normal;
in float visibility;


uniform vec3 cameraPos;
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform sampler2D texture3;
uniform sampler2D texture4;
uniform sampler2D blendMap;


uniform int FlashOn;

struct LightDirectional{
	 vec3 pos;
	 vec3 color;
	 vec3 dirToLight;
};

struct LightSpot{
	 vec3 pos;
	 vec3 color;
	 vec3 dirToLight;

	float cosPhyInner;
	float cosPhyOutter;
};

uniform LightSpot lightS;
uniform LightDirectional lightD;

vec3 calculateLightDirectional(LightDirectional light,vec3 uNormal,vec3 dirToCamera,vec3 Texture){	
	vec3 result ;
	//diffuse
	float diffIntensity =max( dot(light.dirToLight, uNormal),0);
	vec3 diffuse = diffIntensity * light.color * Texture;

	//specular 
	vec3 refl = reflect( -light.dirToLight, uNormal);
	float specIntensity =pow( max(dot(refl, dirToCamera),0), 64.0f);
	vec3 specular =specIntensity * light.color * Texture;

	result = diffuse;
	return result;
}

vec3 calculateLightSpot(LightSpot light,vec3 uNormal,vec3 dirToCamera,vec3 Texture){
	vec3 result;
	//spotratio
	float soptRatio;
	float cosTheta = dot(normalize(FragPos-light.pos),- light.dirToLight);
	if(cosTheta > light.cosPhyInner){
		soptRatio = 1.0f;
	}
	else if(cosTheta > light.cosPhyOutter){
		soptRatio = (cosTheta - light.cosPhyOutter) / (light.cosPhyInner - light.cosPhyOutter);
	}
	else{
		soptRatio = 0;
	}
	//diffuse
	float diffIntensity = max( dot( normalize(light.pos - FragPos), uNormal),0) ;
	vec3 diffuse = diffIntensity * light.color * Texture;


	//specular
	vec3 refl = reflect( -normalize(light.pos - FragPos), uNormal);
	float specIntensity =pow( max(dot(refl, dirToCamera),0), 64.0f);
	vec3 specular =specIntensity * light.color * Texture;

	result =  (diffuse + specular) * soptRatio;
	return result;
}

void main()
{    
	vec3 Texture;
	vec3 finalresult=vec3(0.0f);
	vec3 uNormal=Normal;
	vec3 dirToCamera = normalize(cameraPos - FragPos);
	vec3 fogColor = vec3(0.12f,0.12f,0.12f);

	// Normal mapping
	vec2 tiledCoords = TexCoords * 40.0f;
	

	// Multi-texturing
	vec4 blendMapColour = texture(blendMap, TexCoords);
	float backTextureAmount = 1 - (blendMapColour.r + blendMapColour.g + blendMapColour.b);
	vec4 backgroundTextureColour = texture(texture1, tiledCoords) * backTextureAmount; 
	vec4 rTextureColour = texture(texture1, tiledCoords) * blendMapColour.r;
	vec4 gTextureColour = texture(texture3, tiledCoords) * blendMapColour.g;
	vec4 bTextureColour = texture(texture2, tiledCoords) * blendMapColour.b;
	vec4 totalColour = backgroundTextureColour + rTextureColour + gTextureColour + bTextureColour;


	finalresult +=  calculateLightDirectional(lightD,uNormal,dirToCamera,totalColour.rgb);
	if(FlashOn==1)
		finalresult +=  calculateLightSpot(lightS,uNormal,dirToCamera,totalColour.rgb);

	 //FragColor=totalColour;
	//FragColor=vec4(finalresult,1.0f);
	FragColor = vec4(mix(fogColor,finalresult,visibility),1.0);
	// FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
}					 