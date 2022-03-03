#include "initTextures.h"

namespace Textures {
	
	// call once and must be deleted once program ends
	int initAllTextures() {
		const int unpack_alignment{ 4 };
		std::vector<Image> images{};
		images.push_back(image::loadImage(Constants::textures::player_pngPath, string::player, unpack_alignment));
		images.push_back(image::loadImage(Constants::textures::death_pngPath, string::death, unpack_alignment));
		images.push_back(image::loadImage(Constants::textures::splitTest_pngPath, string::splitTest, unpack_alignment));
		images.push_back(image::loadImage(Constants::textures::collisionBox_pngPath, string::collisionBox, unpack_alignment));
		images.push_back(image::loadImage("E:\\Andrei\\andrei\\PamPamParam\\PamPamParam\\textures\\craftpix-net-672711-free-street-animal-pixel-art-asset-pack\\1 Dog\\Walk.png", "dog", unpack_alignment, 6, 0));

		I_ALLTEXTURES = new TextureArray{ 2048, 2048, GL_CLAMP_TO_EDGE,
					  GL_CLAMP_TO_EDGE,
					  GL_NEAREST,
					  GL_NEAREST, GL_RGBA, images, GL_RGBA, GL_UNSIGNED_BYTE, true,unpack_alignment };

		Textures::player = &I_ALLTEXTURES->getTexture(Textures::string::player);
		Textures::death = &I_ALLTEXTURES->getTexture(Textures::string::death);
		Textures::splitTest = &I_ALLTEXTURES->getTexture(Textures::string::splitTest);
		Textures::collisionBox = &I_ALLTEXTURES->getTexture(Textures::string::collisionBox);

		animations::animationVecDog = std::vector<const Texture*>{ &I_ALLTEXTURES->getTexture(splitTextureName("dog", 1,1)),
		& I_ALLTEXTURES->getTexture(splitTextureName("dog", 1,2)) ,
		& I_ALLTEXTURES->getTexture(splitTextureName("dog", 1,3)) ,
		& I_ALLTEXTURES->getTexture(splitTextureName("dog", 1,4)) ,
		& I_ALLTEXTURES->getTexture(splitTextureName("dog", 1,5)) ,
		& I_ALLTEXTURES->getTexture(splitTextureName("dog", 1,6)) };

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