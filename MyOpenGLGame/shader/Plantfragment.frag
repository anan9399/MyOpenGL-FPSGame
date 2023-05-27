#version 330 core
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;
in float visibility;

out vec4 FragColor;	

uniform sampler2D texture1;
uniform vec3 cameraPos;

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
	vec3 diffuse = diffIntensity * light.color * texture(texture1,TexCoord).rgb;


	//specular
	vec3 refl = reflect( -normalize(light.pos - FragPos), uNormal);
	float specIntensity =pow( max(dot(refl, dirToCamera),0), 64.0f );
	vec3 specular =specIntensity * light.color * texture(texture1,TexCoord).rgb;

	result =  (diffuse + specular) * soptRatio;
	return result;
}


void main()
{    
	vec3 fogColor = vec3(0.12f,0.12f,0.12f);
	vec3 Texture;
	vec3 finalresult=vec3(0.0f);
	vec3 uNormal=Normal;
	vec3 dirToCamera = normalize(cameraPos - FragPos);

    vec4 texColor = texture(texture1,TexCoord);
    if(texColor.a < 0.01)
        discard;
	finalresult +=  calculateLightDirectional(lightD,uNormal,dirToCamera,texColor.rgb);
	if(FlashOn == 1)
		finalresult +=  calculateLightSpot(lightS,uNormal,dirToCamera,texColor.rgb);
    //FragColor = vec4(finalresult,1.0f);

	FragColor = vec4(mix(fogColor,finalresult,visibility),1.0);
	//FragColor = vec4(finalresult,1.0f);
	//vec4(1.0f, 0.5f, 0.2f, 1.0f);
}