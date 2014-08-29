#define GLEW_STATIC

#include <SFML/Graphics.hpp>
#include <GL/glew.h>
#include <fstream>
#include <vector>
#include <sstream>
#include <iostream>
#include <string>

#include "ShaderFactory.h"
int main()
{
	// SFML creates window
	sf::RenderWindow window(sf::VideoMode(800, 600), "Make it Rain",sf::Style::Close);
	sf::Clock clock = sf::Clock();

	// init GLEW
	glewExperimental = GL_TRUE;
	glewInit();

	// create the vertex array object
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// create the vertex buffer object and copy vertex data
	GLuint vbo;
	glGenBuffers(1, &vbo);

	GLfloat vertices[] = {
     0.0f,  0.5f, // Vertex 1 (X, Y)
     0.5f, -0.5f, // Vertex 2 (X, Y)
    -0.5f, -0.5f  // Vertex 3 (X, Y)
	};

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(render_vbo);
	glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0 , geometry_vbo);
	glBeginTransformFeedback(GL_TRIANGLES);
	//renderstuffgoeshere
	glEndTransformFeedback();

	//load update stuff
	glUseProgram(ShaderFactory::GetInstance()->GetShaderAtIndex(1));

	if(/*staying true for now*/true)
	{
		glBindVertexArray(vao[1]);
		glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, vbo[0]);
	}
	else
	{
		glBindVertexArray(vao[0]);
		glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, vbo[1]);
	}

	// create and compile vertex and fragment shader using ShaderFactory
	ShaderFactory::GetInstance()->LoadShaderFromFile("shaders/shader.vert", "shaders/shader.frag");
	glUseProgram(ShaderFactory::GetInstance()->GetShaderAtIndex(0));

	while(window.isOpen())
	{
        std::cout<<"Time: " << clock.getElapsedTime().asSeconds() << std::endl;
		#pragma region //closes the window
		sf::Event windowEvent;

		while (window.pollEvent(windowEvent))
		{
			switch(windowEvent.type)
			{
				//Stop the program from running after the window is closed
				case sf::Event::Closed:
					window.close();
					break;

				// Allows the escape key to close window
				case sf::Event::KeyPressed:
					if(windowEvent.key.code == sf::Keyboard::Escape)
						window.close();
					break;
			}
		}
#pragma endregion
		// clear the screen to black
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

		glBeginTransformFeedback(GL_POINTS);
		glDrawArrays(GL_POINTS, 0, 10); //hardcoded value for now
		glEndTransformFeedback();
		window.display();
	}

	// clean up after myself.
	glDeleteProgram(ShaderFactory::GetInstance()->shaderProgram);
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);

	return 0;
}