#pragma once
#include "window.h"
#include "object.h"
#include "utils.h"
#include "Batch.h"
#include "font.h"
#include "shaders.h"
#include "textureArray.h"
#include "initTextures.h"
#include "entity.h"
#include "basicBlock.h"
#include "text.h"


class Handler {
private:
	//std::vector<Object*> m_objects;
	std::vector<Entity*> m_entities;
	std::vector<BasicBlock*> m_basicBlocks;
	std::vector<Text*> m_texts;
	Batch m_charBatch{ Textures::I_FONT.atlas(), Shaders::I_charShader };
	Batch m_basicBatch{ Textures::I_ALLTEXTURES, Shaders::I_basicShader };


protected:
public:
	Handler(const Handler& handler) = delete;
	Handler& operator=(const Handler& handler) = delete;
	Handler();
	~Handler();

	/*void addObj(Object& object) {
		m_objects.push_back(&object);
	}*/
	void addObj(Entity& entity) {
		m_entities.push_back(&entity);
	}
	void addObj(BasicBlock& basicBlock) {
		m_basicBlocks.push_back(&basicBlock);
	}

	void addObj(Text& text) {
		m_texts.push_back(&text);
	}


	void renderObjects();
	void updateObjects();


#ifdef _DEBUG
private:
	static inline ObjectsCount mS_objectsCount{};

#endif
};