#pragma once
#include "shader.h"

namespace Shaders {
	inline Shader I_charShader{ "char.vertex","rect.geom", "char.frag", Shader::charAttrib()};
	inline Shader I_basicShader{ "basic.vertex","rect.geom", "basic.frag", Shader::basicAttrib()};
}