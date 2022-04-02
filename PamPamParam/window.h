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
	bool m_isFullScreen{ false }; // desktop

protected:
public:

	Window(const float& width, const float& height, std::string_view title, const bool& isFullScreen);
	virtual ~Window();
	Window(const Window& window) = delete;
	Window& operator=(const Window& window) = delete;

	void swapBuffers() {
		SDL_GL_SwapWindow(m_window);
	}

	const float& width() const {
		return m_width;
	}
	const float& height() const {
		return m_height;
	}

	const float& halfWidth() const {
		return m_halfWidth;
	}

	const float& halfHeight() const {
		return m_halfHeight;
	}

	const std::string& title() const {
		return m_title;
	}

	void setWidth(const float& value);
	void setHeight(const float& value);
	void setWindowFullScreen();
	void updateSize();
	void exitFullScreen();

	const bool& isFullScreen() const {
		return m_isFullScreen;
	}

#ifdef _DEBUG
private:
	static inline ObjectsCount mS_objectsCount{};
#endif

};

inline Window I_WIN{ 1600,800, "BestGameEver", false };