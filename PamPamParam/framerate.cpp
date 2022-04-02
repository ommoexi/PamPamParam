#include "framerate.h"

Framerate::Framerate(const float& x, const float& y, const float& letterWidth, const float& letterHeight,
	const Constants::vec4& color, std::string_view content, const Font& font, const float& letterSpacingHorizontal,
	const bool& isAffectedByCamera, const float& maxPixelWidth, const float& letterSpacingVertical) :
	Text{ x,y, letterWidth, letterHeight, color, content, font, letterSpacingHorizontal, isAffectedByCamera,
maxPixelWidth,letterSpacingHorizontal } {
#ifdef _DEBUG
	DEBUG_CONSTRUCTOR_OBJ(this, Source_Files::framerate_cpp, &mS_objectsCount);
#endif

}
Framerate::~Framerate() {

#ifdef _DEBUG
	if (debugDestructor()) {
		DEBUG_DESTRUCTOR_OBJ(this, Source_Files::framerate_cpp);
		setDebugDestructor(false);
	}
#endif
}

void Framerate::update() {
	double currentTime = SDL_GetTicks();
	m_frameCount++;
	// If a second has passed.
	if (currentTime - m_previousTime >= 1000)
	{
		setContent(std::to_string(m_frameCount) + " FPS");
		//std::cout << frameCount << '\n';
		m_frameCount = 0;
		m_previousTime = currentTime;
		setX(Constants::width - getPixelWidthFirstRow() - 10);
		setY(Constants::height - getPixelHeightFirstRow() - 10);
	}
}