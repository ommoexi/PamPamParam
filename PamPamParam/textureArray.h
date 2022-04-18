#pragma once
#include "utils.h"
#include <glad/glad.h>
#include "stb_image.h"
#include <string_view>
#include <map>
#include <string>

struct Texture {
	float x1;
	float x2;
	float y1;
	float y2;
	int z;
	int width;
	int height;

	// must be deleted when no longer used!!!!!
	Texture* reverseXAxis() const {
		return new Texture{ x2, x1, y1, y2, z, width, height };
	}

	// must be deleted when no longer used!!!!!
	Texture* reverseYAxis() const {
		return new Texture{ x1, x2, y2, y1, z, width, height };
	}

	// must be deleted when no longer used!!!!!
	Texture* reverseXYAxis() const {
		return new Texture{ x2,x1, y2,y1,z, width, height };
	}
};


// for stbi
struct Image {
	std::string name;
	unsigned int splitWidth;
	unsigned int splitHeight;
	int width;
	int height;
	int channels;
	unsigned char* data;

};

// i advise loading textures with same height
class TextureArray {

public:
	inline static const int mS_maxDepth{ 256 };

private:
	unsigned int m_id{};
	int m_width{};
	int m_height{};
	int m_depth{};
	int m_xOffset{};
	int m_yOffset{};
	int m_maxTextureHeightPerRow{};
	int m_zOffset{ 1 };

	int m_wrap_s{};
	int m_wrap_t{};
	int m_min_filter{};
	int m_mag_filter{};
	int m_unpack_alignment{};
	int m_internal_format{};
	int m_format{};
	int m_type{};

	std::map<std::string, Texture> m_textures{};

	inline static const Texture mS_nullTexture{};

	unsigned int constructorBody(const int& wrap_s, const int& wrap_t, const int& min_filter, const int& mag_filter,
		const int& internal_format, const int& width, const int& height, const int& depth, const int& format,
		const int& type, const bool& generate_mipmap, int unpack_alignment) const;

	// sets how much depth array has based on all texture sizes
	void alocateMemory(const std::vector<Constants::vec2>& texturesSize);

protected:
public:
	TextureArray(const TextureArray& texture) = delete;
	TextureArray& operator=(const TextureArray& texture) = delete;

	TextureArray(const int& wrap_s, const int& wrap_t, const int& min_filter, const int& mag_filter,
		const int& internal_format, const int& width, const int& height, const int& depth, const int& format,
		const int& type, const bool& generate_mipmap, int unpack_alignment = 4);

	//every texture vector must have same size
	TextureArray(const int& width, const int& height, const int& wrap_s, const int& wrap_t, const int& min_filter,
		const int& mag_filter, const int& internal_format, const std::vector<Constants::vec2>& texturesSize,
		const std::vector<void*>& pixels, const std::vector<std::string>& textureNames, const int& format,
		const int& type, const bool& generate_mipmap,
		int unpack_alignment = 4);

	//loads every texture loaded with stbi then deletes it with stbi
	TextureArray(const int& width, const int& height, const int& wrap_s, const int& wrap_t, const int& min_filter,
		const int& mag_filter, const int& internal_format, std::vector<Image>& images, const int& format,
		const int& type, const bool& generate_mipmap, int unpack_alignment = 4);

	// alocates memory only and textures must be loaded as same as texturesSize
	TextureArray(const int& width, const int& height, const int& wrap_s, const int& wrap_t, const int& min_filter,
		const int& mag_filter, const int& internal_format, const std::vector<Constants::vec2>& texturesSize, const int& format,
		const int& type, const bool& generate_mipmap, int unpack_alignment = 4);

	virtual ~TextureArray();

	// if split is 0 then no split and if split doesnt split exactly on image the outer is discarded
	// names will be image.name-{row.col} row and col start from 1
	const Texture& subImage(const int& width, const int& height, const std::string& textureName, void* pixels,
		const unsigned int& splitWidth = 0, const unsigned int& splitHeight = 0);

	const Texture& getTexture(const std::string& textureName) const;

	void bind() const;

	const int& width() const {
		return m_width;
	}
	const int& height() const {
		return m_height;
	}

#ifdef _DEBUG
private:
	static inline ObjectsCount mS_objectsCount{};

#endif
};

namespace image {

	Image loadImage(std::string_view filePath, std::string_view setName, const int& desiredChannels, unsigned int splitWidth = 0,
		unsigned int splitHeight = 0);

	void freeImageData(Image& image);

}

const Texture& getNullTexture();

std::string splitTextureName(const std::string& textureName, const int& row, const int& col);