#include "constants.h"

namespace Constants {
	ZoneCoords::ZoneCoords(const Point& first, const Point& second) : x{ first.x }, y{ first.y },
		x2{ second.x }, y2{ second.y }, middleX{ (first.x + second.x) / 2 }, middleY{ (first.y + second.y) / 2 } {

	}

}