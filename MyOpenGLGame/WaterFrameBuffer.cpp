#include "WaterFrameBuffer.h"

WaterFrameBuffer::WaterFrameBuffer()
{
    //call when loading the game
    InitializeReflectionFrameBuffer();
    InitializeRefractionFrameBuffer();
}

int WaterFrameBuffer::getReflectionTexture()
{
    return reflectionTexture;
}

int WaterFrameBuffer::getRefractionTexture()
{
    return refractionTexture;
}

void WaterFrameBuffer::BindReflectionFrameBuffer()
{
    glBindFramebuffer(GL_FRAMEBUFFER, reflectionFrameBuffer);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
    glEnable(GL_DEPTH_TEST);
    //BindFrameBuffer(reflectionFrameBuffer, REFLECTION_WIDTH, REFLECTION_HEIGHT);
}

void WaterFrameBuffer::BindRefractionFrameBuffer()
{
    glBindFramebuffer(GL_FRAMEBUFFER, refractionFrameBuffer);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
    glEnable(GL_DEPTH_TEST);
}

void WaterFrameBuffer::InitializeReflectionFrameBuffer()
{
   /* reflectionFrameBuffer = CreateFrameBuffer();
    reflectionTexture = CreateTextureAttachment(REFLECTION_WIDTH, REFLECTION_HEIGHT);
    reflectionDepthBuffer = CreateDepthBufferAttachment(REFLECTION_WIDTH, REFLECTION_HEIGHT);
    UnbindCurrentFrameBuffer();*/

    glGenFramebuffers(1, &reflectionFrameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, reflectionFrameBuffer);
    glDrawBuffer(GL_COLOR_ATTACHMENT0);

    glGenTextures(1, &reflectionTexture);
    glBindTexture(GL_TEXTURE_2D, reflectionTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, REFLECTION_WIDTH, REFLECTION_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, reflectionTexture, 0);

    glGenRenderbuffers(1, &reflectionDepthBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, reflectionDepthBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, REFLECTION_WIDTH, REFLECTION_HEIGHT);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, reflectionDepthBuffer);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);


}

void WaterFrameBuffer::InitializeRefractionFrameBuffer()
{
   /* refractionFrameBuffer = CreateFrameBuffer();
    refractionTexture = CreateTextureAttachment(REFRACTION_WIDTH, REFRACTION_HEIGHT);
    refractionDepthTexture = CreateDepthTextureAttachment(REFRACTION_WIDTH, REFRACTION_HEIGHT);
    UnbindCurrentFrameBuffer();*/


    glGenFramebuffers(1, &refractionFrameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, refractionFrameBuffer);
    glDrawBuffer(GL_COLOR_ATTACHMENT0);

    glGenTextures(1, &refractionTexture);
    glBindTexture(GL_TEXTURE_2D, refractionTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, REFLECTION_WIDTH, REFLECTION_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, refractionTexture, 0);

    glGenTextures(1, &refractionDepthTexture);
    glBindTexture(GL_TEXTURE_2D, refractionDepthTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, REFLECTION_WIDTH, REFLECTION_HEIGHT,  0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glFramebufferTexture(GL_FRAMEBUFFER,GL_DEPTH_ATTACHMENT, refractionDepthTexture, 0);

  

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void WaterFrameBuffer::UnbindCurrentFrameBuffer()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glViewport(0, 0, Screen_Width, Screen_Height);
    glDisable(GL_DEPTH_TEST);
}

void WaterFrameBuffer::cleanUp()
{
    glDeleteFramebuffers(1,&reflectionFrameBuffer);
    glDeleteTextures(1, &reflectionTexture);
    glDeleteRenderbuffers(1, &reflectionDepthBuffer);
    glDeleteFramebuffers(1, &refractionFrameBuffer);
    glDeleteTextures(1,&refractionTexture);
    glDeleteTextures(1,&refractionDepthTexture);  
}

void WaterFrameBuffer::BindFrameBuffer(int frameBuffer, int width, int height)
{
  glBindTexture(GL_TEXTURE_2D, 0);
  glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
  glViewport(0, 0, width, height);
}

unsigned int WaterFrameBuffer::CreateFrameBuffer()
{
    unsigned int framebuffer;
    glGenFramebuffers(1, &framebuffer);
    glDrawBuffer(GL_COLOR_ATTACHMENT0);
    return framebuffer;
}

unsigned int WaterFrameBuffer::CreateTextureAttachment(int width, int height)
{
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,texture,0);

    return texture;
}

unsigned int WaterFrameBuffer::CreateDepthTextureAttachment(int width, int height)
{
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, width, height, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, texture, 0);

    return texture;
}

unsigned int WaterFrameBuffer::CreateDepthBufferAttachment(int width, int height)
{
    unsigned int depthBuffer;
    glGenRenderbuffers(1,&depthBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER,GL_DEPTH_ATTACHMENT,GL_RENDERBUFFER, depthBuffer);
    return depthBuffer;
}
