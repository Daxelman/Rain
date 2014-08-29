#include "ParticleSystem.h"
#include "ShaderFactory.h"
#include <SFML/Graphics.hpp>
#include <GL/glew.h>
#include <vector>
#include <math.h>


int vertexCount = 102;
GLuint render_vbo;
GLuint geometry_vbo;
GLuint vao;
GLuint vbo;


ParticleSystem::ParticleSystem(void)
{
}


ParticleSystem::~ParticleSystem(void)
{
}


void ParticleSystem::renderLoop(void)
{
	/*
	//load shaders
	ShaderFactory::GetInstance()->LoadShaderFromFile("shaders/shader.vert", "shaders/shader.frag");
	
	//load vertex stuff
	glUseProgram(ShaderFactory::GetInstance()->GetShaderAtIndex(0));
	//glUniformMatrix4fv(render_model__matrix_loc, 1, GL_FALSE, model_matrix);
	//glUniformMatrix4fv(render_projection_matrix_loc, 1, GL_FALSE, projection_matrix);

	glBindVertexArray(render_vbo);
	glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0 , geometry_vbo);
	glBeginTransformFeedback(GL_TRIANGLES);
	//renderstuffgoeshere
	glEndTransformFeedback();

	//load update stuff
	glUseProgram(ShaderFactory::GetInstance()->GetShaderAtIndex(1));
	//glUniformMatrix4fv(render_model__matrix_loc, 1, GL_FALSE, model_matrix);
	//glUniformMatrix4fv(render_projection_matrix_loc, 1, GL_FALSE, projection_matrix);

	//glUniform1i(triangle_count_loc, vertexCount / 3);

	//ping pong buffers i think
	if(true)
	{
		glBindVertexArray(vao[1]);
		glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, vbo[0]);
	}
	else
	{
		glBindVertexArray(vao[0]);
		glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, vbo[1]);
	}

	glBeginTransformFeedback(GL_POINTS);
	glDrawArrays(GL_POINTS, 0, 10); //hardcoded value for now
	glEndTransformFeedback();

	glBindVertexArray(0);

	//frame_count++;
	*/


}