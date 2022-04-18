#pragma once
#include "text.h"

class Framerate : public Text {
private:
	double m_previousTime = SDL_GetTicks();
	int m_frameCount = 0;
public:
	Framerate(const float& x, const float& y, const float& letterWidth, const float& letterHeight,
		const Constants::vec4& color, std::string_view content, const Font& font,
		const float& letterSpacingHorizontal, const bool& isAffectedByCamera = false,
		const float& maxPixelWidth = std::numeric_limits<float>::max(), const float& letterSpacingVertical = 0);
	virtual ~Framerate();

	void update();

#ifdef _DEBUG
private:
	static inline ObjectsCount mS_objectsCount{};

#endif
};