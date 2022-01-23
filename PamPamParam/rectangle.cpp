#include "rectangle.h"

Rectangle::Rectangle(const float& width, const float& height, const float& x, const float& y, const Constants::vec4& color) :
	Object{width ,height, x, y, color, Shader::basicAttrib(), mS_rectangleMesh} {
#ifdef _DEBUG
	DEBUG_CONSTRUCTOR_OBJ(this, Source_Files::rectangle_cpp, &mS_objectsCount);
#endif
}
Rectangle::~Rectangle() {
#ifdef _DEBUG
	DEBUG_DESTRUCTOR_OBJ(this, Source_Files::rectangle_cpp);
	setDebugDestructor(false);
#endif
}

void Rectangle::setShaderCoords(const int& index, Mesh& rectMesh, const int& stride) {
	
	float& left_down_x { rectMesh[index] };
	float& left_down_y { rectMesh[index + 1] };

	float& right_down_x{ rectMesh[index + stride] };
	float& right_down_y{ rectMesh[index + stride + 1] };

	float& left_up_x{ rectMesh[index + stride * 2] };
	float& left_up_y{ rectMesh[index + stride * 2 + 1] };

	left_down_x = transformX(left_down_x);
	left_down_y = transformX(left_down_y);

	right_down_x = transformX(right_down_x);
	right_down_y = transformX(right_down_y);

	left_up_x = transformX(left_up_x);
	left_up_y = transformX(left_up_y);
}

void Rectangle::setShaderTextures(const int& index, Mesh& rectMesh, const Texture& texture, const int& stride) {
	rectMesh[index + 2] = texture.x1;
	rectMesh[index + 3] = texture.y1;
	rectMesh[index + 4] = texture.z;

	rectMesh[index + stride + 2] = texture.x2;
	rectMesh[index + stride + 3] = texture.y1;
	rectMesh[index + stride + 4] = texture.z;

	rectMesh[index + stride * 2 + 2] = texture.x1;
	rectMesh[index + stride * 2 + 3] = texture.y2;
	rectMesh[index + stride * 2 + 4] = texture.z;
}

void Rectangle::setShaderColors(const int& index, Mesh& rectMesh, const Constants::vec4& colorNormalized,
	const int& stride) {
	rectMesh[index + 5] = colorNormalized.x;
	rectMesh[index + 6] = colorNormalized.y;
	rectMesh[index + 7] = colorNormalized.z;
	rectMesh[index + 8] = colorNormalized.w;

	rectMesh[index + stride + 5] = colorNormalized.x;
	rectMesh[index + stride + 6] = colorNormalized.y;
	rectMesh[index + stride + 7] = colorNormalized.z;
	rectMesh[index + stride + 8] = colorNormalized.w;

	rectMesh[index + stride * 2 + 5] = colorNormalized.x;
	rectMesh[index + stride * 2 + 6] = colorNormalized.y;
	rectMesh[index + stride * 2 + 7] = colorNormalized.z;
	rectMesh[index + stride * 2 + 8] = colorNormalized.w;
}