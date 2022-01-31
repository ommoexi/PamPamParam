#include "animation.h"

Animation::Animation(const std::vector<Texture*>& textures, const int& framesPerTexture) : m_textures{ textures },
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
		try {
			return *(*m_textures)[m_currentIndex];
		}
		catch (...) {
			m_currentIndex = 0;
		}
	}
	return *(*m_textures)[m_currentIndex];
}

Animation::Animation() {
#ifdef _DEBUG
	DEBUG_CONSTRUCTOR_OBJ(this, Source_Files::animation_cpp, &mS_objectsCount);
#endif
}

Animation::~Animation() {
#ifdef _DEBUG
	DEBUG_DESTRUCTOR_OBJ(this, Source_Files::animation_cpp);
#endif
}