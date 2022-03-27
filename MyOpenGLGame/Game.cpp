#include "Game.h"
//#include<glut.h>
#include"stb_image.h"
#include<vector>




float quadVertices1[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
	  // positions   // texCoords
	  -1.0f,  1.0f,  0.0f, 0.0f,
	  -1.0f, 0.0f,  0.0f, 1.0f,
	   0.0f, 0.0f,   1.0f, 1.0f,

	  -1.0f,  1.0f,  0.0f, 0.0f,
	   0.0f, 1.0f,   1.0f, 0.0f,
	   0.0f,  0.0f,  1.0f, 1.0f
};

float quadVertices[] = {
	  // positions   // texCoords
	  -1.0f,  1.0f,  0.0f, 1.0f,
	  -1.0f, -1.0f,  0.0f, 0.0f,
	   1.0f, -1.0f,  1.0f, 0.0f,

	  -1.0f,  1.0f,  0.0f, 1.0f,
	   1.0f, -1.0f,  1.0f, 0.0f,
	   1.0f,  1.0f,  1.0f, 1.0f
};

float aimVertices[] = {
	// positions   // texCoords
	-0.045f,  0.05f,  0.0f, 1.0f,
	-0.045f, -0.05f,  0.0f, 0.0f,
	 0.045f, -0.05f,  1.0f, 0.0f,
	   		  
	-0.045f,  0.05f,  0.0f, 1.0f,
	 0.045f, -0.05f,  1.0f, 0.0f,
	 0.045f,  0.05f,  1.0f, 1.0f
};


std::vector<glm::vec3> treePosition{
	glm::vec3(234.508f, 35.8568f, 226.0f),
	glm::vec3(231.0f, 3.0f, 418.0f),
	glm::vec3(235.011f, 2.8f, 533.796f),
	glm::vec3(159.971f, 2.5f, 466.452f)
};

std::vector<glm::vec3> treeScale {
	glm::vec3(0.05f),
	glm::vec3(0.05f),
	glm::vec3(0.05f),
	glm::vec3(0.05f),
};

std::vector<glm::vec3> enermyPos{
	glm::vec3(372.2f,17.1f,453.9f),
	glm::vec3(234.508f, 35.8568f, 226.0f),
	glm::vec3(547.2f,9.0f,264.4f),
	glm::vec3(0)

};

#pragma region Camera

Camera camera(glm::vec3(350.0f, 5.0f, 350.0f), glm::radians(-15.0f), -90.0f, glm::vec3(0, 1, 0));
float cameraSpeed = 0.1f;
Raytest* raytest = new Raytest();
#pragma endregion

#pragma region processInput
GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;
int FlashOn = 0;

void Game::processInput(GLFWwindow* window, float dt) {
	float speed=1.0f;
	int mode = 0x0001;
	if (glfwGetKey(window, GLFW_MOD_SHIFT)==GLFW_PRESS) {
		std::cout << "1";
	}

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		camera.MoveForward(speed);
		move = true;
	}
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		camera.MoveForward(-speed);
		move = true;
	}
	else
		move = false;


	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		// camera.Position -= glm::normalize(glm::cross(camera.Forward, camera.WorldUp)) * cameraSpeed;
		//camera.SpeedX = -0.1f;
		camera.MoveRight(-speed);
	}
	else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		// camera.Position += glm::normalize(glm::cross(camera.Forward, camera.WorldUp)) * cameraSpeed;
		//camera.SpeedX = 0.1f;
		camera.MoveRight(speed);
	}
	/*else {
		camera.SpeedX = 0.0f;
	}*/

	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
		//camera.Position -= glm::normalize(glm::cross(camera.Forward, camera.WorldUp)) * cameraSpeed;
		camera.SpeedY = 5.5f;
		//camera.jump();
	}
	else if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
		//camera.Position += glm::normalize(glm::cross(camera.Forward, camera.WorldUp)) * cameraSpeed;
		camera.SpeedY = 5.6f;
	}
	else {
		camera.SpeedY = 0.0f;
	}

	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
		if (FlashOn == 0)
			FlashOn = 1;
		else
			FlashOn = 0;
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {

		if (!camera.inAir) {
			camera.inAir = true;
			camera.isJump = true;
			camera.upwardSpeed = 0.0f;
		}
	}
	if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS) {
		//enermies[0]->beHit();
		raytest->CastRay();
	
	}
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
		/*if (player->GetAmo() != 0) {
			player->Reload(dt, 1);*/
		//player->QuickReload(dt);
		weapon->Reload(dt);
	}



	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
		if (WeaponMod != 1) {
			WeaponMod = 1;
			WeaponSwitch = true;
		}
	}
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
		if (WeaponMod != 2) {
			WeaponMod = 2;
			WeaponSwitch = true;
		}
	}
	if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) {
		if (WeaponMod != 0) {
			WeaponMod = 0;
			WeaponSwitch = true;
		}
	}
	WeaponSwitch = weapon->SwitchWeapon(player, WeaponMod, WeaponSwitch, deltaTime);
}

