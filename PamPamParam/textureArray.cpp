#include "textureArray.h"

namespace {
	const int textureSpacing{ 1 };

	Texture _nullTexture{};

}

namespace image {

	Image loadImage(std::string_view filePath, std::string_view setName, const int& desiredChannels) {

		Image image{ setName.data() };

		image.data = stbi_load(filePath.data(), &image.width, &image.height, &image.channels, desiredChannels);

		return image;
	}

	void freeImageData(Image& image) {
		stbi_image_free(image.data);
	}
}

unsigned int TextureArray::constructorBody(const int& wrap_s, const int& wrap_t, const int& min_filter, const int& mag_filter,
	const int& internal_format, const int& width, const int& height, const int& depth, const int& format,
	const int& type, const bool& generate_mipmap, int unpack_alignment) const {

	unsigned int id{};

	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D_ARRAY, id);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, wrap_s);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, wrap_t);

	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, min_filter);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, mag_filter);

	glPixelStorei(GL_UNPACK_ALIGNMENT, unpack_alignment);

	glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, internal_format, width, height, depth, 0, format, type, nullptr);

	if (generate_mipmap) {
		glGenerateMipmap(GL_TEXTURE_2D_ARRAY);
	}

	return id;
}

TextureArray::TextureArray(const int& wrap_s, const int& wrap_t, const int& min_filter, const int& mag_filter,
	const int& internal_format, const int& width, const int& height, const int& depth, const int& format,
	const int& type, const bool& generate_mipmap, int unpack_alignment) :
	m_width{ width }, m_height{ height }, m_depth{ depth }, m_wrap_s{ wrap_s }, m_wrap_t{ wrap_t }, m_min_filter{ min_filter },
	m_mag_filter{ mag_filter }, m_unpack_alignment{ unpack_alignment }, m_internal_format{ internal_format }, m_format{ format },
	m_type{ type }{

#ifdef _DEBUG
	DEBUG_CONSTRUCTOR_OBJ(this, Source_Files::textureArray_cpp, &mS_objectsCount);
#endif

	m_id = constructorBody(wrap_s, wrap_t, min_filter, mag_filter, internal_format,
		m_width, m_height, m_depth, format, type, generate_mipmap, unpack_alignment);

}

TextureArray::TextureArray(const int& width, const int& height, const int& wrap_s, const int& wrap_t, const int& min_filter, 
	const int& mag_filter,const int& internal_format, const std::vector<Constants::vec2>& texturesSize, const std::vector<void*>& pixels,
	const std::vector<std::string>& textureNames, const int& format, const int& type, const bool& generate_mipmap,
	int unpack_alignment) : m_width{ width }, m_height{ height }, m_wrap_s{ wrap_s }, m_wrap_t{ wrap_t }, 
	m_min_filter{ min_filter },m_mag_filter{ mag_filter }, m_unpack_alignment{ unpack_alignment }, m_internal_format{ internal_format },
	m_format{ format },m_type{ type } {

#ifdef _DEBUG
	DEBUG_CONSTRUCTOR_OBJ(this, Source_Files::textureArray_cpp, &mS_objectsCount);
#endif

	const size_t& texSize{ texturesSize.size() };
	const size_t& pixelsSize{ pixels.size() };
	const size_t& texNamesSize{ textureNames.size() };

	if (texSize != pixelsSize || texSize != texNamesSize) {

#ifdef _DEBUG
#ifdef _DANGER
		debugMessage("DANGER::TEXTURE ARRAY INITIALIZATION VECTORS SIZE DON'T MATCH");
#endif
#endif
		return;
	}
	alocateMemory(texturesSize);
	m_id = constructorBody(wrap_s, wrap_t, min_filter, mag_filter, internal_format,
		m_width, m_height, m_depth, format, type, generate_mipmap, unpack_alignment);

	for (unsigned int i{}; i < texSize; i++) {
		subImage(static_cast<int>(texturesSize[i].x), static_cast<int>(texturesSize[i].y), 
			textureNames[i], pixels[i]);
	}

}

TextureArray::TextureArray(const int& width, const int& height, const int& wrap_s, const int& wrap_t, const int& min_filter, 
	const int& mag_filter,const int& internal_format, std::vector<Image>& images, const int& format, const int& type, 
	const bool& generate_mipmap, int unpack_alignment) : m_width{ width }, m_height{ height },
	m_wrap_s{ wrap_s }, m_wrap_t{ wrap_t }, m_min_filter{ min_filter }, m_mag_filter{ mag_filter },
	m_unpack_alignment{ unpack_alignment }, m_internal_format{ internal_format }, m_format{ format }, m_type{ type } {
#ifdef _DEBUG
	DEBUG_CONSTRUCTOR_OBJ(this, Source_Files::textureArray_cpp, &mS_objectsCount);
#endif

	std::vector<Constants::vec2> size{};
	for (auto& image : images) {
		size.push_back(Constants::vec2{ static_cast<float>(image.width), static_cast<float>(image.height) });
	}
	alocateMemory(size);
	m_id = constructorBody(wrap_s, wrap_t, min_filter, mag_filter, internal_format,
		m_width, m_height, m_depth, format, type, generate_mipmap, unpack_alignment);
	for (auto& image : images) {
		subImage(image.width, image.height, image.name, image.data);
		image::freeImageData(image);
	}
}

