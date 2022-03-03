#version 330 core										
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;
in float visibility;

out vec4 FragColor;	


 struct Material{
	vec3 ambient;
	sampler2D diffuse;
	sampler2D specular;
	sampler2D emission;
 	float shininess;

};


struct LightDirectional{
	 vec3 pos;
	 vec3 color;
	 vec3 dirToLight;
};

struct LightPoint {
	 vec3 pos;
	 vec3 color;
	 vec3 dirToLight;

	 float constant;
	 float linear;
	 float quadratic;
};

struct LightSpot{
	 vec3 pos;
	 vec3 color;
	 vec3 dirToLight;

	float cosPhyInner;
	float cosPhyOutter;
};

//uniform float mixValue;
//uniform sampler2D ourTexture;
//uniform sampler2D ourFace;
//uniform vec4 ourColor;	


uniform vec3 objectColor;
uniform vec3 ambientColor;

uniform vec3 cameraPos;

uniform float emissionLight;
uniform float emissionMove;

uniform Material material;

uniform LightDirectional lightD;

uniform LightSpot lightS;
uniform int FlashOn;
uniform int Hurt;

vec3 calculateLightDirectional(LightDirectional light,vec3 uNormal,vec3 dirToCamera){	
	vec3 result ;
	//diffuse
	float diffIntensity =max( dot(light.dirToLight, uNormal),0);
	vec3 diffuse = diffIntensity * light.color * texture(material.diffuse,TexCoord).rgb;

	//specular 
	vec3 refl = reflect( -light.dirToLight, uNormal);
	float specIntensity =pow( max(dot(refl, dirToCamera),0), material.shininess);
	vec3 specular =specIntensity * light.color * texture(material.diffuse,TexCoord).rgb;

	result = diffuse+specular;
	return result;
}

vec3 calculateLightPoint(LightPoint light,vec3 uNormal,vec3 dirToCamera){
	vec3 result ;
	//attenuation
	float dist = length(light.pos - FragPos);
	float attenuation = 1.0 / (light.constant + light.linear * dist + light.quadratic * (dist* dist));

	//diffuse
	float diffIntensity = max( dot( normalize(light.pos - FragPos), uNormal),0) * attenuation;
	vec3 diffuse = diffIntensity * light.color * texture(material.diffuse,TexCoord).rgb;


	//specular
	vec3 refl = reflect( -normalize(light.pos - FragPos), uNormal);
	float specIntensity =pow( max(dot(refl, dirToCamera),0), material.shininess )* attenuation;
	vec3 specular =specIntensity * light.color * texture(material.specular,TexCoord).rgb;

	result =  diffuse + specular;
	return result;
}

vec3 calculateLightSpot(LightSpot light,vec3 uNormal,vec3 dirToCamera){
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
	float diffIntensity = max(dot(normalize(light.pos - FragPos), uNormal),0) ;
	vec3 diffuse = diffIntensity * light.color * texture(material.diffuse,TexCoord).rgb;

	//specular
	vec3 refl = reflect( -normalize(light.pos - FragPos), uNormal);
	float specIntensity =pow( max(dot(refl, dirToCamera),0), material.shininess);
	vec3 specular =specIntensity * light.color * texture(material.diffuse,TexCoord).rgb;

	result =  (diffuse)*0.25 * soptRatio;
	return result;
}



void main()											
{			
	vec3 fogColor = vec3(0.12f,0.12f,0.12f);
    vec3 finalresult = vec3(0,0,0);
	vec3 uNormal=normalize(Normal);
	vec3 dirToCamera = normalize(cameraPos - FragPos);
	vec4 texColor = texture(material.diffuse,TexCoord);
	 if(texColor.a < 0.1)
        discard;

	 finalresult += calculateLightDirectional(lightD, uNormal, dirToCamera);
	 if(FlashOn == 1)
		finalresult +=  calculateLightSpot(lightS, uNormal, dirToCamera);

	if(Hurt == 1)
		FragColor =vec4(0.8,0.1,0.1,1.0);
	else
		//FragColor = vec4(finalresult,1.0);
		FragColor = vec4(mix(fogColor,finalresult,visibility),1.0);
	//FragColor =vec4(1.0,0.1,0.1,1.0);
	//FragColor = texture(material.diffuse, TexCoord);

}												