#pragma once
#include "utils.h"
#include "entity.h"
#include "basicBlock.h"
#include "text.h"
#include "zone.h"
#include "player.h"
#include <type_traits>

class Map
{
private:
	static inline Zone mS_nullZone{};

	Constants::ZoneCoords m_coords;

	Zone* m_currentZone{};
	Player* m_mainPlayer{};

	std::vector<Zone*> m_lowestZones{};

	Zone* m_subZoneTopLeft{};
	Zone* m_subZoneTopRight{};
	Zone* m_subZoneBotLeft{};
	Zone* m_subZoneBotRight{};

	// 1 or larger
	unsigned int m_updateRadius{};
	unsigned int m_renderRadius{};

	ZoneVectors m_updateVectors{};
	ZoneVectors m_renderVectors{};

	//sorts m_lowestZones then links lowestsZones
	void linkLowestZones();

	void setCurrentZone(const Object& obj);

	void setVectors(ZoneVectors& vectors, unsigned int radius);
	void setVectorsEastZone(ZoneVectors& vectors, unsigned int radius, Zone* zone);
	void setVectorsWestZone(ZoneVectors& vectors, unsigned int radius, Zone* zone);
	void setVectorsZone(ZoneVectors& vectors, Zone* zone);
	void setUpdateVectors();
	void setRenderVectors();

	void addObj(Entity& entity);
	void addObj(BasicBlock& basicBlock);
	void addObj(Text& text);

public:
	~Map();
	Map(const Map& map) = delete;
	Map& operator=(const Map& map) = delete;
	// minCellSize should be large >= 500
	Map(const Point& botLeft, const Point& topRight, const int& minCellSize, const unsigned int& updateRadius,
		const unsigned int& renderRadius, Player* player);

	void addObj(Entity& entity, const bool& useDeleteWhenRemoved);
	void addObj(BasicBlock& basicBlock, const bool& useDeleteWhenRemoved);
	void addObj(Text& text, const bool& useDeleteWhenRemoved);

	const Constants::ZoneCoords& coords() const {
		return m_coords;
	}

	ZoneVectors& updateVectors() {
		return m_updateVectors;
	}
	ZoneVectors& renderVectors() {
		return m_renderVectors;
	}

	void update();

	Zone* getZone(const Object& obj) const;

#ifdef _DEBUG
private:
	static inline ObjectsCount mS_objectsCount{};
#endif
};


