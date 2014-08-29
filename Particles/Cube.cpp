#include "Cube.h"
#define GLEW_STATIC

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

//make a cube
Cube::Cube(float cubeSize, glm::vec3 myColor)
{
	glGenVertexArrays(1, &vertexArray);
	glBindVertexArray(vertexArray);

	//cube verts
#pragma region //verts
	static const GLfloat g_vertex_buffer_data[] = {
    -cubeSize,-cubeSize,-cubeSize, // triangle 1 : begin
    -cubeSize,-cubeSize, cubeSize,
    -cubeSize, cubeSize, cubeSize, // triangle 1 : end
    cubeSize, cubeSize,-cubeSize, // triangle 2 : begin
    -cubeSize,-cubeSize,-cubeSize,
    -cubeSize, cubeSize,-cubeSize, // triangle 2 : end
    cubeSize,-cubeSize, cubeSize,
    -cubeSize,-cubeSize,-cubeSize,
    cubeSize,-cubeSize,-cubeSize,
    cubeSize, cubeSize,-cubeSize,
    cubeSize,-cubeSize,-cubeSize,
    -cubeSize,-cubeSize,-cubeSize,
    -cubeSize,-cubeSize,-cubeSize,
    -cubeSize, cubeSize, cubeSize,
    -cubeSize, cubeSize,-cubeSize,
    cubeSize,-cubeSize, cubeSize,
    -cubeSize,-cubeSize, cubeSize,
    -cubeSize,-cubeSize,-cubeSize,
    -cubeSize, cubeSize, cubeSize,
    -cubeSize,-cubeSize, cubeSize,
    cubeSize,-cubeSize, cubeSize,
    cubeSize, cubeSize, cubeSize,
    cubeSize,-cubeSize,-cubeSize,
    cubeSize, cubeSize,-cubeSize,
    cubeSize,-cubeSize,-cubeSize,
    cubeSize, cubeSize, cubeSize,
    cubeSize,-cubeSize, cubeSize,
    cubeSize, cubeSize, cubeSize,
    cubeSize, cubeSize,-cubeSize,
    -cubeSize, cubeSize,-cubeSize,
    cubeSize, cubeSize, cubeSize,
    -cubeSize, cubeSize,-cubeSize,
    -cubeSize, cubeSize, cubeSize,
    cubeSize, cubeSize, cubeSize,
    -cubeSize, cubeSize, cubeSize,
    cubeSize,-cubeSize, cubeSize
};

#pragma endregion
	
	glGenBuffers(1,&vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER,vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER,sizeof(g_vertex_buffer_data),g_vertex_buffer_data,GL_STATIC_DRAW);


	GLint vertexattrib;
	vertexattrib = glGetAttribLocation(ShaderFactory::GetInstance()->GetShaderAtIndex(0),"position");
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glEnableVertexAttribArray(vertexattrib);
	glVertexAttribPointer(vertexattrib,3,GL_FLOAT,GL_FALSE,0,(void*)0);


	GLint transformMat = glGetUniformLocation(ShaderFactory::GetInstance()->GetShaderAtIndex(0),"transformMat");

	glm::mat4 transform=glm::scale(glm::mat4(1),glm::vec3(.5f));

	glUniformMatrix4fv(transformMat, 1, GL_FALSE,glm::value_ptr(transform));

	GLint colorMat = glGetUniformLocation(ShaderFactory::GetInstance()->GetShaderAtIndex(0),"colorMat");

	glUniform3f(colorMat,myColor.x,myColor.y,myColor.z);

}


Cube::~Cube(void)
{

}

//draws cube
void Cube::drawCube()
{
	glBindVertexArray(vertexArray);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}