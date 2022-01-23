#pragma once
#include "object.h"


class Rectangle : public Object {
private:

	std::vector<Texture*> m_textures{};

	static inline Mesh mS_rectangleMesh{
		//position coords		                            texture coords       color
		Constants::pixelStart,  Constants::pixelStart,		0, 0, 1,             0,0,0,0,	         //left down
		Constants::pixelEnd,    Constants::pixelStart, 		0, 0, 1,             0,0,0,0,            //right down
		Constants::pixelStart,  Constants::pixelEnd, 		0, 0, 1,	         0,0,0,0,            //left up
	};

	void setShaderCoords(const int& index, Mesh& rectMesh, const int& stride);
	void setShaderTextures(const int& index, Mesh& rectMesh, const Texture& texture, const int& stride);
	void setShaderColors(const int& index, Mesh& rectMesh, const Constants::vec4& colorNormalized, const int& stride);



public:

//#ifdef _DEBUG
//		DEBUG_DESTRUCTOR_OBJ(this, Source_Files::text_cpp);
//	setDebugDestructor(false);
//#endif


	Rectangle(const float& width, const float& height, const float& x, const float& y, const Constants::vec4& color);
	virtual ~Rectangle();

#ifdef _DEBUG
private:
	static inline ObjectsCount mS_objectsCount{};

#endif
};