#pragma once

namespace Constants {
	namespace Uniforms {
		inline const char* transform{ "transform" };
		inline const char* color{ "color" };
	}

	const char pS = // path separator
#ifdef _WIN32
		'\\';
#else
		'/';
#endif

	inline const int openglLeft{ -1 };
	inline const int openglRight{ 1 };
	inline const int openglTop{ 1 };
	inline const int openglDown{ -1 };
	inline const int openglCenter{ 0 };

	struct vec2 {
		float x;
		float y;
	};

	struct vec3 {
		float x;
		float y;
		float z;
	};

	struct vec4 {
		float x;
		float y;
		float z;
		float w;
	};

	const inline float pixelStart{ 0 };

	const inline double PI{ 3.141592653589793238462643 };

	const inline float widthStretch{ 1000 };
	const inline float heightStretch{ 1000 };
}

enum class Header_Files {
	camera_h,
	constants_h,
	debug_h,
	font_h,
	imageLoader_h,
	mesh_h,
	object_h,
	shader_h,
	stb_image_h,
	text_h,
	textureArray_h,
	utils_h,
	window_h,
	rectangle_h,
	handler_h,
	entity_h,
	player_h,
	block_h,
	batch_h,
};

enum class Source_Files {
	camera_cpp,
	debug_cpp,
	font_cpp,
	glad_c,
	mesh_cpp,
	object_cpp,
	shader_cpp,
	Source_cpp,
	text_cpp,
	textureArray_cpp,
	utils_cpp,
	window_cpp,
	rectangle_cpp,
	handler_cpp,
	entity_cpp,
	player_cpp,
	block_cpp,
	batch_cpp,
};

namespace Colors {
	const inline Constants::vec4 red{ 255.f, 0.f, 0.f, 255.f };
	const inline Constants::vec4 green{ 0.f, 255.f, 0.f, 255.f };
	const inline Constants::vec4 blue{ 0.f, 0.f, 255.f, 255.f };
	const inline Constants::vec4 white{ 255.f, 255.f, 255.f, 255.f };
	const inline Constants::vec4 black{ 0.0f,0.0f, 0.0f, 255.0f };
}