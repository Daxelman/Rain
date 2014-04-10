/*--------------------------------------------------------------------------------------------------
Adapted by Alberto Bobadilla (labigm@rit.edu) in 2013
The following code is an adaptation of Angels Shader Compiler
--------------------------------------------------------------------------------------------------*/
#ifndef _ANGELSHADERCOMPILER_H
#define _ANGELSHADERCOMPILER_H

#include "System.h"

//  Define M_PI in the case it's not defined in the math header file
#ifndef M_PI
#  define M_PI  3.14159265358979323846
#endif

//  Helper function to load vertex and fragment shader files
GLuint CompileShader( const char* vertexShaderFile,
		   const char* fragmentShaderFile );

//  Defined constant for when numbers are too small to be used in the
//    denominator of a division operation.  This is only used if the
//    DEBUG macro is defined.
const GLfloat  DivideByZeroTolerance = GLfloat(1.0e-07);

//  Degrees-to-radians constant 
const GLfloat  DegreesToRadians = static_cast<GLfloat>(M_PI / 180.0);

#endif //_ANGELSHADERCOMPILER_H