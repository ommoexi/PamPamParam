#pragma once
#define STRINGIFY(name) (#name)

#include "constants.h"
#include <vector>
#ifdef _DEBUG
#include "debug.h"
inline Debugger _I_DEBUG; 

std::string _typeIdClassName(std::string_view typeIdClass);
std::string _getLastScope(std::string_view s);
inline std::string _processEmptyString(std::string_view s) {
	if (s == "\"\"") {
		return "";
	}
	return std::string{ s };
}


#define DEBUG_ADD_OBJ(obj, fileName, objClassNameLocation, funcLocation)\
(_I_DEBUG._addObj(obj, _typeIdClassName(typeid(obj).name()), #obj, _getLastScope(#fileName), _processEmptyString(#objClassNameLocation), funcLocation))

#define DEBUG_REMOVE_OBJ(obj, fileName, objClassNameLocation, funcLocation, removeFromAllObjects)\
(_I_DEBUG._removeObj(obj, _getLastScope(#fileName), _processEmptyString(#objClassNameLocation), funcLocation, #obj, removeFromAllObjects))

#define DEBUG_CONSTRUCTOR_OBJ(obj, fileName, objectsCount)\
(_I_DEBUG._constructorObj(obj, _getLastScope(#fileName), _typeIdClassName(typeid(obj).name()), objectsCount))

#define DEBUG_DESTRUCTOR_OBJ(obj, fileName)\
(_I_DEBUG._destructorObj(obj, _getLastScope(#fileName), _typeIdClassName(typeid(obj).name())))

template<typename T>
inline void printArray(T* array, int size, int perRow) {
	int p{ 0 };
	for (int i{}; i < size; i++) {
		std::cout << array[i] << " ";
		p += 1;
		if (p == perRow) {
			std::cout << '\n';
			p = 0;
		}
	}
	std::cout << '\n';
}

inline void debugMessage(std::string_view message) {
	_I_DEBUG.debugMessage(message);
}

#endif 

inline Constants::vec4 normalizeColor(const Constants::vec4& color) {
	return Constants::vec4{ color.x / 255, color.y / 255, color.z / 255, color.w / 255 };
}

inline float normalizeColor(const float& color) {
	return color / 255;
}


using Mesh = std::vector<float>;

inline float normalizeX(const float& x) {
	return x / Constants::widthStretch;
}

inline float normalizeY(const float& y) {
	return y / Constants::heightStretch;
}