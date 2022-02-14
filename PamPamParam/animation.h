#pragma once
#include "utils.h"
#include "textureArray.h"

class Animation {
private:
	const std::vector<const Texture*>* m_textures{}; // shared
	mutable int m_currentIndex{} ;
	unsigned int m_framersPerTexture{};
	mutable unsigned int m_timer{ m_framersPerTexture };

public:

	Animation(const std::vector<const Texture*>& textures, const unsigned int& framesPerTexture);
	Animation();
	~Animation();
	Animation& operator=(const Animation& animation) = default;
	Animation(const Animation& animation);

	const unsigned int& framesPerTextures() const {
		return m_framersPerTexture;
	}
	Animation& setFramesPerTexture(const unsigned int& value) {
		m_framersPerTexture = value;
		return *this;
	}

	const Texture& nextTexture() const;
	const Texture& currentTexture() const;


#ifdef _DEBUG
private:
	static inline ObjectsCount mS_objectsCount{};

#endif
};
