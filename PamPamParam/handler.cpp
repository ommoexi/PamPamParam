#include "handler.h"

void renderObjects() {

	Handler::charBatch.setAllDataVoid();
	Handler::basicBatch.setAllDataVoid();

	auto& renderVectors{ Handler::map.renderVectors() };

	Handler::charBatch.bindBuffer();
	for (auto& texts : renderVectors.texts) {
		for (auto& text : *texts) {
			text->updateGraphics();
			Handler::charBatch.setSubData(text->mesh());
		}
	}

	Handler::hud.addToBatch(Handler::charBatch);

	Handler::basicBatch.bindBuffer();
	for (auto& entities : renderVectors.entities) {
		for (auto& entity : *entities) {
			entity->updateGraphics();
			Handler::basicBatch.setSubData(entity->mesh());
#ifdef _DEBUG
			if (DebugSettings::I_SHOWCOLLISIONBOXES) {
				entity->hitCollision().updateGraphics();
				Handler::basicBatch.setSubData(entity->hitCollision().mesh());
			}
#endif
		}
	}

	for (auto& basicBlocks : renderVectors.basicBlocks) {
		for (auto& basicBlock : *basicBlocks) {
			basicBlock->updateGraphics();
			Handler::basicBatch.setSubData(basicBlock->mesh());
		}
	}

	Handler::basicBatch.draw();
	Handler::charBatch.draw();
}

void updateObjects() {
	Handler::map.update();
	Handler::hud.update();

	Handler::cam.setX(Handler::player.x() + Handler::player.width() / 2);
	Handler::cam.setY(Handler::player.y() + Constants::windowStretch / 2);
	if (Input::keyUP) {
		Handler::cam.setZoom(Handler::cam.zoom() + 10);
	}
	else if (Input::keyDOWN) {
		Handler::cam.setZoom(Handler::cam.zoom() - 10);
	}
	else {
		Handler::cam.setZoom(Handler::cam.zoom());
	}


	Shaders::I_basicShader.bind();
	Shaders::I_basicShader.setMat3(Constants::Uniforms::camera, Handler::cam.transform());
	Shaders::I_charShader.bind();
	Shaders::I_charShader.setMat3(Constants::Uniforms::camera, Handler::cam.transform());
}

