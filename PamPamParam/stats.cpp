#include "stats.h"

Stats::Stats() {
#ifdef _DEBUG
	DEBUG_CONSTRUCTOR_OBJ(this, Source_Files::stats_cpp, &mS_objectsCount);
#endif
}

Stats::Stats(const float& movementSpeed, const float& jumpSpeed, const float& attackSpeed) : m_movementSpeed{ movementSpeed }, 
m_jumpSpeed{ jumpSpeed }, m_attackSpeed{ attackSpeed } {
#ifdef _DEBUG
	DEBUG_CONSTRUCTOR_OBJ(this, Source_Files::stats_cpp, &mS_objectsCount);
#endif
}

Stats::Stats(const Stats& other) : Stats{ other.m_movementSpeed, other.m_jumpSpeed, other.m_attackSpeed } {

}

Stats::~Stats() {
#ifdef _DEBUG
	DEBUG_DESTRUCTOR_OBJ(this, Source_Files::stats_cpp);
#endif

}