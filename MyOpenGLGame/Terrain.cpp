#include "Terrain.h"


std::vector<glm::vec3> Vertices;
std::vector<glm::vec2> Textures;
std::vector<glm::vec3> Normals;
std::vector<int> index;

int Terrain::readNum(int* cursor, char str[VERTEX_COUNT * 3 + 10])
{
	char c[4];
	for (int i = 0; i < 3; i++)
	{
		c[i] = str[(*cursor)++];
	}
	c[3] = '\0';
	return atoi(c);
}

float Terrain::GetTerrainHeight(float x, float z)
{
	float CameraX = x / SIZE;
	float CameraZ = z / SIZE;
	int Col0 = int(CameraX);
	int Row0 = int(CameraZ);
	int Col1 = Col0 + 1;
	int Row1 = Row0 + 1;
	if (Col1 > VERTEX_COUNT)	Col1 = 0;
	if (Row1 > VERTEX_COUNT)	Row1 = 0;
	float h00 = Vertices[Col0 + Row0 * VERTEX_COUNT].y;
	float h01 = Vertices[Col1 + Row0 * VERTEX_COUNT].y;
	float h11 = Vertices[Col1 + Row1 * VERTEX_COUNT].y;
	float h10 = Vertices[Col0 + Row1 * VERTEX_COUNT].y;
	float tx = CameraX - int(CameraX);
	float ty = CameraZ - int(CameraZ);
	float txty = tx * ty;
	return h00 * (1.0f - ty - tx + txty)
		+ h01 * (tx - txty)
		+ h11 * txty
		+ h10 * (ty - txty);
}


void Terrain::Init()
{
	
	int count = VERTEX_COUNT * VERTEX_COUNT;

	//std::ofstream OutFile("Test123.txt");

	std::ifstream readFile("Test.txt");
	char head[VERTEX_COUNT + 10];

	char ch; int i = 0;
	for (i = 0; i < VERTEX_COUNT * 3 + 10; i++)
	{
		if ((ch = readFile.get()) != '\n')
			head[i] = ch;
		else
			break;
	}
	head[i] = '\0';
	int vertexPointer = 0;
	int cursor;
	for (int i = 0; i < VERTEX_COUNT; i++) {
		char temp[VERTEX_COUNT * 3 + 10];
		int ch, a;
		while ((ch = readFile.get()) == ' ');
		for (a = 0; a < VERTEX_COUNT * 3 + 10; a++)
		{
			if ((ch = readFile.get()) != '\n')
				temp[a] = ch;
			else
				break;
		}
		temp[a] = '\0';

		cursor = 1;
		for (int j = 0; j < VERTEX_COUNT; j++) {
			int h;// = temp[x + 1] - 48;
			h = readNum(&cursor, temp);
			////OutFile << (vertices1[vertexPointer][1] < 10 ? "  " : " ") << (vertices1[vertexPointer][1]);
			Vertices.push_back(glm::vec3((float)j * SIZE, h, (float)i * SIZE));


			Normals.push_back(glm::vec3(0, 1, 0));
			//Normals.push_back(CalculateNormal(i,j));
			vertexPointer++;

			Textures.push_back(glm::vec2((float)j / VERTEX_COUNT, (float)i / VERTEX_COUNT));
		}
	}

	int pointer = 0;
	int triangleIndex = 0;
	int n = 0;
	for (int gz = 0; gz < VERTEX_COUNT - 1; gz++) {
		for (int gx = 0; gx < VERTEX_COUNT - 1; gx++) {
			int topLeft = (gz * VERTEX_COUNT) + gx;
			int topRight = topLeft + 1;
			int bottomLeft = ((gz + 1) * VERTEX_COUNT) + gx;
			int bottomRight = bottomLeft + 1;

			index.push_back(topLeft);
			index.push_back(bottomLeft);
			index.push_back(topRight);

			index.push_back(topRight);
			index.push_back(bottomLeft);
			index.push_back(bottomRight);

			glm::vec3 p1 = glm::vec3(Vertices[topLeft].x, Vertices[topLeft].y, Vertices[topLeft].z);
			glm::vec3 p2 = glm::vec3(Vertices[bottomLeft].x, Vertices[bottomLeft].y, Vertices[bottomLeft].z);
			glm::vec3 p3 = glm::vec3(Vertices[bottomRight].x, Vertices[bottomRight].y, Vertices[bottomRight].z);
			glm::vec3 p4 = glm::vec3(Vertices[topRight].x, Vertices[topRight].y, Vertices[topRight].z);

		
		}
	}

	readFile.close();

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glGenBuffers(1, &TVBO);
	glGenBuffers(1, &NVBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, Vertices.size() * sizeof(glm::vec3), &Vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index.size() * sizeof(int), &index[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, TVBO);
	glBufferData(GL_ARRAY_BUFFER, Textures.size() * sizeof(glm::vec2), &Textures[0], GL_STATIC_DRAW);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, NVBO);
	glBufferData(GL_ARRAY_BUFFER, Normals.size() * sizeof(glm::vec3), &Normals[0], GL_STATIC_DRAW);

	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(2);


	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	texture_1 = Texture::GetInstance().loadTextureBySlot("soil01.jpg", GL_RGB, GL_RGB, 3);
	texture_2 = Texture::GetInstance().loadTextureBySlot("soil02.jpg", GL_RGB, GL_RGB, 4);
	texture_3 = Texture::GetInstance().loadTextureBySlot("soil03.jpg", GL_RGB, GL_RGB, 5);
	blendmap = Texture::GetInstance().loadTextureBySlot("blendmap.png", GL_RGBA, GL_RGBA, 6);
	//std::cout << blendmap << " ";

	object->InitObject(); 
	
	for (int i = 0; i < 2000; i++) {
		int x = rand() % 650;
		int z = rand() % 650;
		plantPos.push_back(glm::vec3(x, GetTerrainHeight(x, z) + 1.0f, z));
		//std::cout  << " " << plantPos[i].x << " " << plantPos[i].y << " " << plantPos[i].z << std::endl;
	}
	plantPos.push_back(glm::vec3(350, GetTerrainHeight(350, 350) + 1.0f, 350));
	object->InitGrass(plantPos); 

	
	treeShader = new Shader("Modelvert.vert", "Modelfrag.frag");

	InitWater();
}

