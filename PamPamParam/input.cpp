#include "input.h"

namespace input {
	void processInput() {
		SDL_Event e;
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				keyExit = true;
			}
			else if (e.type == SDL_KEYDOWN)
			{
				//Select surfaces based on key press
				switch (e.key.keysym.sym)
				{

				case SDLK_w:
					keyW = true;
					break;

				case SDLK_d:
					keyD = true;
					break;

				case SDLK_s:
					keyS = true;
					break;

				case SDLK_a:
					keyA = true;
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
				case SDLK_w:
					keyW = false;
					break;
				case SDLK_d:
					keyD = false;
					break;

				case SDLK_s:
					keyS = false;
					break;

				case SDLK_a:
					keyA = false;
					break;

				default:
					break;
				}
			}
		}
	}
}