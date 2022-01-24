#include "font.h"

void Font::setCharacter(const Texture& texture, const char& textureName, const int& glyphTop) {

	float enlargeLetter{ 2.75 }; // letters divided by screen width and height are too small therefore they need to be multiplied by this

	if (texture.width == 0) {
		float space_width{ m_pixelWidth / 2.4f / m_pixelWidth * enlargeLetter };
		m_characters.insert({ textureName , Character{space_width, 0, std::vector<float>{}} });
		return;
	}

	// divide by m_pixel for scaling

	float x_pos_1{ Constants::pixelStart };
	float glyphWidth{ (texture.width * enlargeLetter) / m_pixelWidth };
	float x_pos_2{ x_pos_1 + glyphWidth };
	float y_pos_1{ (Constants::pixelStart + ((static_cast<float>(glyphTop) - texture.height) / m_pixelHeight)) * enlargeLetter };
	float glyphHeight{ static_cast<float>(texture.height) / m_pixelHeight * enlargeLetter };
	float y_pos_2{ y_pos_1 + glyphHeight };

	if (glyphHeight > m_maxCharacterHeight) {
		m_maxCharacterHeight = glyphHeight;
	}

	Mesh charMesh{
		//position coords		texture coords
		x_pos_1, y_pos_1,		texture.x1, texture.y2, static_cast<float>(texture.z),	//left down
		x_pos_2, y_pos_1, 		texture.x2, texture.y2, static_cast<float>(texture.z),	//right down
		x_pos_1, y_pos_2, 		texture.x1, texture.y1, static_cast<float>(texture.z)	//left up
	};

	m_characters.insert({ textureName , Character{glyphWidth, glyphHeight, charMesh} });

}

Font::Font(std::string_view fontPath, const unsigned int& pixelWidth, const unsigned int& pixelHeight) :
	m_pixelWidth{ pixelWidth }, m_pixelHeight{ pixelHeight } {
#ifdef _DEBUG
	DEBUG_CONSTRUCTOR_OBJ(this, Source_Files::font_cpp, &mS_objectsCount);
#endif


	FT_Library ft;
	if (FT_Init_FreeType(&ft))
	{
#ifdef _DEBUG
		debugMessage("ERROR::FREETYPE: Could not init FreeType Library \n");
#endif
	}

	// load font as face
	FT_Face face;

	if (FT_New_Face(ft, fontPath.data(), 0, &face)) {
#ifdef _DEBUG
		debugMessage("ERROR::FREETYPE: Failed to load font \n");
#endif
	}
	FT_Set_Pixel_Sizes(face, pixelWidth, pixelHeight);

	long glyphSize{ 128 };
	long glyphStart{ 32 };


	auto& glyph{ face->glyph };

	std::vector<Constants::vec2> glyphsSize{};

	for (long i{ glyphStart }; i < glyphSize; i++) {
		if (FT_Load_Char(face, i, FT_LOAD_RENDER)) {
#ifdef _DEBUG
			debugMessage("ERROR::FREETYPE: Failed to load Glyph \n");
			continue;
#endif
		}

		glyphsSize.push_back({ static_cast<float>(glyph->bitmap.width), static_cast<float>(glyph->bitmap.rows) });

	}

	m_atlas = new TextureArray{ static_cast<int>(pixelWidth), static_cast<int>(pixelHeight), GL_CLAMP_TO_EDGE,
					  GL_CLAMP_TO_EDGE,
					  GL_LINEAR,
					  GL_LINEAR, GL_RED, glyphsSize, GL_RED, GL_UNSIGNED_BYTE, true, 1 };

	const size_t& totalGlyphs{ glyphsSize.size() };

	for (long i{ glyphStart }; i < glyphSize; i++) {
		if (FT_Load_Char(face, i, FT_LOAD_RENDER)) {
#ifdef _DEBUG
			debugMessage("ERROR::FREETYPE: Failed to load Glyph \n");
			continue;
#endif
		}


		const Texture& textureCharacter{ m_atlas->subImage(glyph->bitmap.width, glyph->bitmap.rows,
			std::string{ static_cast<char>(i) }, glyph->bitmap.buffer) };
		setCharacter(textureCharacter, static_cast<char>(i), glyph->bitmap_top );

	}

	FT_Done_Face(face);
	FT_Done_FreeType(ft);

}

Font::~Font() {
#ifdef _DEBUG
	DEBUG_DESTRUCTOR_OBJ(this, Source_Files::font_cpp);
#endif

	delete m_atlas;
}

