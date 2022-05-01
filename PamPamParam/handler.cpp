#include "handler.h"

void renderObjects() {

	auto& renderVectors{ Handler::map.renderVectors() };

	Handler::charBatch.bindBuffer();
	for (auto& texts : renderVectors.texts) {
		for (auto& text : *texts) {
			text->updateGraphics();
			Handler::charBatch.setSubData(text->mesh());
		}
	}
	Handler::hud.addToTextBatch(Handler::charBatch);

	Handler::basicBatch.bindBuffer();
	Handler::hud.addToBasicBatch(Handler::basicBatch);
	for (auto& entities : renderVectors.entities) {
		for (auto& entity : *entities) {
			entity->renderToBasicBatch(Handler::basicBatch);
		}
	}

	for (auto& backgrounds : renderVectors.backgrounds) {
		for (auto& background : *backgrounds) {
			background->updateGraphics();
			Handler::basicBatch.setSubData(background->mesh());
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
	Handler::cam.setY(Handler::player.y() + Handler::player.height() / 2);

	float camZoom{Handler::cam.zoom()};
	if (Input::keyUP) {
		camZoom += 10;
	}
	else if (Input::keyDOWN) {
		camZoom -= 10;
	}
	Handler::cam.setZoom(camZoom);
	Handler::cam.update();

	Input::mouse.update(Handler::cam);

	Shaders::I_basicShader.bind();
	Shaders::I_basicShader.setMat3(Constants::Uniforms::camera, Handler::cam.transform());
	Shaders::I_charShader.bind();
	Shaders::I_charShader.setMat3(Constants::Uniforms::camera, Handler::cam.transform());
}

