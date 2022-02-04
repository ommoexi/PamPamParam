#pragma once
#include "utils.h"
#include <glad/glad.h>
#include <SDL.h>
#include <string>
#include <string_view>
#include <iostream>


class Window {
private:
	static inline float mS_width{ 1200 };
	static inline float mS_height{ 800 };
	static inline float mS_halfWidth{mS_width / 2};
	static inline float mS_halfHeight{ mS_height / 2 };
	std::string m_title;
	SDL_Window* m_window;
	SDL_GLContext m_context;

	static const float& halfWidth() {
		return mS_halfWidth;
	}
	static const float& halfHeight() {
		return mS_halfHeight;
	}

protected:
public:

	Window(std::string_view title);
	virtual ~Window();
	Window(const Window& window) = delete;
	Window& operator=(const Window& window) = delete;

	void swapBuffers() {
		SDL_GL_SwapWindow(m_window);
	}

	const float normalizeX(const float& x) const {
		return x / Constants::widthStretch;
	}

	const float normalizeY(const float& y) const {
		return y / Constants::heightStretch;
	}


	static const float& width() {
		return mS_width;
	}
	static const float& height() {
		return mS_height;
	}

	const std::string& title() const {
		return m_title;
	}

	static void setWidth(const float& value) {
		mS_width = value;
		mS_halfWidth = value / 2;
	}

	static void setHeight(const float& value) {
		mS_height = value;
		mS_halfHeight = value / 2;
	}

#ifdef _DEBUG
private:
	static inline ObjectsCount mS_objectsCount{};
#endif

};

inline Window I_WIN{ "BestGameEver" };