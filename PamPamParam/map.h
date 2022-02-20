#pragma once
#include "utils.h"
#include "entity.h"
#include "basicBlock.h"
#include "text.h"
#include "zone.h"
#include "player.h"

// creating a huge map will load slowly and it will not work
class Map
{
	Constants::ZoneCoords m_coords;

	int m_maxDepth{};
	Zone* m_currentZone{};
	Player* m_mainPlayer{};

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

	void addObj(Entity& entity, const bool& useDeleteWhenRemoved);
	void addObj(BasicBlock& basicBlock, const bool& useDeleteWhenRemoved);
	void addObj(Text& text, const bool& useDeleteWhenRemoved);

	Constants::ZoneCoords& coords() {
		return m_coords;
	}

	Zone* getZone(Object* obj) const;

#ifdef _DEBUG
private:
	static inline ObjectsCount mS_objectsCount{};
#endif
};


