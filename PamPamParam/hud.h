#pragma once
#include "utils.h"
#include "text.h"
#include "framerate.h"
#include "initTextures.h"
#include "Batch.h"
#include "rectangle.h"

class Hud {
private:
	std::vector<Text*> m_texts;
	Framerate* m_framerate;
	Rectangle* m_background;
public:
	Hud();
	virtual ~Hud();

	std::vector<Text*>& texts() {
		return m_texts;
	}

	void addObj(Text& text, const bool& useDeleteWhenRemoved);
	void removeObj(Text& text);
	void update();

	void addToTextBatch(Batch& batch);
	void addToBasicBatch(Batch& batch);

#ifdef _DEBUG
private:
	static inline ObjectsCount mS_objectsCount{};
	bool m_debugDestructor{ true }; // no deletion twice
#endif

};