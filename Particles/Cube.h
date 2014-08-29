#pragma once
#include <SFML/Graphics.hpp>
#include <GL/glew.h>
#include <fstream>
#include <vector>
#include <sstream>
#include <iostream>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ShaderFactory.h"

class Cube
{
public:
	Cube(float cubeSize, glm::vec3 myColor);
	~Cube(void);
	void drawCube();
	GLuint vertexbuffer;
	GLuint vertexArray; 
};

