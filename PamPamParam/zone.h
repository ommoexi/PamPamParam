#pragma once
#include "utils.h"
#include "basicBlock.h"
#include "entity.h"
#include "text.h"

struct ZoneVectors {
	std::vector<std::vector<Entity*>*> entities{};
	std::vector<std::vector<BasicBlock*>*> basicBlocks{};
	std::vector<std::vector<Text*>*> texts{};
};

class Zone {
private:
	// zone  functions are linked with map functions

	Constants::ZoneCoords m_coords;

	Zone* m_subZoneTopLeft{};
	Zone* m_subZoneTopRight{};
	Zone* m_subZoneBotLeft{};
	Zone* m_subZoneBotRight{};


	std::vector<Entity*> m_entities{};
	std::vector<BasicBlock*> m_basicBlocks{};
	std::vector<Text*> m_texts{};

	Zone* m_north{};
	Zone* m_east{};
	Zone* m_south{};
	Zone* m_west{};

	friend class Map;

	Zone(const Point& botLeft, const Point& topRight, const int& minCellSize, std::vector<Zone*>& lowestZones);
	// default constructor only for mS_nullZone in map.h
	Zone();

	Zone& setNorth(Zone* zone) {
		m_north = zone;
		return *this;
	}
	Zone& setEast(Zone* const zone) {
		m_east = zone;
		return *this;
	}
	Zone& setSouth(Zone* const zone) {
		m_south = zone;
		return *this;
	}
	Zone& setWest(Zone* const zone) {
		m_west = zone;
		return *this;
	}

	Zone* getZone(const Object& obj);

public:
	Zone(const Zone& zone) = delete;
	Zone& operator=(const Zone& zone) = delete;
	~Zone();

	Zone* subZoneTopLeft() const {
		return m_subZoneTopLeft;
	}

	Zone* subZoneTopRight() const {
		return m_subZoneTopRight;
	}

	Zone* subZoneBotLeft() const {
		return m_subZoneBotLeft;
	}

	Zone* subZoneBotRight() const {
		return m_subZoneBotRight;
	}

	Zone* north() const {
		return m_north;
	}

	Zone* east() const {
		return m_east;
	}

	Zone* south() const {
		return m_south;
	}

	Zone* west() const {
		return m_west;
	}

	const Constants::ZoneCoords& coords() const {
		return m_coords;
	}

	void addObj(Entity& entity);
	void addObj(BasicBlock& basicBlock);
	void addObj(Text& text);

	bool isObjInBounds(const Object& obj);


#ifdef _DEBUG
private:
	static inline ObjectsCount mS_objectsCount{};
#endif
};