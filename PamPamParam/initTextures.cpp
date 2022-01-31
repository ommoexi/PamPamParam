#include "initTextures.h"

namespace Textures {
	
	// call once and must be deleted once program ends
	int initAllTextures() {
		const int unpack_alignment{ 4 };
		std::vector<Image> images{};
		images.push_back(image::loadImage(Constants::textures::player_pngPath, string::player, unpack_alignment));
		images.push_back(image::loadImage(Constants::textures::death_pngPath, string::death, unpack_alignment));

		I_ALLTEXTURES = new TextureArray{ 1024, 1024, GL_CLAMP_TO_EDGE,
					  GL_CLAMP_TO_EDGE,
					  GL_LINEAR,
					  GL_LINEAR, GL_RGBA, images, GL_RGBA, GL_UNSIGNED_BYTE, true,unpack_alignment };

		Textures::player = &I_ALLTEXTURES->getTexture(Textures::string::player);
		Textures::death = &I_ALLTEXTURES->getTexture(Textures::string::death);

		Textures::hidden::animation = std::vector<Texture*>{ Textures::player, Textures::death };
		Textures::animation = Animation{ Textures::hidden::animation, 10 };
	
		
		
		return 1;
	}

	void deleteAllTextures() {
		delete I_ALLTEXTURES;
		I_ALLTEXTURES = nullptr;
	}
}

namespace {
	int init_textures{ Textures::initAllTextures() };
}