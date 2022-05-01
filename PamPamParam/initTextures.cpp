#include "initTextures.h"

void setTexturesFromSplit(std::vector<const Texture*>& animationVector, const std::string& textureName, const int& rows, const int& cols,
	const bool& reverseXAxis = false, const bool& reverseYAxis = false) {
	for (int row{ 1 }; row <= rows; row++) {
		for (int col{ 1 }; col <= cols; col++) {
			if (reverseXAxis && reverseYAxis) {
				animationVector.push_back(Textures::I_ALLTEXTURES->getTexture(splitTextureName(textureName, row, col)).reverseXYAxis());
			}
			else if (reverseXAxis) {
				animationVector.push_back(Textures::I_ALLTEXTURES->getTexture(splitTextureName(textureName, row, col)).reverseXAxis());
			}
			else if (reverseYAxis) {
				animationVector.push_back(Textures::I_ALLTEXTURES->getTexture(splitTextureName(textureName, row, col)).reverseYAxis());
			}
			else {
				animationVector.push_back(&Textures::I_ALLTEXTURES->getTexture(splitTextureName(textureName, row, col)));
			}
		}
	}
}


namespace Textures {

	// call once and must be deleted once program ends
	int initAllTextures() {
		const int unpack_alignment{ 4 };
		std::vector<Image> images{};
		int blueFlower1ImagesSize { image::loadImages(images, Constants::textures::mossyPlantsBlueFlower1Path.generic_string(),
			Textures::string::blueFlower1, unpack_alignment) };
		images.push_back(image::loadImage(Constants::textures::player_pngPath, string::player, unpack_alignment));
		images.push_back(image::loadImage(Constants::textures::grass_pngPath, string::grass, unpack_alignment));
		images.push_back(image::loadImage(Constants::textures::background_pngPath, string::background, unpack_alignment));
		images.push_back(image::loadImage(Constants::textures::grassland_pngPath, string::grassland, unpack_alignment));
		images.push_back(image::loadImage(Constants::textures::tree_pngPath, string::tree, unpack_alignment));
		images.push_back(image::loadImage(Constants::textures::splitTest_pngPath, string::splitTest, unpack_alignment));
		images.push_back(image::loadImage(Constants::textures::collisionBox_pngPath, string::collisionBox, unpack_alignment));
		images.push_back(image::loadImage("E:\\Andrei\\andrei\\PamPamParam\\PamPamParam\\textures\\craftpix-net-672711-free-street-animal-pixel-art-asset-pack\\1 Dog\\Walk.png", "dogwalk", unpack_alignment, 6, 0));
		images.push_back(image::loadImage("E:\\Andrei\\andrei\\PamPamParam\\PamPamParam\\textures\\craftpix-net-672711-free-street-animal-pixel-art-asset-pack\\1 Dog\\Idle.png", "dogidle", unpack_alignment, 4, 0));
		//image::loadImages("test", "test", unpack_alignment);

		I_ALLTEXTURES = new TextureArray{ 2048, 2048, GL_CLAMP_TO_EDGE,
					  GL_CLAMP_TO_EDGE,
					  GL_NEAREST,
					  GL_NEAREST, GL_RGBA, images, GL_RGBA, GL_UNSIGNED_BYTE, true,unpack_alignment };

		Textures::player = &I_ALLTEXTURES->getTexture(Textures::string::player);
		Textures::grass = &I_ALLTEXTURES->getTexture(Textures::string::grass);
		Textures::background = &I_ALLTEXTURES->getTexture(Textures::string::background);
		Textures::grassland = &I_ALLTEXTURES->getTexture(Textures::string::grassland);
		Textures::tree = &I_ALLTEXTURES->getTexture(Textures::string::tree);
		Textures::splitTest = &I_ALLTEXTURES->getTexture(Textures::string::splitTest);
		Textures::collisionBox = &I_ALLTEXTURES->getTexture(Textures::string::collisionBox);

		setTexturesFromSplit(animationV::dogWalkingRight, "dogwalk", 1, 6);
		setTexturesFromSplit(animationV::dogWalkingLeft, "dogwalk", 1, 6, true);
		setTexturesFromSplit(animationV::dogIdleRight, "dogidle", 1, 4);
		setTexturesFromSplit(animationV::dogIdleLeft, "dogidle", 1, 4, true);
		setTexturesFromSplit(animationV::blueFlower1, Textures::string::blueFlower1, 1, blueFlower1ImagesSize);

		return 1;
	}

	void deleteAllTextures() {
		delete I_ALLTEXTURES;
		I_ALLTEXTURES = nullptr;
		for (auto& tex : animationV::dogWalkingLeft) {
			delete tex;
		}
		for (auto& tex : animationV::dogIdleLeft) {
			delete tex;
		}
	}
}

namespace {
	int init_textures{ Textures::initAllTextures() };
}