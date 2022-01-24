#include "initTextures.h"

namespace Textures {
	
	// call once and must be deleted once program ends
	int initAllTextures() {
		std::vector<Image> images{};
		images.push_back(image::loadImage(Constants::textures::player_pngPath, string::player));

		I_ALLTEXTURES = new TextureArray{ 1024, 1024, GL_CLAMP_TO_EDGE,
					  GL_CLAMP_TO_EDGE,
					  GL_LINEAR,
					  GL_LINEAR, GL_RGBA, images, GL_RGBA, GL_UNSIGNED_BYTE, true };

		Textures::player = &I_ALLTEXTURES->getTexture(Textures::string::player);

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