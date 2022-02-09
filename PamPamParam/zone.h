#pragma once
#include "utils.h"
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

	Zone(const Point& botLeft, const Point& topRight, const int& minCellSize, int& mapMaxDepth);
	friend class Map;

	Zone& setNorth(Zone*& zone) {
		m_north = zone;
		return *this;
	}
	Zone& setEast(Zone*& zone) {
		m_east = zone;
		return *this;
	}
	Zone& setSouth(Zone*& zone) {
		m_south = zone;
		return *this;
	}
	Zone& setWest(Zone*& zone) {
		m_west = zone;
		return *this;
	}

public:
	Zone(const Zone& zone) = delete;
	Zone& operator=(const Zone& zone) = delete;
	~Zone();

	Zone* const subZoneTopLeft() const {
		return m_subZoneTopLeft;
	}

	Zone* const subZoneTopRight() const {
		return m_subZoneTopRight;
	}

	Zone* const subZoneBotLeft() const {
		return m_subZoneBotLeft;
	}

	Zone* const subZoneBotRight() const {
		return m_subZoneBotRight;
	}

	Zone* const north() const {
		return m_north;
	}

	Zone* const east() const {
		return m_east;
	}

	Zone* const south() const {
		return m_south;
	}

	Zone* const west() const {
		return m_west;
	}


#ifdef _DEBUG
private:
	static inline ObjectsCount mS_objectsCount{};
#endif
};