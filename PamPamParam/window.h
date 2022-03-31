#pragma once
#include "utils.h"
#include <glad/glad.h>
#include <SDL.h>
#include <string>
#include <string_view>
#include <iostream>


class Window {
private:
	float m_width{ };
	float m_height{ };
	float m_halfWidth{m_width / 2};
	float m_halfHeight{ m_height / 2 };
	std::string m_title;
	SDL_Window* m_window;
	SDL_GLContext m_context;

	const float& halfWidth() {
		return m_halfWidth;
	}
	const float& halfHeight() {
		return m_halfHeight;
	}

protected:
public:

	Window(const float& width, const float& height, std::string_view title);
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


	const float& width() const {
		return m_width;
	}
	const float& height() const {
		return m_height;
	}

	const std::string& title() const {
		return m_title;
	}

	void setWidth(const float& value);
	void setHeight(const float& value);
	void setWindowFullScreen();
	void updateSize();
	void exitFullScreen() {
		SDL_SetWindowFullscreen(m_window, 0);
	}

#ifdef _DEBUG
private:
	static inline ObjectsCount mS_objectsCount{};
#endif

};

inline Window I_WIN{ 1600,800, "BestGameEver" };