#include "map.h"


Map::Map(const Point& botLeft, const Point& topRight, const int& minCellSize) :m_botLeft{ botLeft },
m_topRight{ topRight }{
#ifdef _DEBUG
	DEBUG_CONSTRUCTOR_OBJ(this, Source_Files::quadTree_cpp, &mS_objectsCount);
#endif

	if (!(abs(m_topRight.x - m_botLeft.x) <= minCellSize) &&
		!(abs(m_topRight.y - m_botLeft.y) <= minCellSize))
	{
		m_subZoneTopLeft = new Zone{
		Point{m_botLeft.x, (m_botLeft.y + m_topRight.y) / 2 },
		Point{(m_botLeft.x + m_topRight.x) / 2, m_topRight.y}, minCellSize, m_lowestZones
		};

		m_subZoneTopRight = new Zone{
		Point{(m_botLeft.x + m_topRight.x) / 2, (m_botLeft.y + m_topRight.y) / 2}, m_topRight, minCellSize, m_lowestZones
		};

		m_subZoneBotLeft = new Zone{
		m_botLeft, Point{(m_botLeft.x + m_topRight.x) / 2, (m_botLeft.y + m_topRight.y) / 2}, minCellSize, m_lowestZones
		};


		m_subZoneBotRight = new Zone{
		Point{(m_botLeft.x + m_topRight.x) / 2, m_botLeft.y },
		Point{m_topRight.x, (m_botLeft.y + m_topRight.y) / 2}, minCellSize, m_lowestZones
		};

	}

	if (m_subZoneBotLeft && m_subZoneBotRight && m_subZoneTopLeft && m_subZoneTopRight) {
		m_subZoneBotLeft->setNorth(m_subZoneTopLeft).setEast(m_subZoneBotRight);
		m_subZoneBotRight->setNorth(m_subZoneTopRight).setWest(m_subZoneBotLeft);
		m_subZoneTopLeft->setSouth(m_subZoneBotLeft).setEast(m_subZoneTopRight);
		m_subZoneTopRight->setSouth(m_subZoneBotRight).setWest(m_subZoneTopLeft);

		Zone* iterator{ m_subZoneTopLeft };
		while (iterator) {
			iterator = iterator->subZoneTopLeft();
			m_maxDepth++;
		}

		linkLowestZones();

		// momentan las asa dar trebuie modificat
		Zone* test{ m_subZoneTopLeft };
		while (test->subZoneTopLeft()) {
			test = test->subZoneTopLeft();
		}
		m_currentZone = test;

	}

#ifdef _DEBUG
	else {
		debugMessage("MAP NO SUBZONES\n");
	}
#endif

}

void Map::linkLowestZones() {
	std::sort(m_lowestZones.begin(), m_lowestZones.end(), [](Zone*& leftZone, Zone*& rightZone)
		{
			return leftZone->botLeft().y < rightZone->botLeft().y;
		});
	size_t rowsColSize{ static_cast<size_t>(sqrt(m_lowestZones.size())) };
	size_t i{};
	for (size_t k{ rowsColSize }; k < m_lowestZones.size() + 1; i += rowsColSize, k += rowsColSize) {
		std::sort(m_lowestZones.begin() + i, m_lowestZones.begin() + k, [](Zone*& leftZone, Zone*& rightZone)
			{
				return leftZone->botLeft().x < rightZone->botLeft().x;
			});
	}
	// link horizontally
	for (size_t i{ rowsColSize }; i < m_lowestZones.size() + 1; i+= rowsColSize) {
		for (size_t k{ i - rowsColSize + 1 }; k < i; k++) {
			Zone* leftZone{ m_lowestZones[k - 1] };
			Zone* rightZone{ m_lowestZones[k] };
			leftZone->setEast(rightZone);
			rightZone->setWest(leftZone);		
		}
	}
	// link vertically
	for (size_t i{ }; i < rowsColSize; i++) {
		for (size_t k{ i + rowsColSize }; k < m_lowestZones.size(); k+= rowsColSize) {
			Zone* downZone{ m_lowestZones[k - rowsColSize ] };
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
	else {
		std::cout << "NO NORTH \n";
	}
}
void Map::moveEast() {
	if (m_currentZone->east()) {
		m_currentZone = m_currentZone->east();
	}
	else {
		std::cout << "NO EAST \n";
	}
}
void Map::moveSouth() {
	if (m_currentZone->south()) {
		m_currentZone = m_currentZone->south();
	}
	else {
		std::cout << "NO SOUTH \n";
	}
}
void Map::moveWest() {
	if (m_currentZone->west()) {
		m_currentZone = m_currentZone->west();
	}
	else {
		std::cout << "NO WEST \n";
	}
}

void Map::addObj(Entity& entity, const bool& useDeleteWhenRemoved) {
	//m_entities.push_back(&entity);
	entity.setUseDeleteWhenRemoved(useDeleteWhenRemoved);
}
void Map::addObj(BasicBlock& basicBlock, const bool& useDeleteWhenRemoved) {
	//m_basicBlocks.push_back(&basicBlock);
	basicBlock.setUseDeleteWhenRemoved(useDeleteWhenRemoved);
}

void Map::addObj(Text& text, const bool& useDeleteWhenRemoved) {
	//m_texts.push_back(&text);
	text.setUseDeleteWhenRemoved(useDeleteWhenRemoved);
}

Zone* Map::getZone(Object* obj) const {

	if (obj->x() <= m_topRight.x && obj->x() > m_botLeft.x && obj->y() <= m_topRight.y && obj->y() >= m_botLeft.y) {
		m_subZoneTopLeft = new Zone{
		Point{m_botLeft.x, (m_botLeft.y + m_topRight.y) / 2 },
		Point{(m_botLeft.x + m_topRight.x) / 2, m_topRight.y}, minCellSize, m_lowestZones
		};

		m_subZoneTopRight = new Zone{
		Point{(m_botLeft.x + m_topRight.x) / 2, (m_botLeft.y + m_topRight.y) / 2}, m_topRight, minCellSize, m_lowestZones
		};

		m_subZoneBotLeft = new Zone{
		m_botLeft, Point{(m_botLeft.x + m_topRight.x) / 2, (m_botLeft.y + m_topRight.y) / 2}, minCellSize, m_lowestZones
		};


		m_subZoneBotRight = new Zone{
		Point{(m_botLeft.x + m_topRight.x) / 2, m_botLeft.y },
		Point{m_topRight.x, (m_botLeft.y + m_topRight.y) / 2}, minCellSize, m_lowestZones
		};
	}
#ifdef _DEBUG
	debugMessage("CANNOT INSERT OBJ IN MAP OUT OF BOUNDS\n");
#endif
	
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
