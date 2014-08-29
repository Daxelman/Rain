#include <GL/glew.h>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <vector>
#include <sstream>
#include <iostream>
#include <string>
#include <thread>

#include "ShaderFactory.h"
#include "Cube.h"
#include "MyCamera.h"

//GLM
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp"
#include "glm\gtx\transform.hpp"

using namespace glm;

//globals
GLuint vertexArray;
MyCamera camera;
GLuint colorUni;
GLuint cubeUni;


int main()
{
	// the maximum particles the program seems to take is around 300k
	const int maxParticles = 6000; 
	GLfloat particlesContainter[maxParticles];

	 srand (time(0)); //for random
	// SFML creates window
	sf::RenderWindow window(sf::VideoMode(800, 600), "Make it Rain",sf::Style::Close);
	sf::Clock clock = sf::Clock();

	// init GLEW
	glewExperimental = GL_TRUE;
	glewInit();

	//fill particle container
	for (int i = 0; i < maxParticles - 3; i += 3)
	{
		particlesContainter[i] = ((rand()%1000)/50.0f) - 1;
		particlesContainter[i + 1] = ((rand()%1000)/50.0f) - 1;
		particlesContainter[i + 2] = rand()%100;
	}

	//gen vao
	glGenVertexArrays(1, &vertexArray);
	glBindVertexArray(vertexArray);

	// generate the buffer, bind it making it the active buffer and then input the data
	GLuint particles_buffer;
	glGenBuffers(1, &particles_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, particles_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(particlesContainter), particlesContainter, GL_DYNAMIC_DRAW);

	//GLint posAttrib = glGetAttribLocation(ShaderFactory::GetInstance()->GetShaderAtIndex(0), "posID");
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	//load shaders
	ShaderFactory::GetInstance()->LoadShaderFromFile("shaders/shader.vert", "shaders/shader.frag");
	ShaderFactory::GetInstance()->LoadShaderFromFile("shaders/cameraShader.vert", "shaders/shader.frag");
	glUseProgram(ShaderFactory::GetInstance()->GetShaderAtIndex(0));
	GLuint elapsedTimeUniform = glGetUniformLocation(ShaderFactory::GetInstance()->GetShaderAtIndex(0), "time");
	GLuint idUni = glGetUniformLocation(ShaderFactory::GetInstance()->GetShaderAtIndex(0), "id");

	//load cube

	Cube myCube = Cube(1.0f,glm::vec3(1,0,0));
	float lastTime = clock.getElapsedTime().asSeconds();
	while(window.isOpen())
	{
		float thisTime = clock.getElapsedTime().asSeconds();

        //std::cout<<"Time: " << current << std::endl;
		// clear the screen to black
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(ShaderFactory::GetInstance()->GetShaderAtIndex(0));

		//creating the initial colour uniform 
		colorUni = glGetUniformLocation(ShaderFactory::GetInstance()->GetShaderAtIndex(0),"color");
		glUniform3f(colorUni,100/255.0f,149/255.0f,237/255.0f);

		//clocks
		float current = clock.getElapsedTime().asSeconds();

		glUniform1f(elapsedTimeUniform, current);

		//bind the VAO in order to switch between the Cube buffer and particles buffer
		glBindVertexArray(vertexArray);

		// make the first buffer the active buffer
		glBindBuffer(GL_ARRAY_BUFFER, particles_buffer);
		glEnableVertexAttribArray(0);

		glDrawArrays(GL_POINTS, 0, maxParticles);

		//passing the variables into the shader.frag
		glUseProgram(ShaderFactory::GetInstance()->GetShaderAtIndex(1));
		colorUni = glGetUniformLocation(ShaderFactory::GetInstance()->GetShaderAtIndex(1),"color");
		glUniform3f(colorUni,1,0,0);

		//creating the MVP matrix to pass into the shader
		mat4 View = camera.matrix();
		mat4 Model = (rotate(Model, 45.0f, vec3(0,1,0)));
		mat4 MVP = View * Model;
		
		//camera shader
		cubeUni = glGetUniformLocation(ShaderFactory::GetInstance()->GetShaderAtIndex(1),"MVP");
		glUniformMatrix4fv(cubeUni,1,false,glm::value_ptr(camera.matrix()));
	
		//its hard to see the camera movement, the cube makes it easier to see. 
		myCube.drawCube();

		window.display();

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
					//moves the camera forward (+z)
					if(windowEvent.key.code == sf::Keyboard::W){
						camera.offsetPosition((thisTime - lastTime) * 0.5f * camera.forward());
						lastTime = thisTime;
					}
					//moves the camera backwards (-z) 
					if(windowEvent.key.code == sf::Keyboard::S){
						camera.offsetPosition((thisTime - lastTime) * 0.5f * -camera.forward());
						lastTime = thisTime;
					}
					//moves the camera left
					if(windowEvent.key.code == sf::Keyboard::A){
						camera.offsetPosition((thisTime - lastTime) * 0.5f * -camera.right());
						lastTime = thisTime;
					}
					//moves the camera right
					if(windowEvent.key.code == sf::Keyboard::D){
						camera.offsetPosition((thisTime - lastTime) * 0.5f * camera.right());
						lastTime = thisTime;
					}
					//moves the camera down
					if(windowEvent.key.code == sf::Keyboard::X){
						camera.offsetPosition((thisTime - lastTime) * 0.5f * -glm::vec3(0,1,0));
						lastTime = thisTime;
					}
					//moves the camera up
					if(windowEvent.key.code == sf::Keyboard::Z){
						camera.offsetPosition((thisTime - lastTime) * 0.5f * glm::vec3(0,1,0));
						lastTime = thisTime;
					}
					break;
			}
			
			//attemping to add mouse movements to manipulate the camera 
			//const float mouseSensitivity = 0.1;
			// int mouseX, mouseY;
			// glfwGetMousePos(&mouseX, &mouseY);
			// camera.offSetOrientation(mouseSensitivity * mouseY, mouseSensitivity * mouseX);
			// glfwSetMousePos(0, 0);

		}
#pragma endregion
	}

	// clean up after myself.
	glDeleteProgram(ShaderFactory::GetInstance()->shaderProgram);
	glDeleteBuffers(1, &particles_buffer);
}