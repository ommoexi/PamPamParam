#include "zone.h"

Zone::Zone(const Point& botLeft, const Point& topRight, const int& minCellSize, std::vector<Zone*>& lowestZones) : 
	m_coords{ botLeft, topRight }
	 {
#ifdef _DEBUG
	DEBUG_CONSTRUCTOR_OBJ(this, Source_Files::quadTree_cpp, &mS_objectsCount);
#endif

	if (!(abs(m_coords.x2 - m_coords.x) <= minCellSize) &&
		!(abs(m_coords.y2 - m_coords.y) <= minCellSize))
	{
		m_subZoneTopLeft = new Zone{
		Point{m_coords.x, (m_coords.y + m_coords.y2) / 2 },
		Point{(m_coords.x + m_coords.x2) / 2, m_coords.y2}, minCellSize, lowestZones
		};

		m_subZoneTopRight = new Zone{
		Point{(m_coords.x + m_coords.x2) / 2, (m_coords.y + m_coords.y2) / 2}, Point{m_coords.x2, m_coords.y2}, minCellSize, lowestZones
		};

		m_subZoneBotLeft = new Zone{
		Point{m_coords.x, m_coords.y}, Point{(m_coords.x + m_coords.x2) / 2, (m_coords.y + m_coords.y2) / 2}, minCellSize, lowestZones
		};


		m_subZoneBotRight = new Zone{
		Point{(m_coords.x + m_coords.x2) / 2, m_coords.y },
		Point{m_coords.x2, (m_coords.y + m_coords.y2) / 2}, minCellSize, lowestZones
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

Zone* Zone::getZone(Object* obj) const {
	const float& x{ obj->x() };
	const float& y{ obj->y() };
	if (x >= m_coords.x && x <= m_coords.y2 && y >= m_coords.y && y <= m_coords.y2) {
		// left
		if (x <= m_coords.middleX) {
			//down
			if (y <= m_coords.middleY) {

			}
			else {

			}
			//up
		}
		// right
		else {
			//down
			if (y <= m_coords.middleY) {

			}
			else {

			}
			//up
		}
	}
}