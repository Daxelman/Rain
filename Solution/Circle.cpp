#include "Circle.h"


Circle::Circle(glm::vec2 anOrigin, GLfloat aRadius)
{
	origin = new glm::vec2(anOrigin);
	radius = aRadius;
	GeneratePoints();
	Init();
}

Circle::Circle(const Circle& otherCircle)
{
	origin = new glm::vec2(*otherCircle.origin);
	radius = otherCircle.radius;
	GeneratePoints();
	Init();
}

Circle& Circle::operator=(const Circle& otherCircle)
{
	delete origin; // Demonstration of difference between assignment and copy ctor.
	origin = new glm::vec2(*otherCircle.origin); // Point to different memory but with same x/y coordinates.
	radius = otherCircle.radius;
	GeneratePoints();
	Init();

	return *this;
}

void Circle::Init()
{
	// Create a vertex array object
    GLuint vao;
    glGenVertexArrays( 1, &vao );
    glBindVertexArray( vao );

	// Create and initialize a buffer object for each circle.
	GLuint aBuffer;
    glGenBuffers( 1, &aBuffer );
	myBuffer = aBuffer;
    glBindBuffer( GL_ARRAY_BUFFER, myBuffer );
    glBufferData( GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW );

	// Load shaders and use the resulting shader program
	GLuint program = CompileShader( "Shaders\\vshader.glsl", "Shaders\\fshader.glsl" );
	myShaderProgram = program;
    glUseProgram( myShaderProgram );

	// Initialize the vertex position attribute from the vertex shader
    GLuint loc = glGetAttribLocation( myShaderProgram, "vPosition" );
    glEnableVertexAttribArray( loc );
    glVertexAttribPointer( loc, 2, GL_FLOAT, GL_FALSE, 0, (void*)0 );
}

void Circle::Translate(glm::vec2 aVector)
{
	*origin += aVector;

	// Need to regenerate points and re-create buffer once we move origin - if only we could somehow not have to do this :)
	GeneratePoints(); 
	Init();
}

void Circle::Render(void)
{
	// Use the buffer and shader for each circle.
	glUseProgram( myShaderProgram );
	glBindBuffer( GL_ARRAY_BUFFER, myBuffer );

	// Initialize the vertex position attribute from the vertex shader.
    GLuint loc = glGetAttribLocation( myShaderProgram, "vPosition" );
    glEnableVertexAttribArray( loc );
    glVertexAttribPointer( loc, 2, GL_FLOAT, GL_FALSE, 0, (void*)0 );

	// Something's a bit off still - Each circle needs its own buffer even though the points are the same, just with a different origin!
	// If only we could have a single set of vertices in a single buffer and just draw it a tiny bit differently n times... :)
	glDrawArrays(GL_TRIANGLE_FAN, 0, NUM_VERTICES);
}

void Circle::GeneratePoints(void)
{
	GLfloat x, y, theta = 0;
	for (int i = 0; i < NUM_VERTICES; i++) 
	{
		// you could condense the following, but I expanded it to clarify the algorithm:
		theta += static_cast<GLfloat>(2*M_PI/NUM_VERTICES);
		x = static_cast<GLfloat>(radius*cos(theta));
		y = static_cast<GLfloat>(radius*sin(theta));
		// Offset the x and y coordinate by the origin, thus displacing the circle.
		x += origin->x;
		y += origin->y;
		points[i] = glm::vec2(x,y);
	}
}

glm::vec2 Circle::GetOrigin(void)
{
	return *origin;
}

GLfloat Circle::GetRadius(void)
{
	return radius;
}

Circle::~Circle(void)
{
	delete origin; // Demonstration of needing to clean up in destructor.
}
