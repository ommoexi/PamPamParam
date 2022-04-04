#include "map.h"


Map::Map(const Point& botLeft, const Point& topRight, const int& minCellSize, const unsigned int& updateRadius,
	const unsigned int& renderRadius, Player* mainPlayer) : m_coords{ botLeft, topRight }, m_updateRadius{ updateRadius },
	m_renderRadius{ renderRadius }, m_mainPlayer{ mainPlayer }
{
#ifdef _DEBUG
	DEBUG_CONSTRUCTOR_OBJ(this, Source_Files::map_cpp, &mS_objectsCount);
#endif

	if (m_updateRadius == 0) {
		m_updateRadius = 1;
	}
	if (m_renderRadius == 0) {
		m_renderRadius = 1;
	}

	updateVectorsEachRadiusSizeUpdate();
	renderVectorsEachRadiusSizeUpdate();

	if (!(mainPlayer->x() >= m_coords.x && mainPlayer->x() < m_coords.x2 && mainPlayer->y() >= m_coords.y && mainPlayer->y() <= m_coords.y2)) {
		mainPlayer->setX(static_cast<float>(m_coords.middleX));
		mainPlayer->setY(static_cast<float>(m_coords.middleY));
	}

	if (!(abs(m_coords.x2 - m_coords.x) <= minCellSize) &&
		!(abs(m_coords.y2 - m_coords.y) <= minCellSize))
	{
		m_subZoneTopLeft = new Zone{
		Point{m_coords.x, (m_coords.y + m_coords.y2) / 2 },
		Point{(m_coords.x + m_coords.x2) / 2, m_coords.y2}, minCellSize, m_lowestZones
		};

		m_subZoneTopRight = new Zone{
		Point{(m_coords.x + m_coords.x2) / 2, (m_coords.y + m_coords.y2) / 2}, Point{m_coords.x2, m_coords.y2}, minCellSize, m_lowestZones
		};

		m_subZoneBotLeft = new Zone{
		Point{m_coords.x, m_coords.y}, Point{(m_coords.x + m_coords.x2) / 2, (m_coords.y + m_coords.y2) / 2}, minCellSize, m_lowestZones
		};


		m_subZoneBotRight = new Zone{
		Point{(m_coords.x + m_coords.x2) / 2, m_coords.y },
		Point{m_coords.x2, (m_coords.y + m_coords.y2) / 2}, minCellSize, m_lowestZones
		};

	}

	if (m_subZoneBotLeft && m_subZoneBotRight && m_subZoneTopLeft && m_subZoneTopRight) {
		linkLowestZones();

		setCurrentZone(*m_mainPlayer);
		m_currentZone->addObj(*m_mainPlayer);

	}
	else {
#ifdef _DEBUG
		debugMessage("MAP TOO SMALL");
		m_currentZone = &mS_nullZone;
#endif
	}

}

void Map::linkLowestZones() {
	std::sort(m_lowestZones.begin(), m_lowestZones.end(), [](Zone*& leftZone, Zone*& rightZone)
		{
			return leftZone->coords().y < rightZone->coords().y;
		});
	size_t rowsColSize{ static_cast<size_t>(sqrt(m_lowestZones.size())) };
	size_t i{};
	for (size_t k{ rowsColSize }; k < m_lowestZones.size() + 1; i += rowsColSize, k += rowsColSize) {
		std::sort(m_lowestZones.begin() + i, m_lowestZones.begin() + k, [](Zone*& leftZone, Zone*& rightZone)
			{
				return leftZone->coords().x < rightZone->coords().x;
			});
	}
	// link horizontally
	for (size_t i{ rowsColSize }; i < m_lowestZones.size() + 1; i += rowsColSize) {
		for (size_t k{ i - rowsColSize + 1 }; k < i; k++) {
			Zone* leftZone{ m_lowestZones[k - 1] };
			Zone* rightZone{ m_lowestZones[k] };
			leftZone->setEast(rightZone);
			rightZone->setWest(leftZone);
		}
	}
	// link vertically
	for (size_t i{ }; i < rowsColSize; i++) {
		for (size_t k{ i + rowsColSize }; k < m_lowestZones.size(); k += rowsColSize) {
			Zone* downZone{ m_lowestZones[k - rowsColSize] };
			Zone* upZone{ m_lowestZones[k] };
			downZone->setNorth(upZone);
			upZone->setSouth(downZone);
		}
	}

}


