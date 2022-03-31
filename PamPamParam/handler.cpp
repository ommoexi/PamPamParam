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

	m_charBatch.bindBuffer();
	for (auto& texts : renderVectors.texts) {
		for (auto& text : *texts) {
			text->updateGraphics();
			m_charBatch.setSubData(text->mesh());
		}
	}

	m_basicBatch.bindBuffer();
	for (auto& entities : renderVectors.entities) {
		for (auto& entity : *entities) {
			entity->updateGraphics();
			m_basicBatch.setSubData(entity->mesh());
#ifdef _DEBUG
			if (DebugSettings::I_SHOWCOLLISIONBOXES) {
				entity->hitCollision().updateGraphics();
				m_basicBatch.setSubData(entity->hitCollision().mesh());
			}
#endif
		}
	}

	for (auto& basicBlocks : renderVectors.basicBlocks) {
		for (auto& basicBlock : *basicBlocks) {
			basicBlock->updateGraphics();
			m_basicBatch.setSubData(basicBlock->mesh());
		}
	}

	m_basicBatch.draw();
	m_charBatch.draw();
}

void Handler::updateObjects() {
	m_map->update();

}