float lastX, lastY;
bool firstMouse = true;
bool mouse_button=false;
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		mouse_button = true;
	}
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {

		mouse_button = false;
	}
	/*if (action == GLFW_PRESS) switch (button)
	{
	case GLFW_MOUSE_BUTTON_LEFT:
		std::cout<<"Mosue left button clicked!" << std::endl;
		raytest->CastRay();
		break;
	case GLFW_MOUSE_BUTTON_MIDDLE:
		std::cout << "Mosue middle button clicked!" << std::endl;
		break;
	case GLFW_MOUSE_BUTTON_RIGHT:
		std::cout << "Mosue right button clicked!"<< std::endl;
		break;
	default:
		return;
	}
	return;*/
}



void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	float deltaX, deltaY;
	if (firstMouse == true) {
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}
	deltaX = xpos - lastX;
	deltaY = lastY - ypos;
	lastX = xpos;
	lastY = ypos;


	camera.ProcessMouseMovement(deltaX, deltaY);

}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	camera.ProcessMouseScroll(yoffset);
	std::cout << yoffset;
}

#pragma endregion



void Game::run()
{
#pragma region openWindow
	//Init GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open window
	 window = glfwCreateWindow(Screen_Width, Screen_Height, "My OpenGL Window", NULL, NULL);
	if (window == NULL) {
		printf("open window failed");
		glfwTerminate();
		return ;
	}
	glfwMakeContextCurrent(window);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	//Init GLEW
	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		printf("Init GLEW failed");
		glfwTerminate();
		return ;
	}
	glViewport(0, 0, Screen_Width, Screen_Height);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//glfwSetInputMode(window, GLFW_STICKY_MOUSE_BUTTONS, GLFW_TRUE);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);

#pragma endregion

	Init();
	Gameloop();
}



void Game::Init()
{
#pragma region Init Screen FrameBuffer
	screenShader = new Shader("ScreenVert.vert","ScreenFrag.frag");

	glGenVertexArrays(1, &quadVAO);
	glGenBuffers(1, &quadVBO);
	glBindVertexArray(quadVAO);
	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	
	glGenFramebuffers(1, &framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	// create a color attachment texture

	glGenTextures(1, &textureColorbuffer);
	glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1600, 1200, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, textureColorbuffer, 0);
	// create a renderbuffer object for depth and stencil attachment (we won't be sampling these)

	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 1600, 1200); // use a single renderbuffer object for both a depth AND stencil buffer.
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo); // now actually attach it
	// now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

#pragma endregion

