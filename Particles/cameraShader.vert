#version 330
//SHADER FOR CAMERA DUH
layout (location = 0) in vec3 position;

uniform mat4 MVP;

void main()
{
	gl_Position = MVP * vec4(position,1);
}