#include "map.h"

Map::Map(const Point& botLeft, const Point& topRight, const int& minCellSize, const unsigned int& updateRadius,
	const unsigned int& renderRadius, Player* mainPlayer) : m_coords{ botLeft, topRight }, m_updateRadius{ updateRadius },
	m_renderRadius{ renderRadius }, m_mainPlayer{ mainPlayer }
{
#ifdef _DEBUG
	DEBUG_CONSTRUCTOR_OBJ(this, Source_Files::map_cpp, &mS_objectsCount);
#endif

	if (m_updateRadius == 0) {
		m_updateRadius = 1;
	}
	if (m_renderRadius == 0) {
		m_renderRadius = 1;
	}

	if (!(mainPlayer->x() >= m_coords.x && mainPlayer->x() < m_coords.x2 && mainPlayer->y() >= m_coords.y && mainPlayer->y() <= m_coords.y2)) {
		mainPlayer->setX(static_cast<float>(m_coords.middleX));
		mainPlayer->setY(static_cast<float>(m_coords.middleY));
	}

	if (!(abs(m_coords.x2 - m_coords.x) <= minCellSize) &&
		!(abs(m_coords.y2 - m_coords.y) <= minCellSize))
	{
		m_subZoneTopLeft = new Zone{
		Point{m_coords.x, (m_coords.y + m_coords.y2) / 2 },
		Point{(m_coords.x + m_coords.x2) / 2, m_coords.y2}, minCellSize, m_lowestZones
		};

		m_subZoneTopRight = new Zone{
		Point{(m_coords.x + m_coords.x2) / 2, (m_coords.y + m_coords.y2) / 2}, Point{m_coords.x2, m_coords.y2}, minCellSize, m_lowestZones
		};

		m_subZoneBotLeft = new Zone{
		Point{m_coords.x, m_coords.y}, Point{(m_coords.x + m_coords.x2) / 2, (m_coords.y + m_coords.y2) / 2}, minCellSize, m_lowestZones
		};


		m_subZoneBotRight = new Zone{
		Point{(m_coords.x + m_coords.x2) / 2, m_coords.y },
		Point{m_coords.x2, (m_coords.y + m_coords.y2) / 2}, minCellSize, m_lowestZones
		};

	}

	if (m_subZoneBotLeft && m_subZoneBotRight && m_subZoneTopLeft && m_subZoneTopRight) {
		linkLowestZones();

		setCurrentZone(*m_mainPlayer);

	}
	else {
#ifdef _DEBUG
		debugMessage("MAP TOO SMALL");
#endif
	}

}

void Map::linkLowestZones() {
	std::sort(m_lowestZones.begin(), m_lowestZones.end(), [](Zone*& leftZone, Zone*& rightZone)
		{
			return leftZone->coords().y < rightZone->coords().y;
		});
	size_t rowsColSize{ static_cast<size_t>(sqrt(m_lowestZones.size())) };
	size_t i{};
	for (size_t k{ rowsColSize }; k < m_lowestZones.size() + 1; i += rowsColSize, k += rowsColSize) {
		std::sort(m_lowestZones.begin() + i, m_lowestZones.begin() + k, [](Zone*& leftZone, Zone*& rightZone)
			{
				return leftZone->coords().x < rightZone->coords().x;
			});
	}
	// link horizontally
	for (size_t i{ rowsColSize }; i < m_lowestZones.size() + 1; i += rowsColSize) {
		for (size_t k{ i - rowsColSize + 1 }; k < i; k++) {
			Zone* leftZone{ m_lowestZones[k - 1] };
			Zone* rightZone{ m_lowestZones[k] };
			leftZone->setEast(rightZone);
			rightZone->setWest(leftZone);
		}
	}
	// link vertically
	for (size_t i{ }; i < rowsColSize; i++) {
		for (size_t k{ i + rowsColSize }; k < m_lowestZones.size(); k += rowsColSize) {
			Zone* downZone{ m_lowestZones[k - rowsColSize] };
			Zone* upZone{ m_lowestZones[k] };
			downZone->setNorth(upZone);
			upZone->setSouth(downZone);
		}
	}

}

void Map::moveNorth() {
	if (m_currentZone->north()) {
		m_currentZone = m_currentZone->north();
	}
#ifdef _DEBUG
	else {
		debugMessage("CAN'T MOVE MAP NORTH\n");
	}
#endif
}
void Map::moveEast() {
	if (m_currentZone->east()) {
		m_currentZone = m_currentZone->east();
	}
#ifdef _DEBUG
	else {
		debugMessage("CAN'T MOVE MAP EAST\n");
	}
#endif
}
void Map::moveSouth() {
	if (m_currentZone->south()) {
		m_currentZone = m_currentZone->south();
	}
#ifdef _DEBUG
	else {
		debugMessage("CAN'T MOVE MAP SOUTH\n");
	}
#endif
}
void Map::moveWest() {
	if (m_currentZone->west()) {
		m_currentZone = m_currentZone->west();
	}
#ifdef _DEBUG
	else {
		debugMessage("CAN'T MOVE MAP WEST\n");
	}
#endif
}

void Map::setCurrentZone(const Object& obj) {
	Zone* zone{ getZone(obj) };
	if (zone) {
		m_currentZone = zone;
	}
#ifdef _DEBUG
	else {
		debugMessage("CAN'T SET CURRENT ZONE OUT OF BOUNDS!\n");
	}
#endif
}

void Map::addObj(Entity& entity, const bool& useDeleteWhenRemoved) {
	Zone* zone{ getZone(entity) };
	if (zone) {
		entity.setUseDeleteWhenRemoved(useDeleteWhenRemoved);
		zone->addObj(entity);
	}
}
void Map::addObj(BasicBlock& basicBlock, const bool& useDeleteWhenRemoved) {
	Zone* zone{ getZone(basicBlock) };
	if (zone) {
		basicBlock.setUseDeleteWhenRemoved(useDeleteWhenRemoved);
		zone->addObj(basicBlock);
	}
}

void Map::addObj(Text& text, const bool& useDeleteWhenRemoved) {
	Zone* zone{ getZone(text) };
	if (zone) {
		text.setUseDeleteWhenRemoved(useDeleteWhenRemoved);
		zone->addObj(text);
	}
}

Zone* Map::getZone(const Object& obj) const {
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
#ifdef _DEBUG
	else {
		debugMessage("CANNOT GET ZONE WITH OBJ IN MAP OUT OF BOUNDS\n");
	}
#endif
	return nullptr;
}

Map::~Map() {
#ifdef _DEBUG
	DEBUG_DESTRUCTOR_OBJ(this, Source_Files::map_cpp);
	delete m_subZoneBotLeft;
	delete m_subZoneBotRight;
	delete m_subZoneTopLeft;
	delete m_subZoneTopRight;
#endif
}

void Map::setVectors(ZoneVectors& vectors, unsigned int radius) {
	vectors.basicBlocks.clear();
	vectors.entities.clear();
	vectors.texts.clear();

	vectors.basicBlocks.push_back(&m_currentZone->m_basicBlocks);
	vectors.texts.push_back(&m_currentZone->m_texts);
	vectors.entities.push_back(&m_currentZone->m_entities);

}

void Map::setUpdateVectors() {
	setVectors(m_updateVectors, m_updateRadius);
}
void Map::setRenderVectors() {
	setVectors(m_renderVectors, m_renderRadius);
}