#pragma region Init light
	lightD = new LightDirectional(glm::vec3(2.0f, 10.0f, 10.0f),
		glm::vec3(glm::radians(60.0f),0, 0),
		glm::vec3(0.25, 0.25, 0.25));
	//(0.25, 0.25, 0.25)
	 lightS = new LightSpot(camera.Position,
		glm::vec3(glm::radians(180.0f), 0, 0),
		glm::vec3(2.5, 2.5, 2.6));
#pragma endregion

#pragma region Init 
	 skybox = new Skybox();
	 object = new Object();
	 treeModel = new Model(exePath.substr(0, exePath.find_last_of('\\')) + "\\model\\tree\\tree.obj");
	 stoneModel = new Model(exePath.substr(0, exePath.find_last_of('\\')) + "\\model\\Rock\\rock.obj");
	 fbos = new WaterFrameBuffer();
	 enermyModel = new Model(exePath.substr(0, exePath.find_last_of('\\')) + "\\model\\cube\\cube.obj");
	 enermyShader = new Shader("Modelvert.vert", "Modelfrag.frag");
	 player = new Player();
	 weapon = new Weapon(player);
	 GunModel = new Model(exePath.substr(0, exePath.find_last_of('\\')) + "\\model\\cube\\cube.obj");

	 gunShader = new Shader("Modelvert.vert", "Modelfrag.frag");

	 weapon->IniteModel(GunModel);
#pragma endregion

#pragma region Init enermy
	 TotalEnermyNum = 100;
	 CurrentEnermyNum = 0;

	 for (int j = 0; j < TotalEnermyNum; j++) {
			 Enermy* enermy = new Enermy();
			 enermies.push_back(enermy);
	 }

	 std::cout << enermies.size() << std::endl;
	 EnemyBorn(3);

#pragma endregion
	

#pragma region Init terrain
	Terrain::GetInstance().Init();
	Terrain::GetInstance().InitStone(stoneModel);
	skybox->InitSkybox();
	object->InitObject();
	//glEnableClientState(GL_VERTEX_ARRAY);
	
#pragma endregion
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}



glm::vec3 normalVector[VERTEX_COUNT * VERTEX_COUNT * 2];

//float Game::GetTerrainHeight(float x, float z)
//{
//	float CameraX = x / SIZE;
//	float CameraZ = z / SIZE;
//	int Col0 = int(CameraX);
//	int Row0 = int(CameraZ);
//	int Col1 = Col0 + 1;
//	int Row1 = Row0 + 1;
//	if (Col1 > VERTEX_COUNT)	Col1 = 0;
//	if (Row1 > VERTEX_COUNT)	Row1 = 0;
//	float h00 = Vertices[Col0 + Row0 * VERTEX_COUNT].y;
//	float h01 = Vertices[Col1 + Row0 * VERTEX_COUNT].y;
//	float h11 = Vertices[Col1 + Row1 * VERTEX_COUNT].y;
//	float h10 = Vertices[Col0 + Row1 * VERTEX_COUNT].y;
//	float tx = CameraX - int(CameraX);
//	float ty = CameraZ - int(CameraZ);
//	float txty = tx * ty;
//	return h00 * (1.0f - ty - tx + txty)
//		+ h01 * (tx - txty)
//		+ h11 * txty
//		+ h10 * (ty - txty);
//}

int readNum(int* cursor, char str[VERTEX_COUNT * 3 + 10])
{
	char c[4];
	for (int i = 0; i < 3; i++)
	{
		c[i] = str[(*cursor)++];
	}
	c[3] = '\0';
	return atoi(c);
}

//glm::vec3 CalculateNormal(unsigned int x, unsigned int z)
//{
//	if (x >= 0 && x < VERTEX_COUNT - 1 && z >= 0 && z < VERTEX_COUNT - 1)
//	{
//		float heightL = Game::GetTerrainHeight((float)x - 1, (float)z);
//		float heightR = Game::GetTerrainHeight((float)x + 1, (float)z);
//		float heightD = Game::GetTerrainHeight((float)x, (float)z - 1);
//		float heightU = Game::GetTerrainHeight((float)x, (float)z + 1);
//
//		glm::vec3 normal(heightL - heightR, 2.0f, heightD - heightU);
//		normal = glm::normalize(normal);
//		return normal;
//	}
//
//	return glm::vec3(0.0f, 0.0f, 0.0f);
//}




