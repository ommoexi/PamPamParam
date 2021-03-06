#pragma once
#include "window.h"
#include "object.h"
#include "utils.h"
#include "Batch.h"
#include "font.h"
#include "shaders.h"
#include "textureArray.h"
#include "initTextures.h"
#include "entity.h"
#include "basicBlock.h"
#include "text.h"
#include <array>
#include "map.h"
#include "hud.h"
#include "input.h"

namespace Handler {

#ifdef _DEBUG
	inline CollisionBox* playerHitCollision{ new CollisionBox{30,20,155,180, Textures::collisionBox,true, Colors::red } };
#else 
	inline CollisionBox* playerHitCollision{ new CollisionBox{30,20,155,180 } };
#endif

	inline Player& player{ *(new Player{0,0 , 200, 200, Stats{12,100, 1}, *playerHitCollision}) };
	inline Map map{ Point{-50000,-50000}, Point{50000, 50000}, static_cast<unsigned int>(Constants::windowSizeStretched),
		3,7, &player };

	inline Batch charBatch{ Textures::I_FONT.atlas(), Shaders::I_charShader, 15000 };
	inline Batch basicBatch{ Textures::I_ALLTEXTURES, Shaders::I_basicShader, 15000 };

	inline Hud hud{};

}


void renderObjects();
void updateObjects();
