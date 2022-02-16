#include "zone.h"

Zone::Zone(const Point& botLeft, const Point& topRight, const int& minCellSize, std::vector<Zone*>& lowestZones) :
	m_botLeft{ botLeft }, m_topRight{ topRight } {
#ifdef _DEBUG
	DEBUG_CONSTRUCTOR_OBJ(this, Source_Files::quadTree_cpp, &mS_objectsCount);
#endif

	if (!(abs(m_topRight.x - m_botLeft.x) <= minCellSize) &&
		!(abs(m_topRight.y - m_botLeft.y) <= minCellSize))
	{
		m_subZoneTopLeft = new Zone{
		Point{m_botLeft.x, (m_botLeft.y + m_topRight.y) / 2 },
		Point{(m_botLeft.x + m_topRight.x) / 2, m_topRight.y}, minCellSize,lowestZones
		};

		m_subZoneTopRight = new Zone{
		Point{(m_botLeft.x + m_topRight.x) / 2, (m_botLeft.y + m_topRight.y) / 2}, m_topRight, minCellSize, lowestZones
		};

		m_subZoneBotLeft = new Zone{
		m_botLeft, Point{(m_botLeft.x + m_topRight.x) / 2, (m_botLeft.y + m_topRight.y) / 2}, minCellSize,lowestZones
		};

		m_subZoneBotRight = new Zone{
		Point{(m_botLeft.x + m_topRight.x) / 2, m_botLeft.y },
		Point{m_topRight.x, (m_botLeft.y + m_topRight.y) / 2}, minCellSize,lowestZones
		};
	}
	else {
		lowestZones.push_back(this);
	}
}

Zone::~Zone() {
#ifdef _DEBUG
	DEBUG_DESTRUCTOR_OBJ(this, Source_Files::quadTree_cpp);
	delete m_subZoneBotLeft;
	delete m_subZoneBotRight;
	delete m_subZoneTopLeft;
	delete m_subZoneTopRight;
#endif
}

void Zone::addObj(Entity& entity) {
	m_entities.push_back(&entity);
}
void Zone::addObj(BasicBlock& basicBlock) {
	m_basicBlocks.push_back(&basicBlock);
}
void Zone::addObj(Text& text) {
	m_texts.push_back(&text);
}