void Game::Gameloop()
{
	int i = 0;
	while (!glfwWindowShouldClose(window)) {
		// input
	   // -----
		

		GLfloat currentFrame = glfwGetTime();
		deltaTime = (currentFrame - lastFrame);
		lastFrame = currentFrame;

		//std::cout << deltaTime << std::endl;

		i++;
		if (i == 800) {
			EnemyBorn(1);
			i = 0;
		}
		
		
		float nowy = Terrain::GetInstance().GetTerrainHeight(camera.Position.x, camera.Position.z);

		//fbos->BindReflectionFrameBuffer();
		//float distance = 2 * (camera.Position.y-GetTerrainHeight(camera.Position.x,camera.Position.z));
		//camera.Position.y -= distance;
		//camera.inversePitch();
		//DrawTerrain(glm::vec4(0, 1, 0, 1));
		//skybox->draw(camera);
		//camera.Position.y += distance;
		//camera.inversePitch();
		//fbos->BindRefractionFrameBuffer();
		//DrawTerrain(glm::vec4(0, -1, 0, 0));
		//fbos->UnbindCurrentFrameBuffer();
		//terrain->DrawSand(camera,FlashOn,lightD,lightS);

		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);


		
		//Render screen
		//skybox->draw(camera);
		Terrain::GetInstance().draw(camera, lightD, lightS, FlashOn);
		Terrain::GetInstance().DrawTree(camera, lightD, lightS, FlashOn, treeModel, treePosition, glm::vec3(0.05));
		DrawEnermy(camera, lightD, lightS, FlashOn, enermies);
		DrawEnermy(camera, lightD, lightS, FlashOn, DeadEnermies);
		weapon->Draw(camera, lightD, lightS, FlashOn, move, deltaTime);

		/*enermy->DrawEnermy(camera, lightD, lightS, FlashOn);
		object->DrawWater(camera, lightD, lightS, FlashOn,fbos->getReflectionTexture());*/

		//Render framebuffer
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glDisable(GL_DEPTH_TEST); 
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f); 
		glClear(GL_COLOR_BUFFER_BIT);
		screenShader->use();
		glBindVertexArray(quadVAO);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
		screenShader->setUniform1i("screenTexture", 0);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		//glEnable(GL_DEPTH_TEST);
		

		//in order to make Crosshair is in front of everything
		//draw the Crosshair after the framebuffer when depth is off
		object->DrawCrosshair();

		
		for (auto i = enermies.begin(); i != enermies.end(); i++)
		{
			(*i)->Update(camera, lightD, lightS, FlashOn, player, deltaTime);
			if (!(*i)->alive) {
				Enermy* enermy = new Enermy(false);
				enermy->ActiveEnermy((*i)->Position);
				DeadEnermies.push_back(enermy);
				i = enermies.erase(i);
			}
			if (i == enermies.end())
			{
				break;
			}
		}
		weapon->Upload(camera, enermies, raytest, mouse_button, deltaTime);
	
		//hp <= 0 player lose
		if (player->hp <= 0) {
			object->DrawEnd(lose);
		}
	       // defeat 20 enems player win
		if (DeadEnermies.size()>=20) {
			object->DrawEnd(win);
		}
		
		//AttackUpdate(player);
		processInput(window, deltaTime);
		
		glfwSwapBuffers(window);
		glfwPollEvents();
		lightS->UpdateLightSVector(camera);
		camera.UpdateCameraPos(nowy,deltaTime);
		
		//std::cout << camera.Forward.x<< " " << camera.Forward.y <<  " " << camera.Forward.z <<  " " <<  std::endl;

	}

	fbos->cleanUp();
	glfwTerminate();

}

