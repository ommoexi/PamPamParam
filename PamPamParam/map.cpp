#include "map.h"


Map::Map(const Point& botLeft, const Point& topRight, const int& minCellSize) :m_botLeft{ botLeft },
m_topRight{ topRight }{
#ifdef _DEBUG
	DEBUG_CONSTRUCTOR_OBJ(this, Source_Files::quadTree_cpp, &mS_objectsCount);
#endif

	int _{ 0 }; // update depth only on one

	if (!(abs(m_topRight.x - m_botLeft.x) <= minCellSize) &&
		!(abs(m_topRight.y - m_botLeft.y) <= minCellSize))
	{
		m_subZoneBotLeft = new Zone{
		m_botLeft, Point{(m_botLeft.x + m_topRight.x) / 2, (m_botLeft.y + m_topRight.y) / 2}, minCellSize, m_maxDepth
		};

		m_subZoneTopLeft = new Zone{
		Point{m_botLeft.x, (m_botLeft.y + m_topRight.y) / 2 },
		Point{(m_botLeft.x + m_topRight.x) / 2, m_topRight.y}, minCellSize, _
		};

		m_subZoneBotRight = new Zone{
		Point{(m_botLeft.x + m_topRight.x) / 2, m_botLeft.y },
		Point{m_botLeft.x + m_topRight.x, (m_botLeft.y + m_topRight.y) / 2}, minCellSize, _
		};

		m_subZoneTopRight = new Zone{
		Point{(m_botLeft.x + m_topRight.x) / 2, (m_botLeft.y + m_topRight.y) / 2}, m_topRight, minCellSize, _
		};
	}
	m_maxDepth++;
	linkZones();
}

void Map::linkZones() {
	m_subZoneBotLeft->setNorth(m_subZoneTopLeft).setEast(m_subZoneBotRight);
	m_subZoneBotRight->setNorth(m_subZoneTopRight).setWest(m_subZoneBotLeft);
	m_subZoneTopLeft->setSouth(m_subZoneBotLeft).setEast(m_subZoneTopRight);
	m_subZoneTopRight->setSouth(m_subZoneBotRight).setWest(m_subZoneTopLeft);

	
}

Map::~Map() {
#ifdef _DEBUG
	DEBUG_DESTRUCTOR_OBJ(this, Source_Files::quadTree_cpp);
	delete m_subZoneBotLeft;
	delete m_subZoneBotRight;
	delete m_subZoneTopLeft;
	delete m_subZoneTopRight;
#endif
}
