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
	Text framerateText{ Constants::widthStretch - framerateText.getPixelWidthFirstRow() - 10, 
		Constants::heightStretch - framerateText.getPixelHeightFirstRow() -10,
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
			framerateText.setX(Constants::widthStretch - framerateText.getPixelWidthFirstRow() -10);
			framerateText.setY(Constants::heightStretch - framerateText.getPixelHeightFirstRow() - 10);
		}
	}

}

#include "map.h"

int main(int argc, char* argv[])
{

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	handler.addObj(framerateText, false);
	
	Animation standingAnimation{ Textures::animations::animationVecDog, 8 };

	Player player{ 0,0, 500,500, standingAnimation};

	handler.addObj(player, false);

	Map test{ Point{-800,-800}, Point{800,800}, 100 };

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




