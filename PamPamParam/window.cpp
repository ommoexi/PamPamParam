#include "window.h"

Window::Window(const float& width, const float& height, std::string_view title) : m_width{ width }, m_height{height},
m_title { title } {
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
		static_cast<int>(width), static_cast<int>(height), SDL_WINDOW_OPENGL);
	SDL_SetWindowResizable(m_window, SDL_TRUE);
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

void Window::setWidth(const float& value) {
	m_width = value;
	m_halfWidth = value / 2;
	SDL_SetWindowSize(m_window, static_cast<int>(m_width), static_cast<int>(m_height));
}

void Window::setHeight(const float& value) {
	m_height = value;
	m_halfHeight = value / 2;
	SDL_SetWindowSize(m_window, static_cast<int>(m_width), static_cast<int>(m_height));
}

void Window::setWindowFullScreen() {
	SDL_SetWindowFullscreen(m_window, SDL_WINDOW_FULLSCREEN_DESKTOP);
}

void Window::updateSize() {
	int width{}, height{};
	SDL_GetWindowSize(m_window, &width, &height);
	m_width = static_cast<float>(width);
	m_height = static_cast<float>(height);
	m_halfWidth = static_cast<float>(width / 2);
	m_halfHeight = static_cast<float>(height / 2);
	glViewport(0, 0, static_cast<int>(I_WIN.width()), static_cast<int>(I_WIN.height()));
}