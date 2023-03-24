#shader vertex
#version 330 core

layout(location = 0) in vec3 a_pos;

uniform mat4 u_view_projection;
uniform mat4 u_transform;

void main()
{
	gl_Position = u_view_projection * u_transform * vec4(a_pos, 1.0);
}

#shader fragment
#version 330 core
out vec4 color;

void main()
{
        color = vec4(0.2, 0.3, 0.8, 1.0);
}

