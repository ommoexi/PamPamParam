#pragma once
#include "utils.h"
#include "textureArray.h"

class Animation {
private:
	const std::vector<Texture*>& m_Textures;
	mutable int m_currentIndex{-1} ;
public:

	Animation(const std::vector<Texture*>& textures);
	~Animation();

	const Texture& nextTexture() const;

#ifdef _DEBUG
private:
	static inline ObjectsCount mS_objectsCount{};

#endif
};
