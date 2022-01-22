//#pragma once
//#include "utils.h"
//#include "object.h"
//#include "shaders.h"
//
//// DE MODIFICAT MAI TARZIU
//class Rectangle : public Object {
//private:
//	static inline Mesh* mS_mesh{};
//
//	static Constants::vec2 p1(const float& x, const float& y, const Constants::vec2& rotTranslate)  {
//		return  Constants::vec2{ x - rotTranslate.x, y - rotTranslate.y };
//	}
//	static Constants::vec2 p2(const float& x, const float& y, const Constants::vec2& rotTranslate,
//		const Constants::vec2& xTransform) {
//		return Constants::vec2{ x + xTransform.x * 2 - rotTranslate.x  , 
//			y + xTransform.y * 2 - rotTranslate.y  };
//	}
//	static Constants::vec2 p3(const float& x, const float& y, const Constants::vec2& rotTranslate,
//		const Constants::vec2& yTransform) {
//		return Constants::vec2{ x + yTransform.x * 2 - rotTranslate.x  , 
//			y + yTransform.y * 2 - rotTranslate.y };
//	}
//	static Constants::vec2 p4(const float& x, const float& y, const Constants::vec2& rotTranslate,
//		const Constants::vec2& xTransform, const Constants::vec2& yTransform) {
//		return Constants::vec2{ x + xTransform.x  * 2+ yTransform.x * 2 - rotTranslate.x  ,
//			y + yTransform.y * 2 + xTransform.y * 2- rotTranslate.y };
//}
//
//protected:
//public:
//	Rectangle() = default;
//	Rectangle(const float& width, const float& height, const float& x, const float& y, 
//		const Constants::vec4& color,const float& degrees, Texture* texture);
//	virtual ~Rectangle();
//
//	static void init();
//	static void terminate();
//
//	//3		4
//	//1		2
//	//the points
//	const RectanglePoints getPoints() const;
//	const RectanglePoints getPointsWithoutRotation() const;
//
//	//const RectanglePoints getPreviousPoints() const;
//	const RectanglePoints getPreviousPointsWithoutRotation() const;
//
//	// only works for not rotated
//	bool rectangleCollisionWithoutRot(const Rectangle& rect) const;
//
//
//#ifdef _DEBUG
//private:
//	static inline ObjectsCount mS_objectsCount{};
//#endif
//};