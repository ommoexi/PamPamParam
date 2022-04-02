#pragma once
#include "utils.h"
#include "window.h"
#include <SDL_events.h>
#include <map>

namespace input {

	// these keys can be modified outside processInput but i advise not to
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

	void processInput();
}