#pragma once
#include "window.h"
#include "object.h"
#include "utils.h"
#include "Batch.h"
#include "font.h"
#include "shaders.h"


class Handler {
private:
	std::vector<Object*> m_objects;
	std::vector<Object*> m_texts;

	void renderObj(const Object& obj, Camera& camera);

	Font m_font{ "fonts\\gameFont.ttf", 524,524 };
	Batch m_charBatch{ m_font.atlas(), Shaders::I_charShader };

protected:
public:
	Handler();
	~Handler();

	// de modificat
	Batch& batch() {
		return m_charBatch;
	}

	void addObj(Object& object) {
		m_objects.push_back(&object);
	}

	void addText(Object& text) {
		m_texts.push_back(&text);
	}

	void removeObject(Object& object);

	void updateObjects() {
		for (auto& obj : m_objects) {
			obj->update();
		}
	}

	void renderObjects();

	/*void renderObjects(Camera& camera) {
		for (auto& obj : m_objects) {
			renderObj(*obj, camera);
		}
	}*/

	const Font& font() const {
		return m_font;
	}


#ifdef _DEBUG
private:
	static inline ObjectsCount mS_objectsCount{};

#endif
};