#pragma once
#include "rectangle.h"


class Entity :public Rectangle {
private:
	float m_gravity{ 3 };

protected:
public:
	Entity(const float& x, const float& y, const float& width, const float& height, const Texture* texture,
		const std::map<std::string, Animation>* animations = nullptr, const Constants::vec4& color = Colors::white);
	virtual ~Entity();

	virtual void update(std::vector<Object*>& objs) override;

#ifdef _DEBUG
private:
	static inline ObjectsCount mS_objectsCount{};
#endif
};