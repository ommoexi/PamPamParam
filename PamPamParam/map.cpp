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
		Point{(m_botLeft.x + m_topRight.x) / 2, m_topRight.y}, minCellSize, 1, m_lowestZones
		};

		m_subZoneTopRight = new Zone{
		Point{(m_botLeft.x + m_topRight.x) / 2, (m_botLeft.y + m_topRight.y) / 2}, m_topRight, minCellSize, 2, m_lowestZones
		};

		m_subZoneBotLeft = new Zone{
		m_botLeft, Point{(m_botLeft.x + m_topRight.x) / 2, (m_botLeft.y + m_topRight.y) / 2}, minCellSize, 3, m_lowestZones
		};


		m_subZoneBotRight = new Zone{
		Point{(m_botLeft.x + m_topRight.x) / 2, m_botLeft.y },
		Point{m_topRight.x, (m_botLeft.y + m_topRight.y) / 2}, minCellSize, 4, m_lowestZones
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
			///    de modificat
			forTestingOnly.push_back(new BasicBlock(leftZone->botLeft().x, leftZone->botLeft().y, 
				(leftZone->topRight().x - leftZone->botLeft().x),
				(leftZone->topRight().y - leftZone->botLeft().y),
				Textures::splitTest));
			// ******************************************************
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

#ifdef _DEBUG

void Map::printId(Zone* zone) {
	Zone* currentZone{ zone };
	while (currentZone) {
		std::cout << currentZone->m_id << " X: " << currentZone->botLeft().x << " Y: " << currentZone->botLeft().y << '\n';
		currentZone = currentZone->subZoneTopLeft();
	}
	currentZone = zone;
	while (currentZone) {
		std::cout << currentZone->m_id << " X: " << currentZone->botLeft().x << " Y: " << currentZone->botLeft().y << '\n';
		currentZone = currentZone->subZoneTopRight();
	}
	currentZone = zone;
	while (currentZone) {
		std::cout << currentZone->m_id << " X: " << currentZone->botLeft().x << " Y: " << currentZone->botLeft().y << '\n';
		currentZone = currentZone->subZoneBotLeft();
	}
	currentZone = zone;
	while (currentZone) {
		std::cout << currentZone->m_id << " X: " << currentZone->botLeft().x << " Y: " << currentZone->botLeft().y << '\n';
		currentZone = currentZone->subZoneBotRight();
	}
}
int i{};
void Map::printIds() {
	printId(m_subZoneTopLeft);
	printId(m_subZoneTopRight);
	printId(m_subZoneBotLeft);
	printId(m_subZoneBotRight);
}

void Map::moveNorth() {
	if (m_currentZone->north() && i >= 50) {
		m_currentZone = m_currentZone->north();
		std::cout << m_currentZone->m_id << " x : " << m_currentZone->m_botLeft.x << " y : " << m_currentZone->m_botLeft.y << '\n';
		i = 0;
	}
	else  if (i >= 50) {
		std::cout << "NO NORTH \n";
		i = 0;
	}
	i++;
}
void Map::moveEast() {
	if (m_currentZone->east() && i >= 50) {
		m_currentZone = m_currentZone->east();
		std::cout << m_currentZone->m_id << " x : " << m_currentZone->m_botLeft.x << " y : " << m_currentZone->m_botLeft.y << '\n';
		i = 0;
	}
	else if (i >= 50) {
		std::cout << "NO EAST \n";
		i = 0;
	}
	i++;
}
void Map::moveSouth() {
	if (m_currentZone->south() && i >= 50) {
		m_currentZone = m_currentZone->south();
		std::cout << m_currentZone->m_id << " x : " << m_currentZone->m_botLeft.x << " y : " << m_currentZone->m_botLeft.y << '\n';
		i = 0;
	}
	else if (i >= 50) {
		std::cout << "NO SOUTH \n";
		i = 0;
	}
	i++;
}
void Map::moveWest() {
	if (m_currentZone->west() && i >= 50) {
		m_currentZone = m_currentZone->west();
		std::cout << m_currentZone->m_id << " x : " << m_currentZone->m_botLeft.x << " y : " << m_currentZone->m_botLeft.y << '\n';
		i = 0;
	}
	else if (i >= 50) {
		std::cout << "NO WEST \n";
		i = 0;
	}
	i++;
}


#endif

Map::~Map() {
#ifdef _DEBUG
	DEBUG_DESTRUCTOR_OBJ(this, Source_Files::quadTree_cpp);
	delete m_subZoneBotLeft;
	delete m_subZoneBotRight;
	delete m_subZoneTopLeft;
	delete m_subZoneTopRight;
#endif
}
