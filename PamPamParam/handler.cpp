#include "handler.h"
Handler::Handler() {
#ifdef _DEBUG
	DEBUG_CONSTRUCTOR_OBJ(this, Source_Files::handler_cpp, &mS_objectsCount);
#endif
	m_charBatch.setVBOSize(5000);
	m_basicBatch.setVBOSize(5000);

}
Handler::~Handler() {
#ifdef _DEBUG
	DEBUG_DESTRUCTOR_OBJ(this, Source_Files::handler_cpp);
#endif

}

void Handler::renderObjects() {

	int textOffset{};
	m_charBatch.bindBuffer();
	for (auto& text : m_texts) {
		const Mesh& textMesh{ text->mesh() };
		int verticesSize{ static_cast<int>(textMesh.size()) };
		m_charBatch.setSubData(textOffset, textMesh);
		textOffset += verticesSize;

	}

	int objectOffset{};
	m_basicBatch.bindBuffer();
	for (auto& entity : m_entities) {
		const Mesh& entityMesh{ entity->mesh() };
		int verticesSize{ static_cast<int>(entityMesh.size()) };
		m_basicBatch.setSubData(objectOffset, entityMesh);
		objectOffset += verticesSize;
	}
	for (auto& basicBloc : m_basicBlocks) {
		const Mesh& basicBlockMesh{ basicBloc->mesh() };
		int verticesSize{ static_cast<int>(basicBlockMesh.size()) };
		m_basicBatch.setSubData(objectOffset, basicBlockMesh);
		objectOffset += verticesSize;
	}
	m_charBatch.draw();
	m_basicBatch.draw();
}

void Handler::updateObjects() {
	for (auto& entity : m_entities) {
		entity->update(m_entities, m_basicBlocks);
	}
}