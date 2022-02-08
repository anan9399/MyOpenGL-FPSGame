#include "Object.h"
#include"stb_image.h"

float vertices[] = {
	// positions             // normals           // texture coords
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
};


float vegetationVertices[] = {
	// positions        // normals         // texture Coords (swapped y coordinates because texture is flipped upside down)
	0.0f,  0.5f,  0.0f, 0.0f, 1.0f, 0.0f,  0.0f,  0.0f,
	0.0f, -0.5f,  0.0f, 0.0f, 1.0f, 0.0f,  0.0f,  1.0f,
	1.0f, -0.5f,  0.0f, 0.0f, 1.0f, 0.0f,  1.0f,  1.0f,

	0.0f,  0.5f,  0.0f, 0.0f, 1.0f, 0.0f,  0.0f,  0.0f,
	1.0f, -0.5f,  0.0f, 0.0f, 1.0f, 0.0f,  1.0f,  1.0f,
	1.0f,  0.5f,  0.0f, 0.0f, 1.0f, 0.0f,  1.0f,  0.0f


	//// positions            // normals         // texcoords
	//0.0f,  0.5f,  0.0f, 0.0f, 1.0f, 0.0f,  0.0f,  0.0f,
	//0.0f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   0.0f,  25.0f,
	//25.0f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  25.0f, 25.0f,
	//				
	// 0.0f, 0.5f,  0.0f, 0.0f, 1.0f, 0.0f,  0.0f,  0.0f,
 //    25.0f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  25.0f, 25.0f,
	// 25.0f, 0.5f,  0.0f, 0.0f, 1.0f, 0.0f,  25.0f, 0.0f,
};


float waterVertices[] = {
	// positions         // normals        // texture Coords (note we set these higher than 1 (together with GL_REPEAT as texture wrapping mode). this will cause the floor texture to repeat)
	 60.0f, -0.5f,  60.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
	-60.0f, -0.5f,  60.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
	-60.0f, -0.5f, -60.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
	 				 
	 60.0f, -0.5f,  60.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
	-60.0f, -0.5f, -60.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
	 60.0f, -0.5f, -60.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f
};

float ScreenVertices[] = {
	// positions   // texCoords
	-0.045f,  0.05f,  0.0f, 1.0f,
	-0.045f, -0.05f,  0.0f, 0.0f,
	 0.045f, -0.05f,  1.0f, 0.0f,

	-0.045f,  0.05f,  0.0f, 1.0f,
	 0.045f, -0.05f,  1.0f, 0.0f,
	 0.045f,  0.05f,  1.0f, 1.0f
};

glm::mat4 modelMat;
glm::mat4 viewMat;
glm::mat4 projectionMat;




