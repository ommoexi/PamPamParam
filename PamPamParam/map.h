#pragma once
#include "utils.h"
#include "entity.h"
#include "basicBlock.h"
#include "text.h"
#include "zone.h"
#include "player.h"
#include <type_traits>
#include "background.h"

// only add free store objects with addObj(obj) function
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

	std::vector<unsigned int> m_updateVectorsEachRadiusSize{};
	std::vector<unsigned int> m_updateVectorsEachRadiusTotalSize{}; // for indexes;
	unsigned int m_updateVectorsTotalSize{};

	ZoneVectors m_renderVectors{};

	std::vector<unsigned int> m_renderVectorsEachRadiusSize{};
	std::vector<unsigned int> m_renderVectorsEachRadiusTotalSize{};
	unsigned int m_renderVectorsTotalSize{};

	//sorts m_lowestZones then links lowestsZones
	void linkLowestZones();

	void setCurrentZone(const Object& obj);

	void setVectors(ZoneVectors& vectors, const unsigned int& radius, const unsigned int& vectorsTotalSize, 
		std::vector<unsigned int>vectorsEachRadiusTotalSize);
	void setVectorsEastZone(ZoneVectors& vectors, unsigned int radius, Zone* zone, int index, int counter,
		std::vector<unsigned int>& vectorsEachRadiusTotalIndexLeft);
	void setVectorsWestZone(ZoneVectors& vectors, unsigned int radius, Zone* zone, int index, int counter,
		std::vector<unsigned int>& vectorsEachRadiusTotalIndexLeft);
	void setVectorsZone(ZoneVectors& vectors, Zone* zone, const int& index);

	void vectorsEachRadiusSizeUpdate(std::vector<unsigned int>& vectorsEachRadiusSize, 
		std::vector<unsigned int>& vectorsEachRadiusTotalSize, unsigned int& radius, unsigned int& vectorsTotalSize);
	void updateVectorsEachRadiusSizeUpdate();
	void renderVectorsEachRadiusSizeUpdate();

	void setUpdateVectors();
	void setRenderVectors();

public:
	~Map();
	Map(const Map& map) = delete;
	Map& operator=(const Map& map) = delete;
	// minCellSize should be large >= 500
	Map(const Point& botLeft, const Point& topRight, const int& minCellSize, const unsigned int& updateRadius,
		const unsigned int& renderRadius, Player* player);

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

	const unsigned int& updateRadius() const {
		return m_updateRadius;
	}
	const unsigned int& renderRadius() const {
		return m_renderRadius;
	}

	void setUpdateRadius(const unsigned int& radius);
	void setRenderRadius(const unsigned int& radius);

	Player& mainPlayer() {
		return *m_mainPlayer;
	}

	// add free store entity only !!!!!!
	void addObj(Entity& entity);
	// add free store basicBlock only !!!!!!
	void addObj(BasicBlock& basicBlock);
	// add free store text only !!!!!!
	void addObj(Text& text);
	// add free store background only !!!!!!
	void addObj(Background& background);

#ifdef _DEBUG
private:
	static inline ObjectsCount mS_objectsCount{};
#endif
};


