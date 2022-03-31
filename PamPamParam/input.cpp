#include "input.h"

namespace input {
	void processInput() {
		SDL_Event e;
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT || keyESC) {
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
				case SDLK_e:
					keyE = true;
					break;
				case SDLK_ESCAPE:
					keyESC = true;
					break;
				case SDLK_SPACE:
					keySPACE = true;
					break;
				case SDLK_UP:
					keyUP = true;
					break;
				case SDLK_RIGHT:
					keyRIGHT = true;
					break;
				case SDLK_DOWN:
					keyDOWN = true;
					break;
				case SDLK_LEFT:
					keyLEFT = true;
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
				case SDLK_e:
					keyE = false;
					break;
				case SDLK_ESCAPE:
					keyESC = false;
					break;
				case SDLK_SPACE:
					keySPACE = false;
					break;
				case SDLK_UP:
					keyUP = false;
					break;
				case SDLK_RIGHT:
					keyRIGHT = false;
					break;
				case SDLK_DOWN:
					keyDOWN = false;
					break;
				case SDLK_LEFT:
					keyLEFT = false;
					break;
				default:
					break;
				}
			}
			if (e.type == SDL_WINDOWEVENT) {
				switch (e.window.event) {
				case SDL_WINDOWEVENT_SIZE_CHANGED:
				case SDL_WINDOWEVENT_RESIZED:
					I_WIN.updateSize();
					break;
				}

			}
		}
	}
}