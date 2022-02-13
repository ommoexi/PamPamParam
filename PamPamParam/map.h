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
	~Map();
	Map(const Map& map) = delete;
	Map& operator=(const Map& map) = delete;
	// minCellSize should be large >= 500
	Map(const Point& botLeft, const Point& topRight, const int& minCellSize);

	void moveNorth();
	void moveEast();
	void moveSouth();
	void moveWest();

#ifdef _DEBUG
private:
	static inline ObjectsCount mS_objectsCount{};
#endif
};