void Terrain::draw(Camera camera, LightDirectional* lightD, LightSpot* lightS, int FlashOn)
{

	this->terrainShader->use();
	model = glm::mat4(1.0f);
	view = camera.GetViewMatrix();
	projection = glm::perspective(glm::radians(camera.Zoom), 800.0f / 600.0f, 0.1f, 300.0f);
	//modelMat = glm::rotate(modelMat, glm::radians(45.0f),glm::vec3(1.0,1.0,0.0));
	this->terrainShader->setUniform4m("model", model);
	this->terrainShader->setUniform4m("view", view);
	this->terrainShader->setUniform4m("projection", projection);

	this->terrainShader->setUniform3f("lightD.pos", lightD->Position);
	this->terrainShader->setUniform3f("lightD.color", lightD->Color);
	this->terrainShader->setUniform3f("lightD.dirToLight", lightD->Direction);

	this->terrainShader->setUniform3f("lightS.pos", camera.Position);
	this->terrainShader->setUniform3f("lightS.color", lightS->Color);
	this->terrainShader->setUniform3f("lightS.dirToLight", lightS->Direction);
	this->terrainShader->setUniform1f("lightS.cosPhyInner", lightS->cosPhyInner);
	this->terrainShader->setUniform1f("lightS.cosPhyOutter", lightS->cosPhyOutter);

	this->terrainShader->setUniform3f("cameraPos", camera.Position);
	this->terrainShader->setUniform1i("FlashOn", FlashOn);
	//terrainShader->setUniform4f("plane", clip);

	//glEnable(GL_TEXTURE_2D);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	this->terrainShader->setUniform1i("texture1", 3);
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, texture_1);

	this->terrainShader->setUniform1i("texture2", 4);
	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, texture_2);

	this->terrainShader->setUniform1i("texture3", 5);
	glActiveTexture(GL_TEXTURE5);
	glBindTexture(GL_TEXTURE_2D, texture_3);

	this->terrainShader->setUniform1i("blendMap", 6);
	glActiveTexture(GL_TEXTURE6);
	glBindTexture(GL_TEXTURE_2D, blendmap);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawElements(GL_TRIANGLES, 6 * (VERTEX_COUNT - 1) * (VERTEX_COUNT - 1), GL_UNSIGNED_INT, 0);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glBindVertexArray(0);
	glDisable(GL_TEXTURE_2D);

	
	//object->Drawcube(camera, lightD, lightS, FlashOn);
	object->DrawPlant(camera, lightD, lightS, FlashOn, plantPos);
	DrawWater(camera, lightD, lightS, FlashOn);
	DrawStone(camera, lightD, lightS, FlashOn);
}


