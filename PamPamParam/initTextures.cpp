#include "initTextures.h"

namespace Textures {

	// call once and must be deleted once program ends
	int initAllTextures() {
		const int unpack_alignment{ 4 };
		std::vector<Image> images{};
		images.push_back(image::loadImage(Constants::textures::player_pngPath, string::player, unpack_alignment));
		images.push_back(image::loadImage(Constants::textures::death_pngPath, string::death, unpack_alignment));
		images.push_back(image::loadImage(Constants::textures::death2_pngPath, string::death2, unpack_alignment));
		images.push_back(image::loadImage(Constants::textures::death3_pngPath, string::death3, unpack_alignment));
		images.push_back(image::loadImage(Constants::textures::splitTest_pngPath, string::splitTest, unpack_alignment));
		images.push_back(image::loadImage(Constants::textures::collisionBox_pngPath, string::collisionBox, unpack_alignment));
		images.push_back(image::loadImage("E:\\Andrei\\andrei\\PamPamParam\\PamPamParam\\textures\\craftpix-net-672711-free-street-animal-pixel-art-asset-pack\\1 Dog\\Walk.png", "dogwalk", unpack_alignment, 6, 0));
		images.push_back(image::loadImage("E:\\Andrei\\andrei\\PamPamParam\\PamPamParam\\textures\\craftpix-net-672711-free-street-animal-pixel-art-asset-pack\\1 Dog\\Idle.png", "dogidle", unpack_alignment, 4, 0));


		I_ALLTEXTURES = new TextureArray{ 2048, 2048, GL_CLAMP_TO_EDGE,
					  GL_CLAMP_TO_EDGE,
					  GL_NEAREST,
					  GL_NEAREST, GL_RGBA, images, GL_RGBA, GL_UNSIGNED_BYTE, true,unpack_alignment };

		Textures::player = &I_ALLTEXTURES->getTexture(Textures::string::player);
		Textures::death = &I_ALLTEXTURES->getTexture(Textures::string::death);
		Textures::death2 = &I_ALLTEXTURES->getTexture(Textures::string::death2);
		Textures::death3 = &I_ALLTEXTURES->getTexture(Textures::string::death3);
		Textures::splitTest = &I_ALLTEXTURES->getTexture(Textures::string::splitTest);
		Textures::collisionBox = &I_ALLTEXTURES->getTexture(Textures::string::collisionBox);

		animations::animationVecDogWalkingRight = std::vector<const Texture*>{ 
		&I_ALLTEXTURES->getTexture(splitTextureName("dogwalk", 1,1)),
		&I_ALLTEXTURES->getTexture(splitTextureName("dogwalk", 1,2)) ,
		&I_ALLTEXTURES->getTexture(splitTextureName("dogwalk", 1,3)) ,
		&I_ALLTEXTURES->getTexture(splitTextureName("dogwalk", 1,4)) ,
		&I_ALLTEXTURES->getTexture(splitTextureName("dogwalk", 1,5)) ,
		&I_ALLTEXTURES->getTexture(splitTextureName("dogwalk", 1,6)) };

		animations::animationVecDogWalkingLeft = std::vector<const Texture*>{
		I_ALLTEXTURES->getTexture(splitTextureName("dogwalk", 1,1)).reverseXAxis(),
		I_ALLTEXTURES->getTexture(splitTextureName("dogwalk", 1,2)).reverseXAxis(),
		I_ALLTEXTURES->getTexture(splitTextureName("dogwalk", 1,3)).reverseXAxis(),
		I_ALLTEXTURES->getTexture(splitTextureName("dogwalk", 1,4)).reverseXAxis(),
		I_ALLTEXTURES->getTexture(splitTextureName("dogwalk", 1,5)).reverseXAxis(),
		I_ALLTEXTURES->getTexture(splitTextureName("dogwalk", 1,6)).reverseXAxis() };

		animations::animationVecDogIdleRight = std::vector<const Texture*>{
		&I_ALLTEXTURES->getTexture(splitTextureName("dogidle", 1,1)),
		&I_ALLTEXTURES->getTexture(splitTextureName("dogidle", 1,2)),
		&I_ALLTEXTURES->getTexture(splitTextureName("dogidle", 1,3)),
		&I_ALLTEXTURES->getTexture(splitTextureName("dogidle", 1,4)), };

		animations::animationVecDogIdleLeft = std::vector<const Texture*>{
		I_ALLTEXTURES->getTexture(splitTextureName("dogidle", 1,1)).reverseXAxis(),
		I_ALLTEXTURES->getTexture(splitTextureName("dogidle", 1,2)).reverseXAxis(),
		I_ALLTEXTURES->getTexture(splitTextureName("dogidle", 1,3)).reverseXAxis(),
		I_ALLTEXTURES->getTexture(splitTextureName("dogidle", 1,4)).reverseXAxis(), };

		return 1;
	}

	void deleteAllTextures() {
		delete I_ALLTEXTURES;
		I_ALLTEXTURES = nullptr;
		for (auto& tex : animations::animationVecDogWalkingLeft) {
			delete tex;
		}
		for (auto& tex : animations::animationVecDogIdleLeft) {
			delete tex;
		}
	}
}

namespace {
	int init_textures{ Textures::initAllTextures() };
}