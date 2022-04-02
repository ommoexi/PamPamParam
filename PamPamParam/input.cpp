#include "input.h"

namespace Input {
	void processInput() {
		SDL_Event e;
		int mouseX{};
		int mouseY{};
		SDL_GetMouseState(&mouseX, &mouseY);
		mouse.setX(I_WIN.transformXMouseToWidthStretch(static_cast<float>(mouseX)));
		mouse.setY(I_WIN.transformYMouseToHeightStretch(static_cast<float>(mouseY)));

		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT || keyESC) {
				keyExit = true;
			}
			if (e.type == SDL_KEYDOWN)
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
				case SDLK_F1:
					keyF1 = true;
					break;
				case SDLK_F2:
					keyF2 = true;
					break;
				case SDLK_F3:
					keyF3 = true;
					break;
				case SDLK_F4:
					keyF4 = true;
					break;
				case SDLK_F5:
					keyF5 = true;
					break;
				case SDLK_F6:
					keyF6 = true;
					break;
				case SDLK_F7:
					keyF7 = true;
					break;
				case SDLK_F8:
					keyF8 = true;
					break;
				case SDLK_F9:
					keyF9 = true;
					break;
				case SDLK_F10:
					keyF10 = true;
					break;
				case SDLK_F11:
					keyF11 = true;
					break;
				case SDLK_F12:
					keyF12 = true;
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
				case SDLK_F1:
					keyF1 = false;
					break;
				case SDLK_F2:
					keyF2 = false;
					break;
				case SDLK_F3:
					keyF3 = false;
					break;
				case SDLK_F4:
					keyF4 = false;
					break;
				case SDLK_F5:
					keyF5 = false;
					break;
				case SDLK_F6:
					keyF6 = false;
					break;
				case SDLK_F7:
					keyF7 = false;
					break;
				case SDLK_F8:
					keyF8 = false;
					break;
				case SDLK_F9:
					keyF9 = false;
					break;
				case SDLK_F10:
					keyF10 = false;
					break;
				case SDLK_F11:
					keyF11 = false;
					break;
				case SDLK_F12:
					keyF12 = false;
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
			if (e.type == SDL_MOUSEBUTTONDOWN) {
				switch (e.button.button) {
				case SDL_BUTTON_LEFT:
					mouse.setLeftClick(true);
					break;
				case SDL_BUTTON_RIGHT:
					mouse.setRightClick(true);
					break;
				default:
					break;
				}
			}
			if (e.type == SDL_MOUSEBUTTONUP) {
				switch (e.button.button) {
				case SDL_BUTTON_LEFT:
					mouse.setLeftClick(false);
					break;
				case SDL_BUTTON_RIGHT:
					mouse.setRightClick(false);
					break;
				default:
					break;
				}
			}
			
		}
	}

}