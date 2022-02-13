#pragma once
#include "utils.h"
#include "basicBlock.h"
class Zone {
private:
	Point m_botLeft{};
	Point m_topRight{};

	Zone* m_subZoneTopLeft{};
	Zone* m_subZoneTopRight{};
	Zone* m_subZoneBotLeft{};
	Zone* m_subZoneBotRight{};

	Zone* m_north{};
	Zone* m_east{};
	Zone* m_south{};
	Zone* m_west{};

	Zone(const Point& botLeft, const Point& topRight, const int& minCellSize, std::vector<Zone*>& lowestZones);
	friend class Map;

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

	const Point& botLeft() const {
		return m_botLeft;
	}
	const Point& topRight() const {
		return m_topRight;
	}

#ifdef _DEBUG
private:
	static inline ObjectsCount mS_objectsCount{};
#endif
};