void Map::setCurrentZone(const Object& obj) {
	Zone* zone{ getZone(obj) };
	if (zone) {
		m_currentZone = zone;
		setUpdateVectors();
		setRenderVectors();
	}
#ifdef _DEBUG
	else {
		debugMessage("CAN'T SET CURRENT ZONE OUT OF BOUNDS!\n");
	}
#endif
}

void Map::addObj(Entity& entity, const bool& useDeleteWhenRemoved) {
	Zone* zone{ getZone(entity) };
	if (zone) {
		entity.setUseDeleteWhenRemoved(useDeleteWhenRemoved);
		zone->addObj(entity);
	}
}
void Map::addObj(BasicBlock& basicBlock, const bool& useDeleteWhenRemoved) {
	Zone* zone{ getZone(basicBlock) };
	if (zone) {
		basicBlock.setUseDeleteWhenRemoved(useDeleteWhenRemoved);
		zone->addObj(basicBlock);
	}
}

void Map::addObj(Text& text, const bool& useDeleteWhenRemoved) {
	Zone* zone{ getZone(text) };
	if (zone) {
		text.setUseDeleteWhenRemoved(useDeleteWhenRemoved);
		zone->addObj(text);
	}
}

void Map::addObj(Entity& entity) {
	Zone* zone{ getZone(entity) };
	if (zone) {
		zone->addObj(entity);
	}
}
void Map::addObj(BasicBlock& basicBlock) {
	Zone* zone{ getZone(basicBlock) };
	if (zone) {
		zone->addObj(basicBlock);
	}
}
void Map::addObj(Text& text) {
	Zone* zone{ getZone(text) };
	if (zone) {
		zone->addObj(text);
	}
}

Zone* Map::getZone(const Object& obj) const {
	const float& x{ obj.x() };
	const float& y{ obj.y() };
	if (x >= m_coords.x && x <= m_coords.x2 && y >= m_coords.y && y <= m_coords.y2) {
		// left
		if (x <= m_coords.middleX) {
			//down
			if (y <= m_coords.middleY) {
				if (m_subZoneBotLeft) return m_subZoneBotLeft->getZone(obj);
			}
			//up
			else {
				if (m_subZoneTopLeft) return m_subZoneTopLeft->getZone(obj);
			}

		}
		// right
		else {
			//down
			if (y <= m_coords.middleY) {
				if (m_subZoneBotRight) return m_subZoneBotRight->getZone(obj);
			}
			//up
			else {
				if (m_subZoneTopRight) return m_subZoneTopRight->getZone(obj);
			}
		}
	}
#ifdef _DEBUG
	else {
		debugMessage("CANNOT GET ZONE WITH OBJ IN MAP OUT OF BOUNDS\n");
	}
#endif
	return nullptr;
}

Map::~Map() {
#ifdef _DEBUG
	DEBUG_DESTRUCTOR_OBJ(this, Source_Files::map_cpp);
#endif

	delete m_subZoneBotLeft;
	delete m_subZoneBotRight;
	delete m_subZoneTopLeft;
	delete m_subZoneTopRight;
}

void Map::setVectorsEastZone(ZoneVectors& vectors, unsigned int radius, Zone* zone, int index, int counter,
	std::vector<unsigned int>& vectorsEachRadiusTotalIndexLeft) {
	Zone* currentZone{ zone };
	while (radius && (currentZone = currentZone->east())) {
		if (--counter < 0) {
			index++;
		}
		unsigned int& currentIndex{ vectorsEachRadiusTotalIndexLeft[index] };
		currentIndex--;
		setVectorsZone(vectors, currentZone, currentIndex);
		radius--;
	}
}

