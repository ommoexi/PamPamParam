//#include "player.h"
//namespace {
//	Texture playerTexture{ std::string{"textures"} + Constants::pS + "player.png", GL_REPEAT, GL_REPEAT,
//	GL_NEAREST, GL_NEAREST, GL_RGBA, GL_RGBA, 0, 1 };
//
//}
//
//void Player::update() {
//
//}
//
//Player::Player(const float& width, const float& height, const float& x, const float& y,
//	const float& degrees) : Entity{width, height,x,y,degrees, &playerTexture} {
//#ifdef _DEBUG
//	DEBUG_CONSTRUCTOR_OBJ(this, Source_Files::player_cpp, &mS_objectsCount);
//#endif // _DEBUG
//}
//
//Player::~Player() {
//#ifdef _DEBUG
//	if (debugDestructor()) {
//		DEBUG_DESTRUCTOR_OBJ(this, Source_Files::player_cpp);
//		setDebugDestructor(false);
//	}
//
//#endif // _DEBUG
//}