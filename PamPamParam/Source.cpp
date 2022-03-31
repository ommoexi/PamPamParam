#define STB_IMAGE_IMPLEMENTATION
#include "utils.h"
#include "initTextures.h"
#include "window.h"
#include "textureArray.h"
#include "constants.h"
#include "text.h"
#include "rectangle.h"
#include "handler.h"
#include "player.h"
#include "Batch.h"
#include "shaders.h"
#include "initTextures.h"
#include "input.h"
#include "includeBlocks.h"
#include "includeEntities.h"
#include "enemy.h"

namespace {
	
	double previousTime = SDL_GetTicks();
	Handler handler{};
	int frameCount = 0;
	Text framerateText{ Constants::width - framerateText.getPixelWidthFirstRow() - 10, 
		Constants::height - framerateText.getPixelHeightFirstRow() -10,
		20,20, Colors::black, "FPS" , Textures::I_FONT, 0};

	void framerate() {
		double currentTime = SDL_GetTicks();
		frameCount++;
		// If a second has passed.
		if (currentTime - previousTime >= 1000)
		{
			framerateText.setContent(std::to_string(frameCount) + " FPS");
			//std::cout << frameCount << '\n';
			frameCount = 0;
			previousTime = currentTime;
			framerateText.setX(Constants::width - framerateText.getPixelWidthFirstRow() -10);
			framerateText.setY(Constants::height - framerateText.getPixelHeightFirstRow() - 10);
		}
	}

}

std::vector<std::vector<int>>t{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
};

#include "map.h"

int main(int argc, char* argv[])
{

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	Animation standingAnimation{ Textures::animations::animationVecDog, 8 };
#ifdef _DEBUG
	CollisionBox* hitCollision{ new CollisionBox{30,20,155,180, Textures::collisionBox, Colors::red } };
#else 
	CollisionBox* hitCollision{ new CollisionBox{30,20,155,180 } };
#endif
	Player player{ 1000,1000 , 200, 200, standingAnimation, 5, *hitCollision};

	Map basicMap{ Point{-50000,-50000}, Point{50000, 50000}, static_cast<unsigned int>(Constants::width + Constants::height),
		2,2, &player };
	float y = -100;
	for (auto& f : t) {
		y += 100;
		float x = -100;
		for (auto& in : f) {
			x += 100;
			if (in == 1) {
				BasicBlock* t{ new BasicBlock{x,y, 100, 100, Textures::death} };
				basicMap.addObj(*t, true);
			}
		}
	}
	for (int i{}; i < 10; i++) {
#ifdef _DEBUG
		CollisionBox* wowColl{ new CollisionBox{0,0,100,100, Textures::collisionBox, Colors::red } };
#else 
		CollisionBox* wowColl{ new CollisionBox{0,0,100,100 } };
#endif
		Enemy* enemy{ new Enemy{200,200,100,100, Textures::player, 5, *wowColl} };
		basicMap.addObj(*enemy, true);
	}

	basicMap.addObj(framerateText, false);
	handler.setMap(&basicMap);

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	bool enableDisableBlend{ false };
	bool isFalse{ false };

	Camera test{}

	while (!input::keyExit)
	{	
#ifdef _DEBUG
		if (input::keySPACE) {
			DebugSettings::I_SHOWCOLLISIONBOXES = !DebugSettings::I_SHOWCOLLISIONBOXES;
			input::keySPACE = false;
			I_WIN.setWindowFullScreen();
		}
#endif
		if (input::keyE) {
			I_WIN.exitFullScreen();
		}

		glClear(GL_COLOR_BUFFER_BIT);
		input::processInput();
		framerate();

		handler.updateObjects();
		handler.renderObjects();
		I_WIN.swapBuffers();
	}

	Textures::deleteAllTextures();
	return 0;
}




