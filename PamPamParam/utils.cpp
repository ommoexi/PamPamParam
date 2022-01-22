#include "utils.h"
#ifdef _DEBUG
std::string _typeIdClassName(std::string_view typeIdClass) {
	/*size_t startClass{ typeIdClass.find_first_of(' ') + 1 };
	size_t endStartClass{ typeIdClass.find_first_of(' ', startClass) };
	return std::string{ typeIdClass.substr(startClass, endStartClass - startClass) };*/
	return std::string{ typeIdClass };
}

std::string _getLastScope(std::string_view s) {
	size_t start{ s.find_last_of(':') + 1 };
	return std::string{ s.substr(start, s.length() - start) };
}
#endif
