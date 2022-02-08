#include "Engine.h"

float quadVertices[] = {
	// positions   // texCoords
	-1.0f,  1.0f,  0.0f, 1.0f,
	-1.0f, -1.0f,  0.0f, 0.0f,
	 1.0f, -1.0f,  1.0f, 0.0f,

	-1.0f,  1.0f,  0.0f, 1.0f,
	 1.0f, -1.0f,  1.0f, 0.0f,
	 1.0f,  1.0f,  1.0f, 1.0f
};

#pragma region Camera
Camera camera(glm::vec3(350.0f, 5.0f, 350.0f), glm::radians(-15.0f), -90.0f, glm::vec3(0, 1, 0));
float cameraSpeed = 0.1f;
#pragma endregion

#pragma region processInput
GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;
int FlashOn = 0;

void Engine::processInput(GLFWwindow* window, float dt) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		camera.MoveForward(1);
	}
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		camera.MoveForward(-1);
	}


	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		// camera.Position -= glm::normalize(glm::cross(camera.Forward, camera.WorldUp)) * cameraSpeed;
		//camera.SpeedX = -0.1f;
		camera.MoveRight(-1);
	}
	else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		// camera.Position += glm::normalize(glm::cross(camera.Forward, camera.WorldUp)) * cameraSpeed;
		//camera.SpeedX = 0.1f;
		camera.MoveRight(1);
	}
	else {
		camera.SpeedX = 0.0f;
	}

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
		if (Game::getintance().FlashOn == 0)
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
}

float lastX, lastY;
bool firstMouse = true;

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

void Engine::run()
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
		return;
	}
	glfwMakeContextCurrent(window);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	//Init GLEW
	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		printf("Init GLEW failed");
		glfwTerminate();
		return;
	}
	glViewport(0, 0, Screen_Width, Screen_Height);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

#pragma endregion

	Init();
	Gameloop();
}

void Engine::Init()
{
#pragma region Init Screen FrameBuffer
	screenShader = new Shader("ScreenVert.vert", "ScreenFrag.frag");


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

	lightD = new LightDirectional(glm::vec3(2.0f, 10.0f, 10.0f),
		glm::vec3(glm::radians(60.0f), 0, 0),
		glm::vec3(0.25, 0.25, 0.25));
	//(0.25, 0.25, 0.25)
	lightS = new LightSpot(glm::vec3(0.0f, 5.0f, 0.0f),
		glm::vec3(glm::radians(180.0f), 0, 0),
		glm::vec3(2.0, 2.0, 2.1));



	skybox = new Skybox();
	object = new Object();
	treeModel = new Model(exePath.substr(0, exePath.find_last_of('\\')) + "\\model\\tree\\tree.obj");
	treeShader = new Shader("Modelvert.vert", "Modelfrag.frag");
	fbos = new WaterFrameBuffer();
	enermy = new Enermy(exePath.substr(0, exePath.find_last_of('\\')) + "\\model\\cube\\cube.obj");


	Game::getintance().SetCamera(camera);
	Game::getintance().InitTerrain();
	skybox->InitSkybox();
	Game::getintance().WaterVertexIndex();
	object->InitObject();
	object->InitGrass(Game::getintance().plantPos);
	//glEnableClientState(GL_VERTEX_ARRAY);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);


}

void Engine::Gameloop()
{
	while (!glfwWindowShouldClose(window)) {
		// input
	   // -----
		processInput(window, deltaTime);

		GLfloat currentFrame = glfwGetTime();
		deltaTime = (currentFrame - lastFrame);
		lastFrame = currentFrame;

		//std::cout << deltaTime << std::endl;

		float nowy = Game::getintance().GetTerrainHeight(camera.Position.x, camera.Position.z);

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

		Game::getintance().DrawTerrain(glm::vec4(0, -1, 0, 2000));
		Game::getintance().DrawWater();
		enermy->Update(camera, lightD, lightS, FlashOn);
		//object->DrawWater(camera, lightD, lightS, FlashOn,fbos->getReflectionTexture());


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



		glfwSwapBuffers(window);
		glfwPollEvents();
		lightS->UpdateLightSVector(camera);
		camera.UpdateCameraPos(nowy, deltaTime);

		//std::cout << camera.Position.x<< " " << nowy <<  " " << camera.Position.z<< std::endl;

	}
	fbos->cleanUp();
	glfwTerminate();

}
