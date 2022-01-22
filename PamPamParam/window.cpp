#include "window.h"

namespace {
	/*void framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
		Window::setWidth(static_cast<float>(width));
		Window::setHeight(static_cast<float>(height));

	}*/
}

Window::Window(std::string_view title) : m_title{ title } {
#ifdef _DEBUG
	DEBUG_CONSTRUCTOR_OBJ(this, Source_Files::window_cpp, &mS_objectsCount);
#endif

	// Initialize SDL 
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		fprintf(stderr, "%s: %s\n", "Couldn't initialize SDL", SDL_GetError());
		exit(2);
	}

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	m_window = SDL_CreateWindow(title.data(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		static_cast<int>(mS_width), static_cast<int>(mS_height), SDL_WINDOW_OPENGL);
	m_context = SDL_GL_CreateContext(m_window);

	gladLoadGLLoader(SDL_GL_GetProcAddress);
	SDL_GL_SetSwapInterval(1);
}

Window::~Window() {

#ifdef _DEBUG
	DEBUG_DESTRUCTOR_OBJ(this, Header_Files::window_cpp);
#endif
	SDL_GL_DeleteContext(m_context);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}