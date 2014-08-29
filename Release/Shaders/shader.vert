#version 330

layout (location = 0) in vec3 position;

uniform float time;
uniform float id;

//gives random
float rand(vec2 co)
{ 
	return abs(fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453)); 
}

void main()
{
	float new_time = time;

	//calc z position
	float id = position.z;
	vec2 new_pos = position.xy;

	//calc final velo
	vec2 accel = vec2(-rand(vec2(id, id)), -rand(vec2(id, id)));
	vec2 vel = vec2(0.1, 0.1) + accel * new_time;
	vel = clamp(vel, -id, -0.001);	//clamp velo
	new_pos += vec2(vel*new_time); //add final velo
	new_pos.y = mod(new_pos.y, 2) - 1;
	new_pos.x = mod(new_pos.x, 2) - 1;

	//calc new pos
	gl_Position = vec4(new_pos, 0, 1);
}