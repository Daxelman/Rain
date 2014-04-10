/*--------------------------------------------------------------------------------------------------
Created by Alberto Bobadilla (labigm@rit.edu) in 2014
--------------------------------------------------------------------------------------------------*/
#ifndef __CIRCLE_H_
#define __CIRCLE_H_

//Header to include all the necessary headers and definitions to our application.
#include "System.h"

const int NUM_VERTICES = 100; // Lower to increase performance but lower circle 'roundness'.

class Circle
{
	public:
		Circle(glm::vec2 anOrigin, GLfloat aRadius);
		Circle(const Circle& otherCircle);
		Circle& Circle::operator=(const Circle& otherCircle);
		virtual ~Circle(void);
		
		void Init(void);
		void Render(void);
		void Translate(glm::vec2 aVector);
		glm::vec2 GetOrigin(void);
		GLfloat GetRadius(void);
		
	private:
		void GeneratePoints(void);

		glm::vec2* origin;
		GLfloat radius;
		glm::vec2 points[NUM_VERTICES]; 
		GLuint  myShaderProgram;
		GLuint	myBuffer;
};

#endif //__CIRCLE_H_