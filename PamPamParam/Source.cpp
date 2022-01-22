#define STB_IMAGE_IMPLEMENTATION
#include "utils.h"
#include "window.h"
#include "textureArray.h"
#include "constants.h"
#include "text.h"
#include "rectangle.h"
#include "handler.h"
#include "player.h"
#include "Batch.h"
#include "shaders.h"

bool processInput();

namespace {
	double previousTime = SDL_GetTicks();
	Handler handler{};
	int frameCount = 0;
	Text framerateText{ 800, 800,20,20, Colors::black, "FPS" , handler.font(), 0};
	bool keys[6]{/*up right down left* left right*/ };
	void framerate() {
		double currentTime = SDL_GetTicks();
		frameCount++;
		// If a second has passed.
		if (currentTime - previousTime >= 1000)
		{
			framerateText.setContent(std::to_string(frameCount) + " FPS");
			frameCount = 0;
			previousTime = currentTime;
			std::cout << framerateText.content() << '\n';
		}
	}


}


int main(int argc, char* argv[])
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	std::vector<Text*> texts{};
	handler.addText(framerateText);
	Text test{ 0, 0, 50,50, Colors::white, "I fucking did it" , handler.font(), 0, 100, 50};

	handler.addText(test);

	for (int i{}; i < 40000; i++) {
		Text* text{ new Text{0, 0, 50,50, Colors::white, "I fucking did it" , handler.font(), 0, 100, 50} };
		handler.addText(*text);
	}

	float speed{ 5 };

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	while (processInput())
	{
		glClear(GL_COLOR_BUFFER_BIT);
		framerate();
		if (keys[0]) {
			framerateText.setY(framerateText.y() + speed);
		}

		else if (keys[2]) {
			framerateText.setY(framerateText.y() - speed);
		}
		if (keys[1]) {
			framerateText.setX(framerateText.x() + speed);
		}
		else if (keys[3]) {
			framerateText.setX(framerateText.x() - speed);
		}

		handler.renderObjects();
		I_WIN.swapBuffers();
	}


	return 0;
}

bool processInput()
{
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		else if (e.type == SDL_KEYDOWN)
		{
			//Select surfaces based on key press
			switch (e.key.keysym.sym)
			{

			case SDLK_UP:
				keys[0] = true;
				break;

			case SDLK_RIGHT:
				keys[1] = true;
				break;

			case SDLK_DOWN:
				keys[2] = true;
				break;

			case SDLK_LEFT:
				keys[3] = true;
				break;

			default:
				break;
			}
		}
		if (e.type == SDL_KEYUP)
		{
			//Select surfaces based on key press
			switch (e.key.keysym.sym)
			{
			case SDLK_UP:
				keys[0] = false;
				break;
			case SDLK_RIGHT:
				keys[1] = false;
				break;

			case SDLK_DOWN:
				keys[2] = false;
				break;

			case SDLK_LEFT:
				keys[3] = false;
				break;


			default:
				break;
			}
		}
	}
	return true;
}




