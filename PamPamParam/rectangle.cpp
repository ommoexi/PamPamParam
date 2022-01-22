//#include "rectangle.h"
//
//
//bool Rectangle::rectangleCollisionWithoutRot(const Rectangle& rect) const {
//	RectanglePoints thesePoints{ getPointsWithoutRotation() };
//	RectanglePoints rectPoints{ rect.getPointsWithoutRotation() };
//
//	if (thesePoints.p1.x < rectPoints.p2.x && thesePoints.p2.x > rectPoints.p1.x &&
//		thesePoints.p1.y < rectPoints.p3.y && thesePoints.p3.y > rectPoints.p1.y) {
//		return true;
//	}
//		
//	return false;
//}
//
//Rectangle::Rectangle(const float& width, const float& height, const float& x, const float& y,
//	const Constants::vec4& color, const float& degrees, Texture* texture) :
//	Object{ width ,height, x,y, color, degrees,
//		&Shaders::I_basicShader, mS_mesh, texture } {
//#ifdef _DEBUG
//	DEBUG_CONSTRUCTOR_OBJ(this, Source_Files::square_cpp, &mS_objectsCount);
//#endif // _DEBUG
//}
//
//Rectangle::~Rectangle() {
//#ifdef _DEBUG
//	if (debugDestructor()) {
//		DEBUG_DESTRUCTOR_OBJ(this, Source_Files::square_cpp);
//		setDebugDestructor(false);
//	}
//
//#endif // _DEBUG
//
//}
//
//void Rectangle::init() {
//	const int verticesSize{ 16 };
//
//	float* vertices{ new float[verticesSize] {
//		//position coords	texture coords
//		0.0f, 0.0f,			0.0f, 0.0f,	//left down
//		2.0f, 0.0f, 		1.0f, 0.0f,	//right down
//		0.0f, 2.0f, 		0.0f, 1.0f,	//left up
//		2.0f, 2.0f, 		1.0f, 1.0f,	//right up	
//			}
//	};
//
//#ifdef _DEBUG
//	DEBUG_ADD_OBJ(vertices, Source_Files::rectangle_cpp, Rectangle, __func__);
//#endif
//
//	const int indicesSize{ 6 };
//	unsigned int* indices{ new unsigned int[indicesSize] {
//		0,1,2,
//		1,2,3
//	} };
//#ifdef _DEBUG
//	DEBUG_ADD_OBJ(indices, Source_Files::rectangle_cpp, Rectangle, __func__);
//#endif
//
//	mS_mesh = new Mesh{ vertices, verticesSize, Mesh::basicAttrib(),
//		Mesh::EDRAWMODES::triangles, indices, indicesSize };
//
//#ifdef _DEBUG
//	DEBUG_REMOVE_OBJ(vertices, Source_Files::rectangle_cpp, Rectangle, __func__, true);
//#endif
//	delete[] vertices;
//	vertices = nullptr;
//
//#ifdef _DEBUG
//	DEBUG_REMOVE_OBJ(indices, Source_Files::rectangle_cpp, Rectangle, __func__, true);
//#endif
//	delete[] indices;
//	indices = nullptr;
//}
//
//void Rectangle::terminate() {
//	delete mS_mesh;
//	mS_mesh = nullptr;
//}
//
//const RectanglePoints Rectangle::getPoints() const {
//	const float& _x{ x() };
//	const float& _y{ y() };
//	const Constants::vec2& _rotTranslate{ rotTranslate() };
//	const Constants::vec2& _xTransform{ xTransform() };
//	const Constants::vec2& _yTransform{ yTransform() };
//
//	const Constants::vec2 _p1{ p1(_x, _y, _rotTranslate) };
//	const Constants::vec2 _p2{ p2(_x, _y, _rotTranslate, _xTransform) };
//	const Constants::vec2 _p3{ p3(_x, _y, _rotTranslate, _yTransform) };
//	const Constants::vec2 _p4{ p4(_x, _y, _rotTranslate, _xTransform, _yTransform) };
//
//	return RectanglePoints{ _p1, _p2, _p3, _p4 };
//}
//
//
//const RectanglePoints Rectangle::getPointsWithoutRotation() const {
//
//	const float& _x{ x() };
//	const float& _y{ y() };
//	const float& _width { width() };
//	const float& _height{ height() };
//	const Constants::vec2 _p1{ _x, _y };
//	const Constants::vec2 _p2{ _x + _width, _y };
//	const Constants::vec2 _p3{ _x, _y + _height };
//	const Constants::vec2 _p4{ _x + _width, _y + _height };
//
//	return RectanglePoints{ _p1, _p2, _p3, _p4 };
//}
//
////const RectanglePoints Rectangle::getPreviousPoints() const {
////	const float& _x{ previousX() };
////	const float& _y{ previousY() };
////	const Constants::vec2& _rotTranslate{ previousRotTranslate() };
////	const Constants::vec2& _xTransform{ previousXTransform() };
////	const Constants::vec2& _yTransform{ previousYTransform() };
////
////	const Constants::vec2 _p1{ p1(_x, _y, _rotTranslate) };
////	const Constants::vec2 _p2{ p2(_x, _y, _rotTranslate, _xTransform) };
////	const Constants::vec2 _p3{ p3(_x, _y, _rotTranslate, _yTransform) };
////	const Constants::vec2 _p4{ p4(_x, _y, _rotTranslate, _xTransform, _yTransform) };
////
////	return RectanglePoints{ _p1, _p2, _p3, _p4 };
////}
//
//const RectanglePoints Rectangle::getPreviousPointsWithoutRotation() const {
//
//	const float& _x{ previousX() };
//	const float& _y{ previousY() };
//	const float& _width{ width() };
//	const float& _height{ height() };
//	const Constants::vec2 _p1{ _x, _y };
//	const Constants::vec2 _p2{ _x + _width, _y };
//	const Constants::vec2 _p3{ _x, _y + _height };
//	const Constants::vec2 _p4{ _x + _width, _y + _height };
//
//	return RectanglePoints{ _p1, _p2, _p3, _p4 };
//}
