#pragma once
#include "utils.h"
#include "textureArray.h"
#include "font.h"
#include "animation.h"

namespace Textures {

	namespace string {
		inline const std::string player{ "player" };
		inline const std::string death{ "death" };
		inline const std::string splitTest{ "splitTest" };
	}

	inline Font I_FONT{ Constants::fonts::gameFont, 524,524 };

	int initAllTextures();
	// deletes animations as well from allTextures
	void deleteAllTextures();

	inline TextureArray* I_ALLTEXTURES;

	inline const Texture* player{};
	inline const Texture* death{};
	inline const Texture* splitTest{};

	namespace animations {
		inline std::vector<const Texture*> animationVecDog{};
		inline std::string animationString{ "animation" };
	}


}