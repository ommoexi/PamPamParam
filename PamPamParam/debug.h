#ifdef _DEBUG
#pragma once
#undef _INFO
#include <map>
#include <string_view>
#include <iostream>

using ObjectsCount = unsigned long long;
class Debugger {
private:
	class Data {
	private:
		// object
		std::string m_className{};
		std::string m_varName{};

		std::string m_fileName{};
		std::string m_classNameLocation{};
		std::string m_functionLocation{};
		ObjectsCount* m_objectsCount{};
	public:
		Data(std::string_view className, std::string_view varName, std::string_view fileName,
			std::string_view classNameLocation, std::string_view functionLocation) :m_className{ className },
			m_varName{ varName }, m_fileName{ fileName }, m_classNameLocation{ m_classNameLocation },
			m_functionLocation{ functionLocation }{}
		Data() = default;
		Data(const Data& other) = default;
		virtual ~Data() = default;

		std::string_view className() const {
			return m_className;
		}
		std::string_view varName() const {
			return m_varName;
		}
		std::string_view fileName() const {
			return m_fileName;
		}
		std::string_view classNameLocation() const {
			return m_classNameLocation;
		}
		std::string_view functionLocation() const {
			return m_functionLocation;
		}
		ObjectsCount* objectsCount() const {
			return m_objectsCount;
		}

		Data& setClassName(std::string_view value) {
			m_className = value;
			return *this;
		}
		Data& setVarName(std::string_view value) {
			m_varName = value;
			return *this;
		}
		Data& setFileName(std::string_view value) {
			m_fileName = value;
			return *this;
		}
		Data& setClassNameLocation(std::string_view value) {
			m_classNameLocation = value;
			return *this;
		}
		Data& setFunctionLocation(std::string_view value) {
			m_functionLocation = value;
			return *this;
		}
		Data& setObjectsCount(ObjectsCount* value) {
			m_objectsCount = value;
			return *this;
		}
	};

	std::map<const void*, Data> m_allObjects{};
	std::ostream* m_stream{ &std::cout };
protected:
public:
	Debugger(const Debugger& debugger) = delete;
	Debugger& operator=(const Debugger& debugger) = delete;

	Debugger() = default;
	virtual ~Debugger();
	//call with macro in utils.h
	void _addObj(const void* obj, std::string_view objClassName, std::string_view varName, std::string_view fileName,
		std::string_view objClassNameLocation, std::string_view funcLocation);
	void _constructorObj(const void* obj, std::string_view fileName, std::string_view objClassName,
		ObjectsCount* objectsCount);
	// call with macro in utils.h
	void _removeObj(const void* obj, std::string_view fileName, std::string_view objClassNameLocation,
		std::string_view funcLocation, std::string_view varName, const bool& removeFromAllObjects);
	void _destructorObj(const void* obj, std::string_view fileName, std::string_view objClassName);

	void debugMessage(std::string_view message) {
		(*m_stream) << message;
	}

};

namespace DebugSettings {
	inline bool I_SHOWCOLLISIONBOXES{ false };
}

#endif