Terrain::Terrain()
{
	this->terrainShader = new Shader("vertexSource.vert", "fragmentSource.frag");
}

void Terrain::InitWater()

{

	float valueX = 153;
	float valueZ = 462;	
	int range = 60;
	int size = 3;

	for (int i = 0; i < range; i++)
	{
		for (int j = 0; j < range; j++)
		{
			WaterVertex.push_back(glm::vec3((float)i * size, 0.0f, (float)j * size));
			WaterNormal.push_back(glm::vec3(0, 1, 0));
			WaterTexture.push_back(glm::vec2((float)(1 - i / range), (float)(1 - j / range)));
		}
	}

	int pointer = 0;
	int triangleIndex = 0;
	int n = 0;
	for (int gz = 0; gz < range - 1; gz++) {
		for (int gx = 0; gx < range - 1; gx++) {
			int topLeft = (gz * range) + gx;
			int topRight = topLeft + 1;
			int bottomLeft = ((gz + 1) * range) + gx;
			int bottomRight = bottomLeft + 1;

			WaterIndex.push_back(topLeft);
			WaterIndex.push_back(bottomLeft);
			WaterIndex.push_back(topRight);

			WaterIndex.push_back(topRight);
			WaterIndex.push_back(bottomLeft);
			WaterIndex.push_back(bottomRight);
		}
	}


	glGenVertexArrays(1, &W_VAO);
	glGenBuffers(1, &W_VBO);
	glGenBuffers(1, &W_EBO);
	glGenBuffers(1, &W_TVBO);
	glGenBuffers(1, &W_NVBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(W_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, W_VBO);
	glBufferData(GL_ARRAY_BUFFER, WaterVertex.size() * sizeof(glm::vec3), &WaterVertex[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, W_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, WaterIndex.size() * sizeof(int), &WaterIndex[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, W_TVBO);
	glBufferData(GL_ARRAY_BUFFER, WaterTexture.size() * sizeof(glm::vec2), &WaterTexture[0], GL_STATIC_DRAW);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, W_NVBO);
	glBufferData(GL_ARRAY_BUFFER, WaterNormal.size() * sizeof(glm::vec3), &WaterNormal[0], GL_STATIC_DRAW);

	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(3);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	WaterShader = new Shader("WaterVert.vert", "WaterFrag.frag");
	waterTex = Texture::GetInstance().loadTextureBySlot("water.png", GL_RGBA, GL_RGBA, 0);
}

void Terrain::InitStone(Model* stoneModel)
{
	stone = stoneModel;
	for (int i = 0; i < stoneAmount; i++) {
		float x = RandomNum::GetInstance().GetRandomNumber1f(0.0f, 700.0f);
		float z = RandomNum::GetInstance().GetRandomNumber1f(0.0f, 700.0f);
		//float y = Terrain::GetInstance().GetTerrainHeight(x, z);
		glm::vec3 Pos = glm::vec3(x, GetTerrainHeight(x, z), z);
		//std::cout << Pos.x << " " << Pos.y << " " << Pos.z << " " << std::endl;
		stonesPos.push_back(Pos);
		//stoneScale.push_back(glm::vec3(RandomNum::GetInstance().GetRandomNumber1f(0.3f, 1.0f)));
	}
	//Set model matrix
	for (int i = 0; i < stoneAmount; i++)
	{
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(stonesPos[i].x, stonesPos[i].y, stonesPos[i].z));
		model = glm::scale(model, glm::vec3(RandomNum::GetInstance().GetRandomNumber1f(0.3f, 1.0f)));
		float rotAngle = (rand() % 360);
		model = glm::rotate(model, rotAngle, glm::vec3(0.0f, 1.0f, 0.0f));
		stoneModelMat.push_back(model);
	}

	stoneShader = new Shader("ModelInsVert.vert", "Modelfrag.frag");

	unsigned int stoneVBO;
	glGenBuffers(1, &stoneVBO);
	glBindBuffer(GL_ARRAY_BUFFER, stoneVBO);
	glBufferData(GL_ARRAY_BUFFER, stoneModelMat.size() * sizeof(glm::mat4), &stoneModelMat[0], GL_STATIC_DRAW);
	GLsizei vec4Size = sizeof(glm::vec4);

	for (unsigned int i = 0; i < stoneModel->meshes.size(); i++)
	{
		unsigned int stoneVAO = stoneModel->meshes[i].VAO;
		glBindVertexArray(stoneVAO);
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);
		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4)));
		glEnableVertexAttribArray(5);
		glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));
		glEnableVertexAttribArray(6);
		glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));

		glVertexAttribDivisor(3, 1);
		glVertexAttribDivisor(4, 1);
		glVertexAttribDivisor(5, 1);
		glVertexAttribDivisor(6, 1);

		glBindVertexArray(0);
	}


}


