#include "handler.h"
Handler::Handler() {
#ifdef _DEBUG
	DEBUG_CONSTRUCTOR_OBJ(this, Source_Files::handler_cpp, &mS_objectsCount);
#endif
	m_charBatch.setVBOSize(20000);

}
Handler::~Handler() {
#ifdef _DEBUG
	DEBUG_DESTRUCTOR_OBJ(this, Source_Files::handler_cpp);
#endif

}

void Handler::renderObj(const Object& obj, Camera& camera) {
	const float& x_boundary{ I_WIN.normalizeX(obj.x()) };
	const float& y_boundary{ I_WIN.normalizeY(obj.y()) };
	if (x_boundary >= Constants::openglLeft && x_boundary <= Constants::openglRight &&
		y_boundary >= Constants::openglLeft && y_boundary <= Constants::openglRight) {
	}
}

void Handler::renderObjects() {

	int offset{};

	for (auto& text : m_texts) {
		Mesh& textMesh{ text->mesh() };
		int verticesSize{ static_cast<int>(textMesh.size()) };
		m_charBatch.setSubData(offset, textMesh);
		offset += verticesSize;

	}
	m_charBatch.draw();
	m_charBatch.clearVerticesSize();
}

void Handler::removeObject(Object& object) {
	std::vector<Object*>::iterator deleteObj = std::find(m_objects.begin(), m_objects.end(),
		&object);
	if (deleteObj != m_objects.end()) {
		m_objects.erase(deleteObj);
	}
}