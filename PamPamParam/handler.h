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


class Handler {
private:
	/*std::vector<int> m_entitiesAvailableIndexes{};
	std::vector<int> m_basicBlocksAvailableIndexes{};
	std::vector<int> m_textsAvailableIndexes{};

	std::array<Entity*, Constants::handler::entitiesSize> m_entities{};
	std::array<BasicBlock*, Constants::handler::basicBlocksSize> m_basicBlocks{};
	std::array<Text*, Constants::handler::textsSize> m_texts{};*/

	std::vector<Entity*> m_entities{};
	std::vector<BasicBlock*> m_basicBlocks{};
	std::vector<Text*> m_texts{};

	Batch m_charBatch{ Textures::I_FONT.atlas(), Shaders::I_charShader, 5000};
	Batch m_basicBatch{ Textures::I_ALLTEXTURES, Shaders::I_basicShader, 50000 };

protected:
public:
	Handler(const Handler& handler) = delete;
	Handler& operator=(const Handler& handler) = delete;
	Handler();
	~Handler();

	void addObj(Entity& entity, const bool& useDeleteWhenRemoved);
	void addObj(BasicBlock& basicBlock, const bool& useDeleteWhenRemoved);
	void addObj(Text& text, const bool& useDeleteWhenRemoved);

	void removeObj(Entity& entity);
	void removeObj(BasicBlock& basicBlock);
	void removeObj(Text& text);

	void renderObjects();
	void updateObjects();

#ifdef _DEBUG
private:
	static inline ObjectsCount mS_objectsCount{};

#endif
};