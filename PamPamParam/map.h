#pragma once
#include "utils.h"
#include "entity.h"
#include "basicBlock.h"
#include "text.h"
#include "zone.h"

// creating a huge map will load slowly and it will not work
class Map
{
	Point m_botLeft{};
	Point m_topRight{};

	int m_maxDepth{};
	Zone* m_currentZone{};

	std::vector<Zone*> m_lowestZones{};

	Zone* m_subZoneTopLeft{};
	Zone* m_subZoneTopRight{};
	Zone* m_subZoneBotLeft{};
	Zone* m_subZoneBotRight{};

	//sorts m_lowestZones then links lowestsZones
	void linkLowestZones();

public:
	std::vector<BasicBlock*> forTestingOnly{}; // de modificat
	~Map();
	Map(const Map& quadTree) = delete;
	Map& operator=(const Map& quadTree) = delete;
	// minCellSize should be large >= 500
	Map(const Point& botLeft, const Point& topRight, const int& minCellSize);

#ifdef _DEBUG
	// for testing purposes only

	void printId(Zone* zone);

	void printIds();

	void moveNorth();
	void moveEast();
	void moveSouth();
	void moveWest();
	void printCurrentZoneId() {
		if (m_currentZone) {
			std::cout << m_currentZone->m_id << '\n';
		}
	}

#endif
#ifdef _DEBUG
private:
	static inline ObjectsCount mS_objectsCount{};
#endif
};


