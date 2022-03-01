#include "handler.h"
Handler::Handler() {
#ifdef _DEBUG
	DEBUG_CONSTRUCTOR_OBJ(this, Source_Files::handler_cpp, &mS_objectsCount);
#endif
}
Handler::~Handler() {
#ifdef _DEBUG
	DEBUG_DESTRUCTOR_OBJ(this, Source_Files::handler_cpp);
#endif

}

//void Handler::addObj(Entity& entity, const bool& useDeleteWhenRemoved) {
//	m_entities.push_back(&entity);
//	entity.setUseDeleteWhenRemoved(useDeleteWhenRemoved);
//}
//void Handler::addObj(BasicBlock& basicBlock, const bool& useDeleteWhenRemoved) {
//	m_basicBlocks.push_back(&basicBlock);
//	basicBlock.setUseDeleteWhenRemoved(useDeleteWhenRemoved);
//}
//
//void Handler::addObj(Text& text, const bool& useDeleteWhenRemoved) {
//	m_texts.push_back(&text);
//	text.setUseDeleteWhenRemoved(useDeleteWhenRemoved);
//}
//
//void Handler::removeObj(Entity& entity) {
//	if (entity.useDeleteWhenRemoved()) {
//		delete& entity;
//	}
//	auto it = std::find(m_entities.begin(), m_entities.end(), &entity);
//	if (it != m_entities.end()) {
//		m_entities.erase(it);
//	}
//#ifdef _DEBUG
//	else {
//		debugMessage("Remove entity not found!\n");
//	}
//#endif
//
//}
//void Handler::removeObj(BasicBlock& basicBlock) {
//	if (basicBlock.useDeleteWhenRemoved()) {
//		delete& basicBlock;
//	}
//	auto it = std::find(m_basicBlocks.begin(), m_basicBlocks.end(), &basicBlock);
//	if (it != m_basicBlocks.end()) {
//		m_basicBlocks.erase(it);
//	}
//#ifdef _DEBUG
//	else {
//		debugMessage("Remove basicBlock not found!\n");
//	}
//#endif
//}
//void Handler::removeObj(Text& text) {
//	if (text.useDeleteWhenRemoved()) {
//		delete& text;
//	}
//	auto it = std::find(m_texts.begin(), m_texts.end(), &text);
//	if (it != m_texts.end()) {
//		m_texts.erase(it);
//	}
//#ifdef _DEBUG
//	else {
//		debugMessage("Remove text not found!\n");
//	}
//#endif
//}


// de modificat sistemul cu setAllDataVoid dar nu acum
void Handler::renderObjects() {

	m_charBatch.setAllDataVoid();
	m_basicBatch.setAllDataVoid();

	auto& renderVectors{ m_map->renderVectors() };

	int textOffset{};
	m_charBatch.bindBuffer();
	for (auto& texts : renderVectors.texts) {
		for (auto& text : *texts) {
			const Mesh& textMesh{ text->mesh() };
			int verticesSize{ static_cast<int>(textMesh.size()) };
			m_charBatch.setSubData(textOffset, textMesh);
			textOffset += verticesSize;
		}
	}

	int objectOffset{};
	m_basicBatch.bindBuffer();
	for (auto& entities : renderVectors.entities) {
		for (auto& entity : *entities) {
			const Mesh& entityMesh{ entity->mesh() };
			int verticesSize{ static_cast<int>(entityMesh.size()) };
			m_basicBatch.setSubData(objectOffset, entityMesh);
			objectOffset += verticesSize;
		}
	}

	for (auto& basicBlocks : renderVectors.basicBlocks) {
		for (auto& basicBlock : *basicBlocks) {
			const Mesh& basicBlockMesh{ basicBlock->mesh() };
			int verticesSize{ static_cast<int>(basicBlockMesh.size()) };
			m_basicBatch.setSubData(objectOffset, basicBlockMesh);
			objectOffset += verticesSize;
		}
	}

	m_charBatch.draw();
	m_basicBatch.draw();
}

void Handler::updateObjects() {
	m_map->update();

}