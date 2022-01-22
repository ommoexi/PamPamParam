//#include "entity.h"
//
//void Entity::update() {
//}
//void Entity::draw(float x, float y, Camera& camera) const {
//	settingBasicUniforms(x, y, camera);
//	texture()->bind();
//	mesh()->draw();
//}
//
//Entity::Entity(const float& width, const float& height, const float& x, const float& y,
//	const float& degrees, Texture* texture):
//	Rectangle{width, height, x, y, Colors::white, degrees, texture} {
//#ifdef _DEBUG
//	DEBUG_CONSTRUCTOR_OBJ(this, Source_Files::entity_cpp, &mS_objectsCount);
//#endif // _DEBUG
//}
//
//Entity::~Entity() {
//#ifdef _DEBUG
//	if (debugDestructor()) {
//		DEBUG_DESTRUCTOR_OBJ(this, Source_Files::entity_cpp);
//		setDebugDestructor(false);
//	}
//
//#endif // _DEBUG
//}