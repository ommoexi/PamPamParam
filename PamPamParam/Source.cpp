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
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,1,0,0},
	{0,0,0,0,0,0,0,1,0,0},
	{0,0,0,1,0,0,0,1,0,0},
	{0,0,0,0,1,1,1,0,0,0},
	{0,0,0,0,0,1,1,1,0,0},
	{0,0,0,0,0,0,1,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
};

#include "map.h"

int main(int argc, char* argv[])
{

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	Animation standingAnimation{ Textures::animations::animationVecDog, 8 };
	Rectangle rect{ 20,60,140,25, Textures::collisionBox, Colors::red };
	Rectangle rect2{ 140,0,20,75, Textures::collisionBox, Colors::red };
	Rectangle rect3{ 20,-20,140,25, Textures::collisionBox, Colors::red };
	Rectangle rect4{ 20,0,20,75, Textures::collisionBox, Colors::red };
	Rectangle rect5{ 500,500,40,40, Textures::collisionBox, Colors::red };
	Player player{ 500,500, 160, 80, standingAnimation, 5, rect, rect2, rect3, rect4 ,rect5};
	Map basicMap{ Point{-50000,-50000}, Point{50000, 50000}, static_cast<unsigned int>(Constants::width + Constants::height),
		2,2, &player };
	float y = -200;
	for (auto& f : t) {
		y += 200;
		float x = -200;
		for (auto& in : f) {
			x += 200;
			if (in == 1) {
				BasicBlock* t{ new BasicBlock{x,y, 200, 200, Textures::death} };
				basicMap.addObj(*t, true);
			}
		}
	}

	basicMap.addObj(framerateText, false);
	handler.setMap(&basicMap);

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	while (!input::keyExit)
	{	
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