void Object::InitObject()
{

#pragma region BOX
	m_shader = new Shader("Lightvert.vert", "Lightfrag.frag");
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	//glEnableVertexAttribArray(1);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(3);

	diffuse = Texture::GetInstance().loadTextureBySlot("container2.png", GL_RGBA, GL_RGBA, 0);


	specular = Texture::GetInstance().loadTextureBySlot("container2_specular.png", GL_RGBA, GL_RGBA, 1);
	//std::cout << specular << std::endl;

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glDisable(GL_TEXTURE_2D);
#pragma endregion


#pragma region WATER
	water_shader = new Shader("WaterVert.vert", "WaterFrag.frag");
	glGenVertexArrays(1, &WaterVAO);
	glBindVertexArray(WaterVAO);
	glGenBuffers(1, &WaterVBO);
	glBindBuffer(GL_ARRAY_BUFFER, WaterVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(waterVertices), &waterVertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	//glEnableVertexAttribArray(1);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(3);

	waterTex = Texture::GetInstance().loadTextureBySlot("water.png", GL_RGBA, GL_RGBA, 0);



#pragma endregion

	ScreenShader = new Shader("ScreenVert.vert", "ScreenFrag.frag");
	glGenVertexArrays(1, &ScreenVAO);
	glBindVertexArray(ScreenVAO);
	glGenBuffers(1, &ScreenVBO);
	glBindBuffer(GL_ARRAY_BUFFER, ScreenVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(ScreenVertices), &ScreenVertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

	AimTex = Texture::GetInstance().loadTextureBySlot("crossHair.png", GL_RGBA, GL_RGBA, 0);
	
}

//void Object::InitTree(std::vector<glm::vec3> Vertices)
//{
//	for (int i = 0; i < 100; i++) {
//		for (int j = 0; j < 100; j++)
//		{
//			int n = rand() % 4;
//			int x = i * SIZE;
//			int z = j * SIZE;
//			if (Vertices[j * VERTEX_COUNT + i][1] < 0)
//				continue;
//			trees.push_back(Tree(x, 0, z, 3, Game::GetTerrainHeight(x, z) + 3));
//		}
//	}
//}

void Object::InitGrass(std::vector<glm::vec3> GrassPos)
{
#pragma region GRASS
	//Set grass model matrix
	for (int i = 0; i < GrassPos.size(); i++)
	{
		glm::mat4 model = glm::mat4(1.0f);

		if (GrassPos[i].y > 1)
			model = glm::translate(model, glm::vec3(GrassPos[i].x, GrassPos[i].y + 1 / GrassPos[i].y, GrassPos[i].z));
		else
			model = glm::translate(model, glm::vec3(GrassPos[i].x, GrassPos[i].y, GrassPos[i].z));
		model = glm::scale(model, glm::vec3(2.5f));
	/*	float ra = 0.0f;
		if (i > GrassPos.size() / 4)
			ra = 45.0f;
		else if (i > GrassPos.size() / 2)
			ra = 90.0f;
		else if (i > GrassPos.size() * 3 / 4)
			ra = 135.0f;
		model = glm::rotate(model, glm::radians(ra), glm::vec3(0.0f, 1.0, 0.0));*/

		float rotAngle = (rand() % 360);
		model = glm::rotate(model, rotAngle, glm::vec3(0.0f, 1.0f, 0.0f));

		GrassModel.push_back(model);
	}

	plant_shader = new Shader("Plantvertex.vert", "Plantfragment.frag");
	glGenVertexArrays(1, &PlantVAO);
	glBindVertexArray(PlantVAO);
	glGenBuffers(1, &PlantVBO);
	glBindBuffer(GL_ARRAY_BUFFER, PlantVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vegetationVertices), &vegetationVertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	//glEnableVertexAttribArray(1);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);


	glGenBuffers(1, &PlantInsVBO);
	glBindBuffer(GL_ARRAY_BUFFER, PlantInsVBO);
	glBufferData(GL_ARRAY_BUFFER, GrassModel.size() * sizeof(glm::mat4), &GrassModel[0], GL_STATIC_DRAW);

	GLsizei vec4Size = sizeof(glm::vec4);
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)0);
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(vec4Size));
	glEnableVertexAttribArray(5);
	glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(2 * vec4Size));
	glEnableVertexAttribArray(6);
	glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(3 * vec4Size));

	glVertexAttribDivisor(3, 1);
	glVertexAttribDivisor(4, 1);
	glVertexAttribDivisor(5, 1);
	glVertexAttribDivisor(6, 1);

	glBindVertexArray(0);

	plantTex = Texture::GetInstance().loadTextureBySlot("grass.png", GL_RGBA, GL_RGBA, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	
#pragma endregion
}

void Object::Drawcube(Camera& camera, LightDirectional* lightD, LightSpot* lightS, int FlashOn)
{
	glBindVertexArray(VAO);
	
	m_shader->use();
	modelMat = glm::mat4(1.0f);
	
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 invViewMat = glm::inverse(camera.GetViewMatrix());
	glm::vec3 transpot = glm::vec3(0.15f, -0.15f, -0.5f);

	//model = invViewMat * translation * rotation * scaleMat;
	model = invViewMat;
	model = glm::translate(model, transpot);
	model = glm::rotate(model, glm::radians(45.0f), glm::vec3(1.0f, 1.0f, 0.0f));
	model = glm::scale(model,glm::vec3(0.15f));
	
	viewMat = camera.GetViewMatrix();
	projectionMat = glm::perspective(glm::radians(camera.Zoom), 800.0f / 600.0f, 0.01f, 250.0f);
	modelMat = glm::translate(modelMat,glm::vec3(350.0f,12.0f,350.0));
	modelMat = glm::scale(modelMat, glm::vec3(2.0f, 2.0f, 2.0f));

	m_shader->setUniform4m("model", model);
	m_shader->setUniform4m("view", viewMat);
	m_shader->setUniform4m("projection", projectionMat);

	m_shader->setUniform1i("FlashOn", FlashOn);

	m_shader->setUniform3f("objectColor",glm::vec3( 1.0f, 1.0f, 1.0f));
	m_shader->setUniform3f("ambientColor", glm::vec3(10.0f, 10.0f, 10.0f));
	m_shader->setUniform3f("cameraPos", camera.Position);


	m_shader->setUniform3f("lightD.pos", lightD->Position);
	m_shader->setUniform3f("lightD.color", lightD->Color);
	m_shader->setUniform3f("lightD.dirToLight", lightD->Direction);


	m_shader->setUniform3f("lightS.pos", camera.Position);
	m_shader->setUniform3f("lightS.color", lightS->Color);
	m_shader->setUniform3f("lightS.dirToLight", lightS->Direction);
	m_shader->setUniform1f("lightS.cosPhyInner", lightS->cosPhyInner);
	m_shader->setUniform1f("lightS.cosPhyOutter", lightS->cosPhyOutter);

	m_shader->setUniform3f("material.ambient", glm::vec3(1.0f, 1.0f, 1.0f));
	m_shader->setUniform1i("material.diffuse", 0);
	//m_shader->setUniform4f("plane", clip);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, diffuse);
	m_shader->setUniform1i("material.specular", 1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, specular);
	m_shader->setUniform1f("material.shininess", 64.0f);

	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);	
	m_shader->stop();
}

