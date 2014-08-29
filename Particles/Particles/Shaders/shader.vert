#version 150

in vec4 vPosition;
uniform float time;
uniform vec2 transform;
uniform float velocity;


float rand( float n, float p )
{
	return clamp(fract(sin(n)*43) * fract(cos(p)*43), 1.0, 10.0);
}


void main()
{
	float accel = rand(1, 100);
	mat4 scale = mat4(	0.005, 0, 0, 0,
						0, 0.005, 0, 0,
						0, 0, 1, 0,
						0, 0, 0, 1);

	vec2 pos = (vPosition * scale).xy;
	velocity += accel;
	pos.y -= (mod(time, 3) -1.5);

	pos.y *= velocity;1

	gl_Position = vec4(pos, 0, 1);
}