#pragma once
#include "window.h"
#include "object.h"
#include "utils.h"
#include "Batch.h"
#include "font.h"
#include "shaders.h"
#include "textureArray.h"
#include "initTextures.h"


class Handler {
private:
	std::vector<Object*> m_objects;
	std::vector<Object*> m_texts;
	Batch m_charBatch{ Textures::I_FONT.atlas(), Shaders::I_charShader };
	Batch m_basicBatch{ Textures::I_ALLTEXTURES, Shaders::I_basicShader };


protected:
public:
	Handler();
	~Handler();

	void addObj(Object& object) {
		m_objects.push_back(&object);
	}

	void addText(Object& text) {
		m_texts.push_back(&text);
	}


	void renderObjects();
	void updateObjects();


#ifdef _DEBUG
private:
	static inline ObjectsCount mS_objectsCount{};

#endif
};