void Map::setVectorsWestZone(ZoneVectors& vectors, unsigned int radius, Zone* zone, int index, int counter,
	std::vector<unsigned int>& vectorsEachRadiusTotalIndexLeft) {
	Zone* currentZone{ zone };
	while (radius && (currentZone = currentZone->west())) {
		if (--counter < 0) {
			index++;
		}
		unsigned int& currentIndex{ vectorsEachRadiusTotalIndexLeft[index] };
		currentIndex--;
		setVectorsZone(vectors, currentZone, currentIndex);
		radius--;
	}
}
void Map::setVectorsZone(ZoneVectors& vectors, Zone* zone, const int& index) {
	vectors.basicBlocks[index] = &zone->m_basicBlocks;
	vectors.texts[index] = &zone->m_texts;
	vectors.entities[index] = &zone->m_entities;
}

void Map::setVectors(ZoneVectors& vectors, const unsigned int& radius, const unsigned int& vectorsTotalSize,
	std::vector<unsigned int>vectorsEachRadiusTotalSize) {

	vectors.basicBlocks.resize(vectorsTotalSize);
	vectors.entities.resize(vectorsTotalSize);
	vectors.texts.resize(vectorsTotalSize);

	int index{ 0 };
	int counter{ 0 };
	setVectorsZone(vectors, m_currentZone, index);
	unsigned int westAndEastRadius{ radius - 1 };

	setVectorsEastZone(vectors, westAndEastRadius, m_currentZone, index, counter, vectorsEachRadiusTotalSize);
	setVectorsWestZone(vectors, westAndEastRadius, m_currentZone, index, counter, vectorsEachRadiusTotalSize);

	Zone* upDownZone{ m_currentZone };
	unsigned int upDownRadius{ radius - 1 };
	while (upDownRadius && (upDownZone = upDownZone->north())) {
		index++;
		unsigned int& currentIndex{ vectorsEachRadiusTotalSize[index] };
		currentIndex--;
		counter++;
		setVectorsZone(vectors, upDownZone, currentIndex);
		setVectorsEastZone(vectors, westAndEastRadius, upDownZone, index, counter, vectorsEachRadiusTotalSize);
		setVectorsWestZone(vectors, westAndEastRadius, upDownZone, index, counter, vectorsEachRadiusTotalSize);
		upDownRadius--;
	}

	index = 0;
	counter = 0;
	upDownZone = m_currentZone;
	upDownRadius = radius - 1;
	while (upDownRadius && (upDownZone = upDownZone->south())) {
		index++;
		unsigned int& currentIndex{ vectorsEachRadiusTotalSize[index] };
		currentIndex--;
		counter++;
		setVectorsZone(vectors, upDownZone, currentIndex);
		setVectorsEastZone(vectors, westAndEastRadius, upDownZone, index, counter, vectorsEachRadiusTotalSize);
		setVectorsWestZone(vectors, westAndEastRadius, upDownZone, index, counter, vectorsEachRadiusTotalSize);
		upDownRadius--;
	}

}


void Map::setUpdateVectors() {
	setVectors(m_updateVectors, m_updateRadius, m_updateVectorsTotalSize, m_updateVectorsEachRadiusTotalSize);
}
void Map::setRenderVectors() {
	setVectors(m_renderVectors, m_renderRadius, m_renderVectorsTotalSize, m_renderVectorsEachRadiusTotalSize);
}


