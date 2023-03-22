#version 330 core

in vec3 v_pos;

out vec4 color;

void main()
{
	color = vec4(v_pos * 0.5 + 0.5, 1.0);
}
