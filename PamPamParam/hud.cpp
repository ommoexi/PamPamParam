#include "hud.h"

Hud::Hud() {
#ifdef _DEBUG
	DEBUG_CONSTRUCTOR_OBJ(this, Source_Files::hud_cpp, &mS_objectsCount);
#endif
	m_framerate = new Framerate{0,0,20,20, Colors::black, "FPS" , Textures::I_FONT, 0, false } ;
	m_framerate->setX(Constants::width - m_framerate->getPixelWidthFirstRow() - 10);
	m_framerate->setY(Constants::height - m_framerate->getPixelHeightFirstRow() - 10);

}
Hud::~Hud() {
#ifdef _DEBUG
	if (m_debugDestructor) {
		DEBUG_DESTRUCTOR_OBJ(this, Source_Files::hud_cpp);
	}
#endif

	for (size_t i{}; i < m_texts.size(); i++) {
		Text*& text{ m_texts[i] };
		if (text->useDeleteWhenRemoved()) {
			delete text;
		}
	}
	delete m_framerate;
}

void Hud::addObj(Text& text, const bool& useDeleteWhenRemoved) {
	text.setUseDeleteWhenRemoved(useDeleteWhenRemoved);
	m_texts.push_back(&text);
}

void Hud::removeObj(Text& text) {
	auto it = find(m_texts.begin(), m_texts.end(), &text);

	// If element was found
	if (it != m_texts.end())
	{
		if (text.useDeleteWhenRemoved()) {
			delete& text;
		}
		m_texts.erase(it);
	}
#ifdef _DEBUG
	else {
		debugMessage("HUD TEXT NOT FOUND \n");
	}
#endif
}

void Hud::update() {
	m_framerate->update();
}

void Hud::addToBatch(Batch& batch) {
	m_framerate->updateGraphics();
	batch.setSubData(m_framerate->mesh());
}