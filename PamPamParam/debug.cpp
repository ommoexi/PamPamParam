#ifdef _DEBUG
#include "debug.h"
namespace {
	const char* infoString{ "info ::" };
	const char* warningString{ "WARNING ::" };
	const char* dangerString{ "DANGER ::" };
	//info + obj
	const char* objCreationString{ " OBJECT_CREATION :: " };
	const char* objectForDeletionNotFound{ " OBJECT_FOR_DELETION_NOT_FOUND :: " };
	const char* objDeletionString{ " OBJECT_DELETION :: " };
	const char* noObjectsCount{ " NO OBJECTS_COUNT " };
	const char* zeroObjects{ " ZERO_OBJECTS :: " };

	const char* fileString{ "FILE :: " };
	const char* classString{ "CLASS :: " };
	const char* functionString{ "FUNCTION :: " };
	const char* varNameString{ "VAR_NAME :: " };

	const char* delimitatorString{ " || " };
	const char* constructorString{ "constructor" };
	const char* destructorString{ "destructor" };
	const char* locationString{ " |||| LOCATION :: " };
	const char* newLocationString{ " |||| NEW LOCATION :: " };
	const char* previousLocationString{ " |||| PREVIOUS_LOCATION :: " };

}

Debugger::~Debugger() {
#ifdef _DANGER
	if (m_allObjects.size() != 0) {
		*m_stream << dangerString << " OBJECTS_LEFT_IN_FREE_STORE :: " << m_allObjects.size() << '\n';
	}
#endif
}

void Debugger::_addObj(const void* obj, std::string_view objClassName, std::string_view varName,
	std::string_view fileName, std::string_view objClassNameLocation, std::string_view funcLocation) {

	Data& allObjectsData{ m_allObjects[obj] };

	if (!objClassName.empty()) {
		allObjectsData.setClassName(objClassName);
	}

#ifdef _INFO
	* m_stream << infoString << objCreationString << classString << objClassName;
#endif
	if (!varName.empty()) {
#ifdef _INFO
		* m_stream << delimitatorString << varNameString << varName;
#endif
		allObjectsData.setVarName(varName);
	}
#ifdef _INFO
	* m_stream << locationString;
#endif
	if (!fileName.empty()) {
#ifdef _INFO
		* m_stream << fileString << fileName << delimitatorString;
#endif
		allObjectsData.setFileName(fileName);
	}
	if (!objClassNameLocation.empty()) {
#ifdef _INFO
		* m_stream << classString << objClassNameLocation << delimitatorString;
#endif
		allObjectsData.setClassNameLocation(objClassNameLocation);
	}
	if (!funcLocation.empty()) {
#ifdef _INFO
		* m_stream << functionString << funcLocation;
#endif
		allObjectsData.setFunctionLocation(funcLocation);
	}
#ifdef _INFO
	* m_stream << '\n';
#endif


}

void Debugger::_constructorObj(const void* obj, std::string_view fileName, std::string_view objClassName,
	ObjectsCount* objectsCount) {

	Data& allObjectsData{ m_allObjects[obj] };

	allObjectsData.setClassName(objClassName);

	if (objectsCount != nullptr) {
		*objectsCount += 1;
		if (allObjectsData.objectsCount() != nullptr) {
			*allObjectsData.objectsCount() -= 1;
		}
		allObjectsData.setObjectsCount(objectsCount);
	}
#ifdef _DANGER // NO OBJECTS
	else {
		*m_stream << dangerString << objCreationString << fileString << fileName << delimitatorString
			<< classString << objClassName << delimitatorString << noObjectsCount << '\n';
	}
#endif

#ifdef _INFO // SUCCESS
	* m_stream << infoString << objCreationString << fileString << fileName << delimitatorString
		<< classString << objClassName << delimitatorString << constructorString << '\n';
#endif

}

void Debugger::_destructorObj(const void* obj, std::string_view fileName, std::string_view objClassName) {
	if (m_allObjects.count(obj) != 0) {
		Data& data{ m_allObjects[obj] };
		if (data.objectsCount() != nullptr) {
			*data.objectsCount() -= 1;
		}
#ifdef _DANGER // NO OBJECTS
		else {
			*m_stream << dangerString << objDeletionString << fileString << fileName << delimitatorString
				<< classString << data.className() << delimitatorString << noObjectsCount << '\n';
		}
#endif
#ifdef _INFO // success
		* m_stream << infoString << objDeletionString << fileString << fileName << delimitatorString
			<< classString << data.className() << delimitatorString <<
			destructorString << '\n';
		if (data.objectsCount() != nullptr && *data.objectsCount() == 0) {
			*m_stream << infoString << zeroObjects << classString << data.className() << '\n';
		}
#endif

		m_allObjects.erase(obj);

	}
#ifdef _DANGER // NO DATA
	else {
		*m_stream << dangerString << objectForDeletionNotFound << classString << objClassName << '\n';
	}
#endif
}

void Debugger::_removeObj(const void* obj, std::string_view fileName, std::string_view objClassNameLocation,
	std::string_view funcLocation, std::string_view varName, const bool& removeFromAllObjects) {
	if (m_allObjects.count(obj) != 0) {
		Data& data{ m_allObjects[obj] };
#ifdef _INFO // success
		* m_stream << infoString << objDeletionString << classString << data.className();
		*m_stream << previousLocationString;

		if (!data.fileName().empty()) {
			*m_stream << fileString << data.fileName() << delimitatorString;
		}
		if (!data.classNameLocation().empty()) {
			*m_stream << classString << data.classNameLocation() << delimitatorString;
		}
		if (!data.functionLocation().empty()) {
			*m_stream << functionString << data.functionLocation();
		}
		if (!data.varName().empty()) {
			*m_stream << delimitatorString << varNameString << data.varName();
		}

		*m_stream << newLocationString;

		if (!fileName.empty()) {
			*m_stream << fileString << fileName << delimitatorString;
		}
		if (!objClassNameLocation.empty()) {
			*m_stream << classString << objClassNameLocation << delimitatorString;
		}
		if (!funcLocation.empty()) {
			*m_stream << functionString << funcLocation;
		}
		if (!varName.empty()) {
			*m_stream << delimitatorString << varNameString << varName;
		}
		*m_stream << '\n';
#endif

		if (removeFromAllObjects) {
			m_allObjects.erase(obj);
	}
}
#ifdef _DANGER // NO DATA
	else {
		*m_stream << dangerString << objectForDeletionNotFound;
		if (!fileName.empty()) {
			*m_stream << fileString << fileName << delimitatorString;
		}
		if (!objClassNameLocation.empty()) {
			*m_stream << classString << objClassNameLocation << delimitatorString;
		}
		if (!funcLocation.empty()) {
			*m_stream << functionString << funcLocation;
		}
		if (!varName.empty()) {
			*m_stream << delimitatorString << varNameString << varName;
		}
		*m_stream << '\n';
	}
#endif
}


#endif