#pragma once
#include "utils.h"
#include "textureArray.h"
#include "font.h"
#include "animation.h"

namespace Textures {

	namespace string {
		inline const std::string player{ "player" };
		inline const std::string death{ "death" };
		inline const std::string death2{ "death 2" };
		inline const std::string death3{ "death 3" };
		inline const std::string splitTest{ "splitTest" };
		inline const std::string collisionBox{ "collisionBox" };
	}

	inline Font I_FONT{ Constants::fonts::gameFont, 64,64 };

	int initAllTextures();
	void deleteAllTextures();

	inline TextureArray* I_ALLTEXTURES;

	inline const Texture* player{};
	inline const Texture* death{};
	inline const Texture* death2{};
	inline const Texture* death3{};
	inline const Texture* splitTest{};
	inline const Texture* collisionBox{};

	namespace animationV {
		inline std::vector<const Texture*> dogWalkingRight{};
		inline std::vector<const Texture*> dogWalkingLeft{};
		inline std::vector<const Texture*> dogIdleRight{};
		inline std::vector<const Texture*> dogIdleLeft{};
	}

	namespace animations{
		inline Animation dogWalkingRight{ animationV::dogWalkingRight, 12 };
		inline Animation dogWalkingLeft{ animationV::dogWalkingLeft, 12 };
		inline Animation dogIdleRight{ animationV::dogIdleRight, 12 };
		inline Animation dogIdleLeft{ animationV::dogIdleLeft, 12 };
	}


}