#pragma once
#include "utils.h"
#include "textureArray.h"
#include "font.h"

namespace Textures {

	namespace string {
		inline const std::string player{ "player" };
	}
	
	inline Font I_FONT{ Constants::fonts::gameFont, 524,524 };

	int initAllTextures();
	void deleteAllTextures();
	
	inline TextureArray* I_ALLTEXTURES;

	inline const Texture* player{};


}