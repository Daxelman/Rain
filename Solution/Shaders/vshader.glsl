#version 150

in vec4 vPosition;
uniform float time;
uniform float loopDuration;

void main()
{
	float timeScale = 3.14159f * 2.0f/loopDuration;
	float currTime = mod(time,loopDuration);
	vec4 offset = vec4(cos(currTime*timeScale)*0.5, 0.0f, 0.0f, 0.0f);
	gl_Position = vPosition + offset;
	}