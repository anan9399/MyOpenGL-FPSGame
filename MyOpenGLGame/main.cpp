#include "Game.h"
#define STB_IMAGE_IMPLEMENTATION
#include"stb_image.h"
#include"Terrain.h"


int main(int agrc, char* argv[]) {
	Game game;
	std::string exePath = argv[0];
	game.SetExePath(exePath);
	/*Terrain terrain;
	terrain.InitTerrain();*/
	game.run();


	return 0;
}