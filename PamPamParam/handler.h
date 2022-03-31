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
#include <array>
#include "map.h"
#include "input.h"


class Handler {
private:

	Map* m_map{};

	Batch m_charBatch{ Textures::I_FONT.atlas(), Shaders::I_charShader, 5000 };
	Batch m_basicBatch{ Textures::I_ALLTEXTURES, Shaders::I_basicShader, 15000 };

protected:
public:
	Handler(const Handler& handler) = delete;
	Handler& operator=(const Handler& handler) = delete;
	Handler();
	~Handler();

	/*void addObj(Entity& entity, const bool& useDeleteWhenRemoved);
	void addObj(BasicBlock& basicBlock, const bool& useDeleteWhenRemoved);
	void addObj(Text& text, const bool& useDeleteWhenRemoved);

	void removeObj(Entity& entity);
	void removeObj(BasicBlock& basicBlock);
	void removeObj(Text& text);*/

	void renderObjects();
	void updateObjects();

	void setMap(Map* map) {
		m_map = map;
	}

#ifdef _DEBUG
private:
	static inline ObjectsCount mS_objectsCount{};

#endif
};