#pragma once
#include "shader.h"

namespace Shaders {
	inline Shader I_charShader{ Constants::char_vertexPath,Constants::rect_geomPath, Constants::char_fragPath, Shader::charAttrib()};
	inline Shader I_basicShader{ Constants::basic_vertexPath,Constants::rect_geomPath, Constants::basic_fragPath, Shader::basicAttrib()};
}