void Object::DrawPlant(Camera& camera, LightDirectional* lightD, LightSpot* lightS, int FlashOn, std::vector<glm::vec3>plantPos)
{

	glBindVertexArray(PlantVAO);
	plant_shader->use();
	modelMat = glm::mat4(1.0f);
	viewMat = camera.GetViewMatrix();
	projectionMat = glm::perspective(glm::radians(camera.Zoom), 800.0f / 600.0f, 0.1f, 290.0f);
	
	plant_shader->setUniform4m("view", viewMat);
	plant_shader->setUniform4m("projection", projectionMat);


	plant_shader->setUniform3f("lightD.pos", lightD->Position);
	plant_shader->setUniform3f("lightD.color", lightD->Color);
	plant_shader->setUniform3f("lightD.dirToLight", lightD->Direction);

	plant_shader->setUniform3f("cameraPos",camera.Position);
	plant_shader->setUniform1i("FlashOn", FlashOn);

	plant_shader->setUniform3f("lightS.pos", camera.Position);
	plant_shader->setUniform3f("lightS.color", lightS->Color);
	plant_shader->setUniform3f("lightS.dirToLight", lightS->Direction);
	plant_shader->setUniform1f("lightS.cosPhyInner", lightS->cosPhyInner);
	plant_shader->setUniform1f("lightS.cosPhyOutter", lightS->cosPhyOutter);

	//plant_shader->setUniform4f("plane", clip);

	plant_shader->setUniform1i("texture1",0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, plantTex);
	
	glDrawArraysInstanced(GL_TRIANGLES,0,6,2000);
	glBindVertexArray(0);
	plant_shader->stop();
	//for (int i = 0; i < plantPos.size(); i++) {
	//	plant_shader->setUniform4m("model", GrassModel[i]);
	//	glDrawArrays(GL_TRIANGLES, 0, 6);
	//}
}

void Object::DrawWater(Camera& camera, LightDirectional* lightD, LightSpot* lightS, int FlashOn,int reflect)
{
	glBindVertexArray(WaterVAO);

	water_shader->use();
	modelMat = glm::mat4(1.0f);
	viewMat = camera.GetViewMatrix();
	projectionMat = glm::perspective(glm::radians(camera.Zoom), 800.0f / 600.0f, 0.1f, 250.0f);
	modelMat = glm::translate(modelMat, glm::vec3(233.448f, 1.5f , 472.987f));
	water_shader->setUniform4m("model", modelMat);
	water_shader->setUniform4m("view", viewMat);
	water_shader->setUniform4m("projection", projectionMat);

	water_shader->setUniform1i("FlashOn", FlashOn);

	water_shader->setUniform3f("objectColor", glm::vec3(1.0f, 1.0f, 1.0f));
	water_shader->setUniform3f("ambientColor", glm::vec3(1.0f, 1.0f, 1.0f));
	water_shader->setUniform3f("cameraPos", camera.Position);

	water_shader->setUniform3f("lightD.pos", lightD->Position);
	water_shader->setUniform3f("lightD.color", lightD->Color);
	water_shader->setUniform3f("lightD.dirToLight", lightD->Direction);

	water_shader->setUniform3f("lightS.pos", camera.Position);
	water_shader->setUniform3f("lightS.color", lightS->Color);
	water_shader->setUniform3f("lightS.dirToLight", lightS->Direction);
	water_shader->setUniform1f("lightS.cosPhyInner", lightS->cosPhyInner);
	water_shader->setUniform1f("lightS.cosPhyOutter", lightS->cosPhyOutter);

	water_shader->setUniform3f("material.ambient", glm::vec3(1.0f, 1.0f, 1.0f));
	water_shader->setUniform1i("material.diffuse", 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, waterTex);
	water_shader->setUniform1i("material.specular", 1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, waterTex);
	water_shader->setUniform1f("material.shininess", 64.0f);


	water_shader->setUniform1i("reflectiontexture", 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, reflect);
	water_shader->setUniform1i("refractiontexture", 1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, reflect);

	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
	water_shader->stop();
}

void Object::DrawCrosshair()
{
	ScreenShader->use();
	glBindVertexArray(ScreenVAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, AimTex);
	ScreenShader->setUniform1i("screenTexture", 0);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	ScreenShader->stop();
}