void Game::InitLight()
{
	
}


void Game::EnemyBorn(int n)
{
	int i = 0;
	while (i < n && CurrentEnermyNum < TotalEnermyNum) {
		int pos = i % 3;
		enermies[CurrentEnermyNum]->ActiveEnermy(enermyPos[i]);
		CurrentEnermyNum++;
		i++;
	}
	
}


void Game::DrawEnermy(Camera camera, LightDirectional* lightD, LightSpot* lightS, int FlashOn, std::vector<Enermy*>enermys)
{
	//Set view and projection mat
	enermyShader->use();
	view = camera.GetViewMatrix();
	projection = glm::perspective(glm::radians(camera.Zoom), 800.0f / 600.0f, 0.1f, 300.0f);
	enermyShader->setUniform4m("viewMat", view);
	enermyShader->setUniform4m("projectMat", projection);

	//Set Directional Light
	enermyShader->setUniform3f("lightD.pos", lightD->Position);
	enermyShader->setUniform3f("lightD.color", lightD->Color);
	enermyShader->setUniform3f("lightD.dirToLight", lightD->Direction);

	//Set Spot Light
	enermyShader->setUniform3f("lightS.pos", camera.Position);
	enermyShader->setUniform3f("lightS.color", lightS->Color);
	enermyShader->setUniform3f("lightS.dirToLight", lightS->Direction);
	enermyShader->setUniform1f("lightS.cosPhyInner", lightS->cosPhyInner);
	enermyShader->setUniform1f("lightS.cosPhyOutter", lightS->cosPhyOutter);


	enermyShader->setUniform3f("cameraPos", camera.Position);

	//Set Meterial -> Testure
	enermyShader->setUniform3f("material.ambient", glm::vec3(1.0f, 1.0f, 1.0f));
	enermyShader->setUniform1i("material.diffuse", 0);
	enermyShader->setUniform1i("material.specular", 1);
	enermyShader->setUniform1f("material.shininess", 64.0f);
	enermyShader->setUniform1i("FlashOn", FlashOn);

	for (int i = 0; i < enermys.size(); i++)
	{
		if (enermys[i]->Hurt) {
			enermyShader->setUniform1i("Hurt", 1);
		}
		else {
			enermyShader->setUniform1i("Hurt", 0);
		}
		
		model = glm::mat4(1.0f);
		model = glm::translate(model, enermys[i]->Position);

		//model = glm::rotate(model, enermys[i]->Angle, glm::vec3(0, 1.0f, 0));	
		if (enermys[i]->alive == false) {
			model = glm::translate(model, glm::vec3(0, -5.0f, 0));
			model = glm::rotate(model, glm::radians(45.0f), glm::vec3(1.0f, 0, 0));
		}

		
		enermyShader->setUniform4m("modelMat", model);
		enermyModel->Draw(enermyShader);
	}
	enermyShader->stop();

	for (auto i = enermys.begin(); i != enermys.end(); i++) {
		if ((*i)->active) {
			(*i)->DrawParticle(camera, deltaTime);
		}
	}

}


/****************************************************************/
//Player attack check
void Game::AttackUpdate(Player* player)
{
	//check player is using which weapon. 0 is close fight so dont need reload or amo
	if (player->GetWeapon() !=0) {
		//check whether player is reloading
		if (player->ReloadCheck()) {
			if (player->atkDuration >= player->atkDurationMax && mouse_button) {
					player->AmoCheck();
					raytest->CastRay();
					std::cout << player->GetAmo() << std::endl;
					//check the amo
			}
			else if (player->atkDuration < player->atkDurationMax){
				player->atkDuration += 2 * deltaTime;
			}
		}
		else
		{
			player->Reload(deltaTime);
		}
	} else if (player->atkDuration >= player->atkDurationMax && mouse_button) {
				raytest->CastRay();
		}

	raytest->Update(camera, deltaTime, enermies, player->GetWeapon());
}