void Terrain::DrawWater(Camera camera, LightDirectional* lightD, LightSpot* lightS, int FlashOn)
{
	WaterShader->use();
	model = glm::mat4(1.0f);
	view = camera.GetViewMatrix();
	projection = glm::perspective(glm::radians(camera.Zoom), 800.0f / 600.0f, 0.1f, 300.0f);
	//modelMat = glm::rotate(modelMat, glm::radians(45.0f),glm::vec3(1.0,1.0,0.0));
	model = glm::translate(model, glm::vec3(163.448f, 1.0f, 420.987f));
	WaterShader->setUniform4m("model", model);
	WaterShader->setUniform4m("view", view);
	WaterShader->setUniform4m("projection", projection);

	WaterShader->setUniform3f("lightD.pos", lightD->Position);
	WaterShader->setUniform3f("lightD.color", lightD->Color);
	WaterShader->setUniform3f("lightD.dirToLight", lightD->Direction);

	WaterShader->setUniform3f("lightS.pos", camera.Position);
	WaterShader->setUniform3f("lightS.color", lightS->Color);
	WaterShader->setUniform3f("lightS.dirToLight", lightS->Direction);
	WaterShader->setUniform1f("lightS.cosPhyInner", lightS->cosPhyInner);
	WaterShader->setUniform1f("lightS.cosPhyOutter", lightS->cosPhyOutter);

	WaterShader->setUniform3f("cameraPos", camera.Position);
	WaterShader->setUniform1i("FlashOn", FlashOn);

	WaterShader->setUniform3f("material.ambient", glm::vec3(1.0f, 1.0f, 1.0f));

	WaterShader->setUniform1i("material.diffuse", 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, waterTex);
	WaterShader->setUniform1i("material.specular", 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, waterTex);

	WaterShader->setUniform1f("material.shininess", 64.0f);

	glBindVertexArray(W_VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, W_EBO);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawElements(GL_TRIANGLES, 6 * (60 - 1) * (60 - 1), GL_UNSIGNED_INT, 0);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glBindVertexArray(0);
	glDisable(GL_TEXTURE_2D);
}

