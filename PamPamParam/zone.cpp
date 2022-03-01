#include "zone.h"

Zone::Zone(const Point& botLeft, const Point& topRight, const int& minCellSize, std::vector<Zone*>& lowestZones) : 
	m_coords{ botLeft, topRight }
	 {
#ifdef _DEBUG
	DEBUG_CONSTRUCTOR_OBJ(this, Source_Files::zone_cpp, &mS_objectsCount);
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

Zone::Zone() {
#ifdef _DEBUG
	DEBUG_CONSTRUCTOR_OBJ(this, Source_Files::zone_cpp, &mS_objectsCount);
#endif
}

Zone::~Zone() {
#ifdef _DEBUG
	DEBUG_DESTRUCTOR_OBJ(this, Source_Files::zone_cpp);
	delete m_subZoneBotLeft;
	delete m_subZoneBotRight;
	delete m_subZoneTopLeft;
	delete m_subZoneTopRight;

	for (size_t i{}; i < m_entities.size(); i++) {
		Entity*& entity{ m_entities[i] };
		if (!entity->isDeleted() && entity->useDeleteWhenRemoved()) {
			delete entity;
		}
	}
	for (size_t i{}; i < m_basicBlocks.size(); i++) {
		BasicBlock*& basicBlock{ m_basicBlocks[i] };
		if (!basicBlock->isDeleted() && basicBlock->useDeleteWhenRemoved()) {
			delete basicBlock;
		}
	}
	for (size_t i{}; i < m_texts.size(); i++) {
		Text*& text{ m_texts[i] };
		if (!text->isDeleted() && text->useDeleteWhenRemoved()) {
			delete text;
		}
	}
#endif
}

void Zone::addObj(Entity& entity) {
	m_entities.push_back(&entity);
	entity.setBottomLeftBounds(m_coords.x, m_coords.y);
	entity.setTopRightBounds(m_coords.x2, m_coords.y2);
}
void Zone::addObj(BasicBlock& basicBlock) {
	m_basicBlocks.push_back(&basicBlock);
	basicBlock.setBottomLeftBounds(m_coords.x, m_coords.y);
	basicBlock.setTopRightBounds(m_coords.x2, m_coords.y2);
}
void Zone::addObj(Text& text) {
	m_texts.push_back(&text);
	text.setBottomLeftBounds(m_coords.x, m_coords.y);
	text.setTopRightBounds(m_coords.x2, m_coords.y2);
}

Zone* Zone::getZone(const Object& obj) {
	const float& x{ obj.x() };
	const float& y{ obj.y() };
	if (x >= m_coords.x && x <= m_coords.x2 && y >= m_coords.y && y <= m_coords.y2) {
		// left
		if (x <= m_coords.middleX) {
			//down
			if (y <= m_coords.middleY) {
				if (m_subZoneBotLeft) return m_subZoneBotLeft->getZone(obj);
			}
			//up
			else {
				if (m_subZoneTopLeft) return m_subZoneTopLeft->getZone(obj);
			}

		}
		// right
		else {
			//down
			if (y <= m_coords.middleY) {
				if (m_subZoneBotRight) return m_subZoneBotRight->getZone(obj);
			}
			//up
			else {
				if (m_subZoneTopRight) return m_subZoneTopRight->getZone(obj);
			}
		}
	}
	return this;
}

bool Zone::isObjInBounds(const Object& obj) {
	return (obj.x() <= m_coords.x2 && obj.x() >= m_coords.x && obj.y() <= m_coords.y2 && obj.y() >= m_coords.y);
}