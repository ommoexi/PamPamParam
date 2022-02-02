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
	for (auto& object : m_objects) {
		const Mesh& objectMesh{ object->mesh() };
		int verticesSize{ static_cast<int>(objectMesh.size()) };
		m_basicBatch.setSubData(objectOffset, objectMesh);
		objectOffset += verticesSize;
	}
	m_charBatch.draw();
	m_basicBatch.draw();
	m_charBatch.clearVerticesSize();
	m_basicBatch.clearVerticesSize();
}

void Handler::updateObjects() {
	for (auto& obj : m_objects) {
		obj->update(m_objects);
	}
}