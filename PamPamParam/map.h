#pragma once
#include "utils.h"
#include "entity.h"
#include "basicBlock.h"
#include "text.h"
#include "zone.h"

class Map
{
	Point m_botLeft{};
	Point m_topRight{};

	int m_maxDepth{};
	Zone* m_currentZone{};

	Zone* m_subZoneTopLeft{};
	Zone* m_subZoneTopRight{};
	Zone* m_subZoneBotLeft{};
	Zone* m_subZoneBotRight{};

	void linkZones();

public:
	~Map();
	Map(const Map& quadTree) = delete;
	Map& operator=(const Map& quadTree) = delete;
	Map(const Point& botLeft, const Point& topRight, const int& minCellSize);

#ifdef _DEBUG
private:
	static inline ObjectsCount mS_objectsCount{};
#endif
};


