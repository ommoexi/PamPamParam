#include "animation.h"

Animation::Animation(const std::vector<Texture*>& textures) : m_Textures{ textures } {
#ifdef _DEBUG
	DEBUG_CONSTRUCTOR_OBJ(this, Source_Files::animation_cpp, &mS_objectsCount);
#endif
}

const Texture& Animation::nextTexture() const {
	m_currentIndex++;
	try {
		return *m_Textures[m_currentIndex];
	}
	catch (...) {
		m_currentIndex = 0;
	}
	return *m_Textures[m_currentIndex];
}

Animation::~Animation() {
#ifdef _DEBUG
	DEBUG_DESTRUCTOR_OBJ(this, Source_Files::animation_cpp);
#endif
}