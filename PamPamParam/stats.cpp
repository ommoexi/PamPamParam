#include "stats.h"

Stats::Stats() {
#ifdef _DEBUG
	DEBUG_CONSTRUCTOR_OBJ(this, Source_Files::stats_cpp, &mS_objectsCount);
#endif
}

Stats::Stats(const float& movementSpeed, const float& jumpSpeed) : m_movementSpeed{ movementSpeed }, m_jumpSpeed{ jumpSpeed } {
#ifdef _DEBUG
	DEBUG_CONSTRUCTOR_OBJ(this, Source_Files::stats_cpp, &mS_objectsCount);
#endif
}

Stats::Stats(const Stats& other) : Stats{ other.m_movementSpeed, other.m_jumpSpeed } {

}

Stats::~Stats() {
#ifdef _DEBUG
	DEBUG_DESTRUCTOR_OBJ(this, Source_Files::stats_cpp);
#endif

}