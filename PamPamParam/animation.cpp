#include "animation.h"

Animation::Animation(const std::vector<const Texture*>& textures, const unsigned int& framesPerTexture) : m_textures{ &textures },
m_framersPerTexture{ framesPerTexture } {
#ifdef _DEBUG
	DEBUG_CONSTRUCTOR_OBJ(this, Source_Files::animation_cpp, &mS_objectsCount);
#endif
}

const Texture& Animation::nextTexture() const {
	m_timer--;
	if (m_timer == 0) {
		m_timer = m_framersPerTexture;
		m_currentIndex++;
		if (m_currentIndex >= m_textures->size()) {
			m_currentIndex = 0;
		}
		return *(*m_textures)[m_currentIndex];


	}
	return *(*m_textures)[m_currentIndex];
}

Animation::Animation() {
#ifdef _DEBUG
	DEBUG_CONSTRUCTOR_OBJ(this, Source_Files::animation_cpp, &mS_objectsCount);
#endif

}

Animation::Animation(const Animation& animation) : m_textures{ animation.m_textures }, m_currentIndex{ animation.m_currentIndex },
m_framersPerTexture{ animation.m_framersPerTexture }, m_timer{ m_framersPerTexture }{
#ifdef _DEBUG
	DEBUG_CONSTRUCTOR_OBJ(this, Source_Files::animation_cpp, &mS_objectsCount);
#endif
}

Animation::~Animation() {
#ifdef _DEBUG
	DEBUG_DESTRUCTOR_OBJ(this, Source_Files::animation_cpp);
#endif
}