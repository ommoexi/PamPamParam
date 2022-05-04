#pragma once
#include <filesystem>

// constants.h
struct Point
{
	int x{};
	int y{};
	
};

inline std::ostream& operator<<(std::ostream& os, const Point& p) {
	os << "x : " << p.x << " y : " << p.y << '\n';
	return os;
}

namespace Constants {
	namespace Uniforms {
		inline const std::string camera{ "camera" };
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
		void copy(const Point& first, const Point& second);
		ZoneCoords() = default;
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

	const inline float pixelStart{ 0 };
	const inline float pixelEnd{ 1 };

	const inline double PI{ 3.141592653589793238462643 };

	const inline float windowStretch{ 1000 };
	const inline float windowSizeStretched{ windowStretch * 2 };

	const inline std::filesystem::path currentDirectoryPath{ std::filesystem::current_path() };

	const inline std::string basic_fragFile{ "basic.frag" };
	const inline std::string basic_vertexFile{ "basic.vertex" };
	const inline std::string char_fragFile{ "char.frag" };
	const inline std::string char_vertexFile{ "char.vertex" };
	const inline std::string rect_geomFile{ "rect.geom" };

	const inline std::string basic_fragPath{ (currentDirectoryPath / basic_fragFile).generic_string() };
	const inline std::string basic_vertexPath{ (currentDirectoryPath / basic_vertexFile).generic_string() };
	const inline std::string char_fragPath{ (currentDirectoryPath / char_fragFile).generic_string() };
	const inline std::string char_vertexPath{ (currentDirectoryPath / char_vertexFile).generic_string() };
	const inline std::string rect_geomPath{ (currentDirectoryPath / rect_geomFile).generic_string() };

	namespace textures {

		const inline std::string texturesFolder{ "textures" };
		const inline std::filesystem::path texturesPath{ currentDirectoryPath / texturesFolder };

		const inline std::string mossyPlantsFolder{ "Mossy Plants" };
		const inline std::filesystem::path mossyPlantsPath{ texturesPath / mossyPlantsFolder };

		const inline std::string mossyPlantsBlueFlower1Folder{ "BlueFlower1" };
		const inline std::filesystem::path mossyPlantsBlueFlower1Path{ mossyPlantsPath / mossyPlantsBlueFlower1Folder };

		const inline std::string mossyPlantsBlueFlower2Folder{ "BlueFlower2" };
		const inline std::filesystem::path mossyPlantsBlueFlower2Path{ mossyPlantsPath / mossyPlantsBlueFlower2Folder };

		const inline std::string mossyPlantsPlant1Folder{ "Plant 1" };
		const inline std::filesystem::path mossyPlantsPlant1Path{ mossyPlantsPath / mossyPlantsPlant1Folder };

		const inline std::string mossyPlantsPlant2Folder{ "Plant 2" };
		const inline std::filesystem::path mossyPlantsPlant2Path{ mossyPlantsPath / mossyPlantsPlant2Folder };

		const inline std::string mossyPlantsPlant3Folder{ "Plant 3" };
		const inline std::filesystem::path mossyPlantsPlant3Path{ mossyPlantsPath / mossyPlantsPlant3Folder };

		const inline std::string mossyPlantsPlant4Folder{ "Plant 4" };
		const inline std::filesystem::path mossyPlantsPlant4Path{ mossyPlantsPath / mossyPlantsPlant4Folder };

		const inline std::string mossyPlantsPlant5Folder{ "Plant 5" };
		const inline std::filesystem::path mossyPlantsPlant5Path{ mossyPlantsPath / mossyPlantsPlant5Folder };

		const inline std::string mossyPlantsPlant6Folder{ "Plant 6" };
		const inline std::filesystem::path mossyPlantsPlant6Path{ mossyPlantsPath / mossyPlantsPlant6Folder };

		const inline std::string mossyPlantsPlant7Folder{ "Plant 7" };
		const inline std::filesystem::path mossyPlantsPlant7Path{ mossyPlantsPath / mossyPlantsPlant7Folder };


		const inline std::string player_pngFile{ "player.png" };
		const inline std::string player_pngPath{ (texturesPath / player_pngFile).generic_string() };
		const inline std::string grass_pngFile{ "grass.png" };
		const inline std::string grass_pngPath{ (texturesPath / grass_pngFile).generic_string() };
		const inline std::string background_pngFile{ "background.png" };
		const inline std::string background_pngPath{ (texturesPath / background_pngFile).generic_string() };
		const inline std::string grassland_pngFile{ "grassland.png" };
		const inline std::string grassland_pngPath{ (texturesPath / grassland_pngFile).generic_string() };
		const inline std::string tree_pngFile{ "tree.png" };
		const inline std::string tree_pngPath{ (texturesPath / tree_pngFile).generic_string() };
		const inline std::string splitTest_pngFile{ "splitTest.png" };
		const inline std::string splitTest_pngPath{ (texturesPath / splitTest_pngFile).generic_string() };
		const inline std::string collisionBox_pngFile{ "collisionBox.png" };
		const inline std::string collisionBox_pngPath{ (texturesPath / collisionBox_pngFile).generic_string() };

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
	collisionBox_h,
	enemy_h,
	hud_h,
	framerate_h,
	controls_h,
	mouse_h,
	stats_h,
	physicsStats_h,
	background_h,
	projectile_h
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
	collisionBox_cpp,
	enemy_cpp,
	hud_cpp,
	framerate_cpp,
	controls_cpp,
	mouse_cpp,
	stats_cpp,
	physicsStats_cpp,
	background_cpp,
	projectile_cpp,
};
#endif

namespace Colors {
	const inline Constants::vec4 red{ 255.f, 0.f, 0.f, 255.f };
	const inline Constants::vec4 green{ 0.f, 255.f, 0.f, 255.f };
	const inline Constants::vec4 blue{ 0.f, 0.f, 255.f, 255.f };
	const inline Constants::vec4 white{ 255.f, 255.f, 255.f, 255.f };
	const inline Constants::vec4 black{ 0.0f,0.0f, 0.0f, 255.0f };
}

namespace Directions {
	enum class Direction {
		UP = 0,
		RIGHT = 1,
		DOWN = 2,
		LEFT = 3,
		NODIRECTION = 4,
	};

	const inline Direction UP{ Direction::UP };
	const inline Direction RIGHT{ Direction::RIGHT };
	const inline Direction DOWN{ Direction::DOWN };
	const inline Direction LEFT{ Direction::LEFT };
	const inline Direction NODIRECTION{ Direction::NODIRECTION };
}



namespace BasicNullTypes {
	const inline std::string string{ "nullString" };
}

inline std::string directionsDecifer(const int& val) {
	if (val == 0) {
		return "UP";
	}
	else if (val == 1) {
		return "RIGHT";
	}
	else if (val == 2) {
		return "DOWN";
	}
	else if (val == 3) {
		return "LEFT";
	}
	else if (val == 4) {
		return "NO DIRECTION";
	}
	return "";
}