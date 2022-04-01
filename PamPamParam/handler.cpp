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

	m_hud.addToBatch(m_charBatch);

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
	m_hud.update();

	// de modificat m_cam mai tarziu
	Player& player{ m_map->mainPlayer() };
	m_cam.setX(player.x() - Constants::widthStretch + player.width() / 2);
	m_cam.setY(player.y() - Constants::heightStretch / 1.5);
	Shaders::I_basicShader.bind();
	Shaders::I_basicShader.setMat3(Constants::Uniforms::camera, m_cam.transform());
	Shaders::I_charShader.bind();
	Shaders::I_charShader.setMat3(Constants::Uniforms::camera, m_cam.transform());
}