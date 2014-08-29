#pragma once

#include <iostream>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class MyCamera
{
private:
	glm::vec3 _position;
    float _horizontalAngle;
    float _verticalAngle;
    float _fieldOfView;
    float _nearPlane;
    float _farPlane;
    float _viewportAspectRatio;

    void normalizeAngles();

public:
	MyCamera(void);
	~MyCamera(void);

	//position of camera
	const glm::vec3& position() const;
	void setPosition(const glm::vec3& position);
	void offsetPosition(const glm::vec3& offset);

	//vertical viewing angle of camera
	float fieldOfView() const;
	void setFieldOfView(float fieldOfView);


	//closest visible distance
	float nearPlane() const;

	//farthest visible distance
	float farPlane() const;

	// sets near and far plane distances
	void setNearAndFarPlanes(float nearPlane, float farPlane);

	//rotation matrix which determines direction of camera
	glm::mat4 orientation() const;

	//offset the camera's orientation

	void offSetOrientation(float upAngle, float rightAngle);


	// position to look at
	void lookAt(glm::vec3 position);

	//viewport
	float viewPortAspectRatio() const;
	void setViewportAspectRatio(float viewPortAspectRatio);

	 // A unit vector representing the direction the camera is facing 
    glm::vec3 forward() const;

    // A unit vector representing the direction to the right of the camera
    glm::vec3 right() const;

    // A unit vector representing the direction out of the top of the camera
    glm::vec3 up() const;

	//combined camera trasformation matrix
	glm::mat4 matrix() const;

	//projection matrix
	glm::mat4 projection() const;

	// view matrix
	glm::mat4 view() const;

};