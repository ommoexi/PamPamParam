#pragma once
#include "utils.h"
#include "text.h"
#include "framerate.h"
#include "initTextures.h"
#include "Batch.h"
#include "background.h"

class Hud {
private:
	std::vector<Text*> m_texts; // unique only
	Framerate* m_framerate; // unique 
	Background* m_background; // unique
public:
	Hud();
	virtual ~Hud();

	std::vector<Text*>& texts() {
		return m_texts;
	}
	// add only free store text only!!!!!!!
	void addObj(Text& text);
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