void Terrain::DrawStone(Camera camera, LightDirectional* lightD, LightSpot* lightS, int FlashOn)
{
	stoneShader->use();
	view = camera.GetViewMatrix();
	projection = glm::perspective(glm::radians(camera.Zoom), 800.0f / 600.0f, 0.1f, 300.0f);
	stoneShader->setUniform4m("viewMat", view);
	stoneShader->setUniform4m("projectMat", projection);

	//Set Directional Light
	stoneShader->setUniform3f("lightD.pos", lightD->Position);
	stoneShader->setUniform3f("lightD.color", lightD->Color);
	stoneShader->setUniform3f("lightD.dirToLight", lightD->Direction);

	//Set Spot Light
	stoneShader->setUniform3f("lightS.pos", camera.Position);
	stoneShader->setUniform3f("lightS.color", lightS->Color);
	stoneShader->setUniform3f("lightS.dirToLight", lightS->Direction);
	stoneShader->setUniform1f("lightS.cosPhyInner", lightS->cosPhyInner);
	stoneShader->setUniform1f("lightS.cosPhyOutter", lightS->cosPhyOutter);

	stoneShader->setUniform3f("cameraPos", camera.Position);

	//Set Meterial -> Testure
	stoneShader->setUniform3f("material.ambient", glm::vec3(1.0f, 1.0f, 1.0f));
	stoneShader->setUniform1i("material.diffuse", 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, stone->textures_loaded[0].id);
	stoneShader->setUniform1i("material.specular", 1);
	stoneShader->setUniform1f("material.shininess", 256.0f);
	stoneShader->setUniform1i("FlashOn", FlashOn);

	stoneShader->use();
	for (unsigned int i = 0; i < stone->meshes.size(); i++)
	{
		glBindVertexArray(stone->meshes[i].VAO);
		glDrawElementsInstanced(GL_TRIANGLES, stone->meshes[i].indices.size(), GL_UNSIGNED_INT, 0, stoneAmount);
		glBindVertexArray(0);
	}
}

void Terrain::DrawTree(Camera camera, LightDirectional* lightD, LightSpot* lightS, int FlashOn, Model* treeModel,std::vector<glm::vec3>treePosition, glm::vec3 scaleSize)
{
	
	model = glm::mat4(1.0f);
	treeShader->use();
	//Set view and projection mat
	view = camera.GetViewMatrix();
	projection = glm::perspective(glm::radians(camera.Zoom), 800.0f / 600.0f, 0.1f, 300.0f);
	treeShader->setUniform4m("viewMat", view);
	treeShader->setUniform4m("projectMat", projection);

	//Set Directional Light
	treeShader->setUniform3f("lightD.pos", lightD->Position);
	treeShader->setUniform3f("lightD.color", lightD->Color);
	treeShader->setUniform3f("lightD.dirToLight", lightD->Direction);

	//Set Spot Light
	treeShader->setUniform3f("lightS.pos", camera.Position);
	treeShader->setUniform3f("lightS.color", lightS->Color);
	treeShader->setUniform3f("lightS.dirToLight", lightS->Direction);
	treeShader->setUniform1f("lightS.cosPhyInner", lightS->cosPhyInner);
	treeShader->setUniform1f("lightS.cosPhyOutter", lightS->cosPhyOutter);


	treeShader->setUniform3f("cameraPos", camera.Position);
	//treeShader->setUniform4f("plane", clip);
	 
	//Set Meterial -> Testure
	treeShader->setUniform3f("material.ambient", glm::vec3(1.0f, 1.0f, 1.0f));
	treeShader->setUniform1i("material.diffuse", 0);
	treeShader->setUniform1i("material.specular", 1);

	treeShader->setUniform1f("material.shininess", 32.0f);
	treeShader->setUniform1i("FlashOn", FlashOn);

	float rotateRadian = 0.0f;
	for (int i = 0; i < treePosition.size(); i++) {
		model = glm::mat4(1.0f);
		model = glm::translate(model, treePosition[i]);
		//231.0f, 3.65f, 418.0

		model = glm::scale(model, scaleSize);
		treeShader->setUniform4m("modelMat", model);
		treeModel->Draw(treeShader);
	}

}


