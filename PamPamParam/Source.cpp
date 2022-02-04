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
	Text framerateText{ 800, 800,20,20, Colors::black, "FPS" , Textures::I_FONT, 0};
	void framerate() {
		double currentTime = SDL_GetTicks();
		frameCount++;
		// If a second has passed.
		if (currentTime - previousTime >= 1000)
		{
			framerateText.setContent(std::to_string(frameCount) + " FPS");
			std::cout << frameCount << '\n';
			frameCount = 0;
			previousTime = currentTime;
		}
	}

}

int main(int argc, char* argv[])
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	handler.addObj(framerateText);
	
	Animation t{ Textures::animations::animationVecDog, 8 };
	std::map<std::string, Animation> m{ };
	m[Textures::animations::animationString] = t;

	Entity player{ -500,-500, 160,80 , Textures::animations::animationVecDog[0], &m};
	BasicBlock block{ 200,200, 100,100, Textures::splitTest };

	handler.addObj(block);
	handler.addObj(player);

	for (size_t i{}; i < 3000; i++) {
		Entity* t{ new Entity{-500,-500, 160,80 , Textures::animations::animationVecDog[0]} };
		handler.addObj(*t);
	}

	float speed{ 5 };
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	while (true)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		input::processInput();
		if (input::keyW) {
			player.setY(player.y() + speed);
		}
		else if (input::keyS) {
			player.setY(player.y() - speed);
		}
		if (input::keyD) {
			player.setX(player.x() + speed);
		}
		else if (input::keyA) {
			player.setX(player.x() - speed);
		}
		if (input::keyExit) {
			break;
		}
		framerate();

		handler.updateObjects();
		handler.renderObjects();
		I_WIN.swapBuffers();
	}

	Textures::deleteAllTextures();
	return 0;
}




