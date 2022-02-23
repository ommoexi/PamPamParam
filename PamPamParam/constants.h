#pragma once
#include <filesystem>

// constants.h
struct Point
{
	int x{};
	int y{};
};

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

	struct ZoneCoords {
		int x{};
		int y{};
		int x2{};
		int y2{};
		int middleX{};
		int middleY{};

		ZoneCoords(const Point& first, const Point& second);
	};

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

	const inline float pixelStart { 0 };
	const inline float pixelEnd { 1 };

	const inline double PI{ 3.141592653589793238462643 };

	const inline float widthStretch{ 1000 };
	const inline float heightStretch{ 1000 };
	
	const inline std::filesystem::path currentDirectoryPath{ std::filesystem::current_path() };

	const inline std::string basic_fragFile{ "basic.frag" };
	const inline std::string basic_vertexFile{ "basic.vertex" };
	const inline std::string char_fragFile{ "char.frag" };
	const inline std::string char_vertexFile{ "char.vertex" };
	const inline std::string rect_geomFile{ "rect.geom" };

	const inline std::string basic_fragPath{( currentDirectoryPath / basic_fragFile).generic_string() };
	const inline std::string basic_vertexPath{ (currentDirectoryPath / basic_vertexFile).generic_string() };
	const inline std::string char_fragPath{ (currentDirectoryPath / char_fragFile).generic_string() };
	const inline std::string char_vertexPath{ (currentDirectoryPath / char_vertexFile).generic_string() };
	const inline std::string rect_geomPath{ (currentDirectoryPath / rect_geomFile).generic_string() };

	namespace textures {

		const inline std::string texturesFolder{ "textures" };
		const inline std::filesystem::path texturesPath{ currentDirectoryPath / texturesFolder };

		const inline std::string player_pngFile{ "player.png" };
		const inline std::string player_pngPath{ (texturesPath / player_pngFile).generic_string() };
		const inline std::string death_pngFile{ "death.png" };
		const inline std::string death_pngPath{ (texturesPath / death_pngFile).generic_string() };
		const inline std::string splitTest_pngFile{ "splitTest.png" };
		const inline std::string splitTest_pngPath{ (texturesPath / splitTest_pngFile).generic_string() };

	}
	namespace fonts {

		const inline std::string fontsFolder{ "fonts" };
		const inline std::filesystem::path fontsPath{ currentDirectoryPath / fontsFolder };

		const inline std::string gameFontFile{ "gameFont.ttf" };
		const inline std::string gameFont{ (fontsPath / gameFontFile).generic_string() };
	}

	namespace handler {
		const inline size_t entitiesSize{ 500 };
		const inline size_t basicBlocksSize{ 500 };
		const inline size_t textsSize{ 500 };
	}



}
#ifdef _DEBUG
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
	basicBlock_h,
	batch_h,
	animation_h,
	input_h,
	includeBlocks_h,
	includeEntities_h,
	map_h,
	zone_h,
};

enum class Source_Files {
	camera_cpp,
	constants_cpp,
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
	animation_cpp,
	input_cpp,
	map_cpp,
	zone_cpp,
};
#endif

namespace Colors {
	const inline Constants::vec4 red{ 255.f, 0.f, 0.f, 255.f };
	const inline Constants::vec4 green{ 0.f, 255.f, 0.f, 255.f };
	const inline Constants::vec4 blue{ 0.f, 0.f, 255.f, 255.f };
	const inline Constants::vec4 white{ 255.f, 255.f, 255.f, 255.f };
	const inline Constants::vec4 black{ 0.0f,0.0f, 0.0f, 255.0f };
}

