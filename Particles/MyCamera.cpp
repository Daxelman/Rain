#define _USE_MATH_DEFINES
#include "MyCamera.h"

//max angle
static const float MAX_VERTICAL_ANGLE = 85.0f;

//convert to degrees
static inline float RadiansToDegrees(float rads){

	return rads * 180.0f / (float)M_PI;

}
// set variables
MyCamera::MyCamera(void) :
    _position(0.0f, 0.0f, 5.0f),
    _horizontalAngle(0.0f),
    _verticalAngle(0.0f),
    _fieldOfView(50.0f),
    _nearPlane(0.01f),
    _farPlane(100.0f),
    _viewportAspectRatio(4.0f/3.0f)
{
	
}


MyCamera::~MyCamera(void)
{
}

//get position 
const glm::vec3& MyCamera::position() const {
    return _position;
}
//set position
void MyCamera::setPosition(const glm::vec3& position) {
    _position = position;
}
//offset position
void MyCamera::offsetPosition(const glm::vec3& offset) {
    _position += offset;
}
//get fieldofView
float MyCamera::fieldOfView() const {
    return _fieldOfView;
}
//set fieldofView
void MyCamera::setFieldOfView(float fieldOfView) {
    assert(fieldOfView > 0.0f && fieldOfView < 180.0f);
    _fieldOfView = fieldOfView;
}
//get nearplane
float MyCamera::nearPlane() const {
    return _nearPlane;
}
//set nearplane
float MyCamera::farPlane() const {
    return _farPlane;
}
//set both planes
void MyCamera::setNearAndFarPlanes(float nearPlane, float farPlane) {
    assert(nearPlane > 0.0f);
    assert(farPlane > nearPlane);
    _nearPlane = nearPlane;
    _farPlane = farPlane;
}
//matrix for orientaion
glm::mat4 MyCamera::orientation() const {
    glm::mat4 orientation;
    orientation = glm::rotate(orientation, _verticalAngle, glm::vec3(1,0,0));
    orientation = glm::rotate(orientation, _horizontalAngle, glm::vec3(0,1,0));
    return orientation;
}
//matrix for offsetting orientation
void MyCamera::offSetOrientation(float upAngle, float rightAngle) {
    _horizontalAngle += rightAngle;
    _verticalAngle += upAngle;
    normalizeAngles();
}

void MyCamera::lookAt(glm::vec3 position) {
    assert(position != _position);
    glm::vec3 direction = glm::normalize(position - _position);
    _verticalAngle = RadiansToDegrees(asinf(-direction.y));
    _horizontalAngle = -RadiansToDegrees(atan2f(-direction.x, -direction.z));
    normalizeAngles();
}
//get viewportAspectRatio
float MyCamera::viewPortAspectRatio() const {
    return _viewportAspectRatio;
}
//set viewportAspectRatio
void MyCamera::setViewportAspectRatio(float viewportAspectRatio) {
    assert(viewportAspectRatio > 0.0);
    _viewportAspectRatio = viewportAspectRatio;
}
//move camera forward by applying matrix
glm::vec3 MyCamera::forward() const {
    glm::vec4 forward = glm::inverse(orientation()) * glm::vec4(0,0,-1,1);
    return glm::vec3(forward);
}
//move camera right by applying matrix
glm::vec3 MyCamera::right() const {
    glm::vec4 right = glm::inverse(orientation()) * glm::vec4(1,0,0,1);
    return glm::vec3(right);
}
//move camera up by applying matrix
glm::vec3 MyCamera::up() const {
    glm::vec4 up = glm::inverse(orientation()) * glm::vec4(0,1,0,1);
    return glm::vec3(up);
}
// getting the camera matrix
glm::mat4 MyCamera::matrix() const {
    return projection() * view();
}
//get projection matrix
glm::mat4 MyCamera::projection() const {
    return glm::perspective(_fieldOfView, _viewportAspectRatio, _nearPlane, _farPlane);
}
//get view matrix
glm::mat4 MyCamera::view() const {
    return orientation() * glm::translate(glm::mat4(), -_position);
}
//normalize angles (not used)
void MyCamera::normalizeAngles() {
    _horizontalAngle = fmodf(_horizontalAngle, 360.0f);
    //fmodf can return negative values, but this will make them all positive
    if(_horizontalAngle < 0.0f)
        _horizontalAngle += 360.0f;

    if(_verticalAngle > MAX_VERTICAL_ANGLE)
        _verticalAngle = MAX_VERTICAL_ANGLE;
    else if(_verticalAngle < -MAX_VERTICAL_ANGLE)
        _verticalAngle = -MAX_VERTICAL_ANGLE;
}