#pragma once
#include "utils.h"
#include "textureArray.h"
#include "font.h"
#include "animation.h"

namespace Textures {

	namespace string {
		inline const std::string player{ "player" };
		inline const std::string grass{ "grass" };
		inline const std::string background{ "background" };
		inline const std::string grassland{ "grassland" };
		inline const std::string tree{ "tree" };
		inline const std::string blueFlower1{ "blueFlower1" };
		inline const std::string blueFlower2{ "blueFlower2" };
		inline const std::string plant1{ "plant1" };
		inline const std::string plant2{ "plant2" };
		inline const std::string plant3{ "plant3" };
		inline const std::string plant4{ "plant4" };
		inline const std::string plant5{ "plant5" };
		inline const std::string plant6{ "plant6" };
		inline const std::string plant7{ "plant7" };
		inline const std::string splitTest{ "splitTest" };
		inline const std::string collisionBox{ "collisionBox" };
	}

	inline Font I_FONT{ Constants::fonts::gameFont, 64,64 };

	int initAllTextures();
	void deleteAllTextures();

	inline TextureArray* I_ALLTEXTURES;

	inline const Texture* player{};
	inline const Texture* grass{};
	inline const Texture* background{};
	inline const Texture* grassland{};
	inline const Texture* tree{};
	inline const Texture* splitTest{};
	inline const Texture* collisionBox{};

	namespace animationV {
		inline std::vector<const Texture*> dogWalkingRight{};
		inline std::vector<const Texture*> dogWalkingLeft{};
		inline std::vector<const Texture*> dogIdleRight{};
		inline std::vector<const Texture*> dogIdleLeft{};
		inline std::vector<const Texture*> blueFlower1{};
		inline std::vector<const Texture*> blueFlower2{};
		inline std::vector<const Texture*> plant1{};
		inline std::vector<const Texture*> plant2{};
		inline std::vector<const Texture*> plant3{};
		inline std::vector<const Texture*> plant4{};
		inline std::vector<const Texture*> plant5{};
		inline std::vector<const Texture*> plant6{};
		inline std::vector<const Texture*> plant7{};
	}

	namespace animations {
		inline Animation dogWalkingRight{ animationV::dogWalkingRight, 12 };
		inline Animation dogWalkingLeft{ animationV::dogWalkingLeft, 12 };
		inline Animation dogIdleRight{ animationV::dogIdleRight, 12 };
		inline Animation dogIdleLeft{ animationV::dogIdleLeft, 12 };
		inline Animation blueFlower1{ animationV::blueFlower1, 5 };
		inline Animation blueFlower2{ animationV::blueFlower2, 5 };
		inline Animation plant1{ animationV::plant1, 5 };
		inline Animation plant2{ animationV::plant2, 5 };
		inline Animation plant3{ animationV::plant3, 5 };
		inline Animation plant4{ animationV::plant4, 5 };
		inline Animation plant5{ animationV::plant5, 5 };
		inline Animation plant6{ animationV::plant6, 5 };
		inline Animation plant7{ animationV::plant7, 5 };

	}

}