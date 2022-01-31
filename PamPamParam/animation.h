#pragma once
#include "utils.h"
#include "textureArray.h"

class Animation {
private:
	const std::vector<Texture*>* m_textures; // shared
	mutable int m_currentIndex{-1} ;
	int m_framersPerTexture{};
	mutable int m_timer{ m_framersPerTexture };

public:

	Animation(const std::vector<Texture*>& textures, const int& framesPerTexture);
	Animation();
	~Animation();

	const int& framesPerTextures() const {
		return m_framersPerTexture;
	}
	Animation& setFramesPerTexture(const int& value) {
		m_framersPerTexture = value;
		return *this;
	}

	const Texture& nextTexture() const;


#ifdef _DEBUG
private:
	static inline ObjectsCount mS_objectsCount{};

#endif
};
