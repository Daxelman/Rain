/*--------------------------------------------------------------------------------------------------
Created by Alberto Bobadilla (labigm@rit.edu) in 2014
--------------------------------------------------------------------------------------------------*/

#include "Application.h" //Include our application library
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")//this line hides the command window

const int NUM = 3;
glm::vec2 points[NUM] = { glm::vec2( 0.0, 0.0) , glm::vec2( 0.25, 0.25), glm::vec2( 0.5, 0.0) }; 
GLuint vao;
GLuint buffer;
GLuint loc;
GLuint program;
GLuint elapsedTimeUniform;
GLuint loopDurationUnf;

void init( void )
{
    // Create a vertex array object
    glGenVertexArrays( 1, &vao );
    glBindVertexArray( vao );

    // Create and initialize a buffer object
    glGenBuffers( 1, &buffer );
    glBindBuffer( GL_ARRAY_BUFFER, buffer );
    glBufferData( GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW );

    // Load shaders and use the resulting shader program
	program = CompileShader( "Shaders//vshader.glsl", "Shaders//fshader.glsl" );
	glUseProgram( program );
	loc = glGetAttribLocation( program, "vPosition" );

	elapsedTimeUniform = glGetUniformLocation(program, "time");
	loopDurationUnf = glGetUniformLocation(program, "loopDuration");
	glUniform1f(loopDurationUnf, 1.0f);

    glEnableVertexAttribArray( loc );
    glVertexAttribPointer( loc, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*) (0) );
	
	glClearColor( 1.0, 1.0, 1.0, 1.0 ); // white background
}

void display( void )
{
	glClear(GL_COLOR_BUFFER_BIT);
	glUniform1f(elapsedTimeUniform, glutGet(GLUT_ELAPSED_TIME) / 1000.0f);
    glDrawArrays(GL_LINE_LOOP,0,NUM); 
	glutSwapBuffers();
	glutPostRedisplay();
}

int main( int argc, char **argv ) {
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_RGBA );
    glutInitWindowSize( 512, 512 );
    glutCreateWindow("Animated Triangle (Shader)");
	glewExperimental = GL_TRUE;
    glewInit();
	init();
    glutDisplayFunc( display );
    glutMainLoop();
    return 0;
}