TextureArray::TextureArray(const int& width, const int& height, const int& wrap_s, const int& wrap_t, const int& min_filter,
	const int& mag_filter,const int& internal_format, const std::vector<Constants::vec2>& texturesSize, const int& format,
	const int& type, const bool& generate_mipmap, int unpack_alignment) : m_width{ width }, m_height{ height }, 
	m_wrap_s{ wrap_s }, m_wrap_t{ wrap_t }, m_min_filter{ min_filter },m_mag_filter{ mag_filter }, 
	m_unpack_alignment{ unpack_alignment }, m_internal_format{ internal_format }, m_format{ format },m_type{ type }{
#ifdef _DEBUG
	DEBUG_CONSTRUCTOR_OBJ(this, Source_Files::textureArray_cpp, &mS_objectsCount);
#endif

	alocateMemory(texturesSize);
	m_id = constructorBody(wrap_s, wrap_t, min_filter, mag_filter, internal_format,
		m_width, m_height, m_depth, format, type, generate_mipmap, unpack_alignment);
}

void TextureArray::alocateMemory(const std::vector<Constants::vec2>& texturesSize) {
	for (auto& tSize : texturesSize) {
		if (m_maxTextureHeightPerRow < tSize.y) {
			m_maxTextureHeightPerRow = static_cast<int>(tSize.y);
		}
		int newXOffset{ m_xOffset + static_cast<int>(tSize.x) + textureSpacing };
		if (newXOffset > m_width) {
			int newYOffset{ m_yOffset + m_maxTextureHeightPerRow + textureSpacing };
			m_xOffset = 0;
			newXOffset = static_cast<int>(tSize.x);
			if (newYOffset + tSize.y > m_height) {
				m_yOffset = 0;
				m_zOffset += 1;
				m_maxTextureHeightPerRow = 0;
			}
			else {
				m_yOffset = newYOffset;
				m_maxTextureHeightPerRow = static_cast<int>(tSize.y);
			}
		}
		if (m_zOffset > mS_maxDepth) {
#ifdef _DEBUG
#ifdef _DANGER
			debugMessage("DANGER:: TEXTURE ARRAY ALOCATION MAX DEPTH \n");
#endif
#endif
			break;
		}
		m_xOffset = newXOffset;

	}
	m_depth = m_zOffset;
	m_maxTextureHeightPerRow = 0;
	m_xOffset = 0;
	m_yOffset = 0;
	m_zOffset = 0;
}


TextureArray::~TextureArray() {
#ifdef _DEBUG
	DEBUG_DESTRUCTOR_OBJ(this, Source_Files::textureArray_cpp);
#endif

	glDeleteTextures(1, &m_id);
}

const Texture& TextureArray::subImage(const int& width, const int& height, const std::string& textureName, void* pixels) {
	glBindTexture(GL_TEXTURE_2D_ARRAY, m_id);
	if (m_maxTextureHeightPerRow < height) {
		m_maxTextureHeightPerRow = height;
	}
	int newXOffset{ m_xOffset + width + textureSpacing };
	if (newXOffset > m_width) {
		int newYOffset{ m_yOffset + m_maxTextureHeightPerRow + textureSpacing };
		m_xOffset = 0;
		newXOffset = width;
		if (newYOffset + height > m_height) {
			m_yOffset = 0;
			m_zOffset += 1;
			m_maxTextureHeightPerRow = 0;
		}
		else {
			m_yOffset = newYOffset;
			m_maxTextureHeightPerRow = height;
		}
	}
	if (m_zOffset > m_depth) {
#ifdef _DEBUG
#ifdef _DANGER
		debugMessage("DANGER:: TEXTURE ARRAY NO SPACE \n");
#endif
#endif
		return _nullTexture;
	}
	glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, m_xOffset, m_yOffset, m_zOffset, width, height, 1, m_format, m_type, pixels);

	float x_1{ static_cast<float>(m_xOffset) / m_width };
	float x_2{ x_1 + static_cast<float>(width) / m_width };

	float y_1{ static_cast<float>(m_yOffset) / m_height };
	float y_2{ y_1 + static_cast<float>(height) / m_height };

	m_xOffset = newXOffset;

#ifdef _DEBUG
#ifdef _DANGER
	if (m_textures.count(textureName) > 0) {
		debugMessage("DANGER:: TEXTURE OVERRIDE \n");
	}

#endif
#endif
	Texture newTexture{ Texture{ x_1, x_2, y_1, y_2, m_zOffset, width, height } };
	m_textures[textureName] = newTexture;
	return m_textures[textureName];

}

const Texture& TextureArray::getTexture(const std::string& textureName) const {
	try {
		return m_textures.at(textureName);
	}
	catch (...) {
#ifdef _DEBUG
#ifdef _DANGER
		debugMessage("DANGER:: GETTING UNCREATED TEXTURE \n");
#endif
#endif
	}
	return mS_nullTexture;
}

void TextureArray::bind() const {
	glBindTexture(GL_TEXTURE_2D_ARRAY, m_id);
}
