#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
class WaterFrameBuffer
{
public:
	 WaterFrameBuffer();
	 int getReflectionTexture();
	 int getRefractionTexture();
	 void BindReflectionFrameBuffer();
	 void BindRefractionFrameBuffer();
	 void UnbindCurrentFrameBuffer();
	 void cleanUp();

	 void InitializeReflectionFrameBuffer();
	 void InitializeRefractionFrameBuffer();

	 unsigned int reflectionFrameBuffer;
	 unsigned int reflectionTexture;
	 unsigned int reflectionDepthBuffer;


	 unsigned int refractionFrameBuffer;
	 unsigned int refractionTexture;
	 unsigned int refractionDepthTexture;
	 unsigned int refractionDepthBuffer;
private:

	const int REFLECTION_WIDTH = 1600;
	const int REFLECTION_HEIGHT = 1200;
	const int REFRACTION_WIDTH = 1280;
	const int REFRACTION_HEIGHT = 720;

	const int Screen_Width = 1600;
	const int Screen_Height = 1200;




	void BindFrameBuffer(int frameBuffer, int width, int height);
	
	
	unsigned int CreateFrameBuffer();
	unsigned int CreateTextureAttachment(int width,int height);
	unsigned int CreateDepthTextureAttachment(int width, int height);
	unsigned int CreateDepthBufferAttachment(int width, int height);
};