glm::vec3 generateNormal(glm::vec3 trianglePoint1, glm::vec3 trianglePoint2, glm::vec3 trianglePoint3)
{
	// point 2 - point 1
	glm::vec3 side1 = trianglePoint2 - trianglePoint1;

	// point 3 - point 1 
	glm::vec3 side2 = trianglePoint3 - trianglePoint1;

	//calculating the cross product
	glm::vec3 normalVector;
	normalVector.x = (side1.y * side2.z) - (side1.z * side2.y);
	normalVector.y = (side1.z * side2.x) - (side1.x * side2.z);
	normalVector.z = (side1.x * side2.y) - (side1.y * side2.x);

	//normalizing so all x,y and z only add up to 1.0 and it doesn't increase the force's magnitude
	glm::vec3 scaledNormalVector;
	scaledNormalVector.x = normalVector.x / (fabs(normalVector.x) + fabs(normalVector.y) + fabs(normalVector.z));
	scaledNormalVector.y = normalVector.y / (fabs(normalVector.x) + fabs(normalVector.y) + fabs(normalVector.z));
	scaledNormalVector.z = normalVector.z / (fabs(normalVector.x) + fabs(normalVector.y) + fabs(normalVector.z));

	return scaledNormalVector;
}


//void Game::DrawGun(Camera camera, LightDirectional* lightD, LightSpot* lightS, int FlashOn)
//{
//
//	model = glm::mat4(1.0f);
//	gunShader->use();
//	//Set view and projection mat
//	view = camera.GetViewMatrix();
//	projection = glm::perspective(glm::radians(camera.Zoom), 800.0f / 600.0f, 0.00000001f, 300.0f);
//	gunShader->setUniform4m("viewMat", view);
//	gunShader->setUniform4m("projectMat", projection);
//
//	//Set Directional Light
//	gunShader->setUniform3f("lightD.pos", lightD->Position);
//	gunShader->setUniform3f("lightD.color", lightD->Color);
//	gunShader->setUniform3f("lightD.dirToLight", lightD->Direction);
//
//	//Set Spot Light
//	gunShader->setUniform3f("lightS.pos", camera.Position);
//	gunShader->setUniform3f("lightS.color", lightS->Color);
//	gunShader->setUniform3f("lightS.dirToLight", lightS->Direction);
//	gunShader->setUniform1f("lightS.cosPhyInner", lightS->cosPhyInner);
//	gunShader->setUniform1f("lightS.cosPhyOutter", lightS->cosPhyOutter);
//
//
//	gunShader->setUniform3f("cameraPos", camera.Position);
//	//treeShader->setUniform4f("plane", clip);
//
//	//Set Meterial -> Testure
//	gunShader->setUniform3f("material.ambient", glm::vec3(1.0f, 1.0f, 1.0f));
//	gunShader->setUniform1i("material.diffuse", 0);
//	gunShader->setUniform1i("material.specular", 1);
//
//	gunShader->setUniform1f("material.shininess", 32.0f);
//	gunShader->setUniform1i("FlashOn", FlashOn);
//
//	
//	model = glm::mat4(1.0f);
//	glm::mat4 invViewMat = glm::inverse(camera.GetViewMatrix()); 
//	glm::vec3 transpotMat = glm::vec3(1.7f, 2.0f, 2.0f);
//
//	glm::mat4 translation = glm::translate(transpotMat);
//	glm::mat4 rotation = glm::rotate(1.0f, glm::vec3(0.0f, 1.0f, 0.0f));
//	glm::mat4 scaleMat = glm::scale(glm::vec3(0.0001f));
//
//	model = invViewMat * translation;
//	//model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
//	//231.0f, 3.65f, 418.0
//
//	gunShader->setUniform4m("modelMat", model);
//	GunModel->Draw(gunShader);
//
//
//}
//}
