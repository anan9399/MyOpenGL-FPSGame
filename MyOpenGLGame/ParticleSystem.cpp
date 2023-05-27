#include "ParticleSystem.h"

float pVertices[] = { 
	-0.5f , 0.5f, 0.0f , 1.0f ,0.0f,     //0         
	-0.5f ,-0.5f, 0.0f , 0.0f ,0.0f,	 //1
	 0.5f ,-0.5f, 0.0f , 0.0f ,1.0f,	 //2
	 0.5f , 0.5f, 0.0f , 1.0f ,1.0f,	 //3
};

int pInidices[] = {
	0,1,2,
	2,3,0
};


ParticleSystem::ParticleSystem()
{
}

void ParticleSystem::init(int numOfParticles)
{
	for (int i = 0; i < numOfParticles; i++)
	{
		positions.push_back(glm::vec3(0.0f, 0.0f, 0.0f));
		Particle oneParticle;
		particles.push_back(oneParticle);
	}
	PaticleShader = new Shader("ParticleVert.vert", "ParticleFrag.frag");

	glGenVertexArrays(1, &P_VAO);
	glBindVertexArray(P_VAO);
	glGenBuffers(1, &P_VBO);
	glGenBuffers(1, &P_EBO);
	glBindBuffer(GL_ARRAY_BUFFER, P_VBO);

	glBindBuffer(GL_ARRAY_BUFFER, P_VBO);
	glBufferData(GL_ARRAY_BUFFER,sizeof(pVertices), &pVertices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, P_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(int), &pInidices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	P_texture = Texture::GetInstance().loadTextureBySlot("texture/RedOrb.png", GL_RGBA, GL_RGBA, 0);
}

void ParticleSystem::update(float dt)
{
	
}

void ParticleSystem::aging(float dt)
{
	for (auto it = particles.begin(); it != particles.end(); it++) {
		it->age += dt;
		if (it->age > it->life) {
			it->Position = it->origin;
			it->Velocity = glm::vec3(RandomNum::GetInstance().GetRandomNumber1f(-1.0, 1.0), RandomNum::GetInstance().GetRandomNumber1f(0.0, 5.0), RandomNum::GetInstance().GetRandomNumber1f(-1.0, 1.0));
			it->age = 0.0f;
		}
	}
}

void ParticleSystem::kinematics(float dt)
{
	for (auto it = particles.begin(); it != particles.end(); it++) {
		it->Position += it->Velocity*dt;
	}
}

void ParticleSystem::prepare()
{
	glEnable(GL_BLEND);
	
}

void ParticleSystem::draw(Camera &camera,float dt,glm::vec3 startPos)
{
	
	PaticleShader->use();
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = camera.GetViewMatrix();
	glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), 800.0f / 600.0f, 0.1f, 250.0f);
	glDepthMask(false);
	for (auto it = particles.begin(); it != particles.end(); it++) {
		if (it->Update(dt)) {
			it->SetOrigin(startPos);

			model = glm::mat4(1.0f);
			model = glm::translate(model,glm::vec3( it->Position.x, it->Position.y+0.8f, it->Position.z));
			//keep the view matrix no rotation
			model[0][0] = view[0][0];
			model[0][1] = view[1][0];
			model[0][2] = view[2][0];
			model[1][0] = view[0][1];
			model[1][1] = view[1][1];
			model[1][2] = view[2][1];
			model[2][0] = view[0][2];
			model[2][1] = view[1][2];
			model[2][2] = view[2][2];
			model = glm::scale(model, glm::vec3(0.3f));
			PaticleShader->setUniform4m("model", model);

			PaticleShader->setUniform4m("view", view);
			PaticleShader->setUniform4m("projection", projection);

			glBindVertexArray(P_VAO);
			PaticleShader->setUniform1i("texture01", 0);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, P_texture);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
		

		}
	}
	PaticleShader->stop();
	glDepthMask(true);
}


