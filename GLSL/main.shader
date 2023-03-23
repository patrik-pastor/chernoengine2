#shader vertex
#version 330 core

layout(location = 0) in vec3 a_pos;
layout(location = 1) in vec4 a_color;

out vec3 v_pos;
out vec4 v_color;

uniform mat4 u_view_projection;

void main()
{
	v_pos = a_pos;
	v_color = a_color;
	gl_Position = u_view_projection * vec4(a_pos, 1.0);
}

#shader fragment
#version 330 core
in vec3 v_pos;
in vec4 v_color;

out vec4 color;

void main()
{
        color = vec4(v_pos * 0.5 + 0.5, 1.0);
	color = v_color;
}