void Map::update() {
	unsigned int& lastRing{ m_updateVectorsEachRadiusSize.back() };

	for (size_t i{}; i < m_updateVectors.entities.size() - lastRing; i++) {
		auto& entities{ *m_updateVectors.entities[i] };
		for (size_t k{}; k < entities.size();) {
			Entity& entity{ *entities[k] };
			if (entity.isRemoveFromVector()) {
				if (entity.useDeleteWhenRemoved()) {
					delete& entity;
				}
				entities.erase(entities.begin() + k);
			}
			else if (!entity.isInBounds()) {
				entities.erase(entities.begin() + k);
				addObj(entity);
			}
			else {
				entity.update(m_updateVectors.entities, m_updateVectors.basicBlocks);
				k++;
			}
		}
	}

	for (size_t i{}; i < m_updateVectors.basicBlocks.size() - lastRing; i++) {
		auto& basicBlocks{ *m_updateVectors.basicBlocks[i] };
		for (size_t k{}; k < basicBlocks.size();) {
			BasicBlock& basicBlock{ *basicBlocks[k] };
			if (basicBlock.isRemoveFromVector()) {
				if (basicBlock.useDeleteWhenRemoved()) {
					delete& basicBlock;
				}
				basicBlocks.erase(basicBlocks.begin() + k);
			}
			else if (!basicBlock.isInBounds()) {
				basicBlocks.erase(basicBlocks.begin() + k);
				addObj(basicBlock);
			}
			else {
				k++;
				if (Input::mouse.isLeftClick() && Input::mouse.isCollideWithCamAndZoom(basicBlock)) {
					basicBlock.setRemoveFromVector(true);
				}
			}
		}
	}

	for (size_t i{}; i < m_updateVectors.texts.size() - lastRing; i++) {
		auto& texts{ *m_updateVectors.texts[i] };
		for (size_t k{}; k < texts.size();) {
			Text& text{ *texts[k] };
			if (text.isRemoveFromVector()) {
				if (text.useDeleteWhenRemoved()) {
					delete& text;
				}
				texts.erase(texts.begin() + k);
			}
			else if (!text.isInBounds()) {
				texts.erase(texts.begin() + k);
				addObj(text);
			}
			else {
				k++;
			}
		}
	}

	if (!m_currentZone->isObjInBounds(*m_mainPlayer)) {
		setCurrentZone(*m_mainPlayer);
	}

}


void Map::vectorsEachRadiusSizeUpdate(std::vector<unsigned int>& vectorsEachRadiusSize,
	std::vector<unsigned int>& vectorsEachRadiusTotalSize, unsigned int& radius, unsigned int& vectorsTotalSize) {
	vectorsEachRadiusSize.clear();
	vectorsEachRadiusTotalSize.clear();
	vectorsEachRadiusSize.push_back(1);
	vectorsEachRadiusTotalSize.push_back(1);
	vectorsTotalSize = 1;
	for (unsigned int i{ 1 }; i < radius; i++) {
		unsigned int value{ 8 * i };
		vectorsEachRadiusSize.push_back(value);
		vectorsEachRadiusTotalSize.push_back(vectorsEachRadiusTotalSize[i - 1] + value);
		vectorsTotalSize += value;
	}
}

void Map::updateVectorsEachRadiusSizeUpdate() {
	vectorsEachRadiusSizeUpdate(m_updateVectorsEachRadiusSize, m_updateVectorsEachRadiusTotalSize, m_updateRadius, m_updateVectorsTotalSize);
}


void Map::renderVectorsEachRadiusSizeUpdate() {
	vectorsEachRadiusSizeUpdate(m_renderVectorsEachRadiusSize, m_renderVectorsEachRadiusTotalSize, m_renderRadius, m_renderVectorsTotalSize);
}

void Map::setUpdateRadius(const unsigned int& radius) {
	if (radius == 0) {
		m_updateRadius = 1;
	}
	else {
		m_updateRadius = radius;
	}
	updateVectorsEachRadiusSizeUpdate();
	setUpdateVectors();
}
void Map::setRenderRadius(const unsigned int& radius) {
	if (radius == 0) {
		m_renderRadius = 1;
	}
	else {
		m_renderRadius = radius;
	}
	renderVectorsEachRadiusSizeUpdate();
	setRenderVectors();
}