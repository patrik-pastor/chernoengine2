#type vertex
#version 330 core

layout(location = 0) in vec3 a_pos;
layout(location = 1) in vec2 a_texcoord;

out vec2 v_texcoord;

uniform mat4 u_view_projection;
uniform mat4 u_transform;

void main()
{
	v_texcoord = a_texcoord;
	gl_Position = u_view_projection * u_transform * vec4(a_pos, 1.0);
}

#type fragment
#version 330 core
in vec2 v_texcoord;

out vec4 color;

uniform sampler2D u_texture;

void main()
{
        color = texture(u_texture, v_texcoord);
}

