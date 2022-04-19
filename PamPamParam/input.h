#pragma once
#include "utils.h"
#include "window.h"
#include <SDL_events.h>
#include <map>
#include "mouse.h"
#include "camera.h"

namespace Handler {
	inline Camera cam{ 0,0, 1000 };
}

namespace Input {

	inline bool keyW{ false };
	inline bool keyS{ false };
	inline bool keyA{ false };
	inline bool keyD{ false };
	inline bool keyE{ false };
	inline bool keySPACE{ false };
	inline bool keyESC{ false };

	inline bool keyUP{ false };
	inline bool keyDOWN{ false };
	inline bool keyLEFT{ false };
	inline bool keyRIGHT{ false };

	inline bool keyF1{ false };
	inline bool keyF2{ false };
	inline bool keyF3{ false };
	inline bool keyF4{ false };
	inline bool keyF5{ false };
	inline bool keyF6{ false };
	inline bool keyF7{ false };
	inline bool keyF8{ false };
	inline bool keyF9{ false };
	inline bool keyF10{ false };
	inline bool keyF11{ false };
	inline bool keyF12{ false };
	
	inline bool keyExit{ false };

	inline Mouse mouse{ };

	void processInput();

}
