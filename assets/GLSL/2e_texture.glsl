#type vertex
#version 330 core

layout(location = 0) in vec3 a_pos;
layout(location = 1) in vec4 a_color;
layout(location = 2) in vec2 a_texcoord;

out vec2 v_texcoord;
out vec4 v_color;

uniform mat4 u_view_projection;

void main()
{
	v_texcoord = a_texcoord;
	v_color = a_color;
	gl_Position = u_view_projection * vec4(a_pos, 1.0);
}

#type fragment
#version 330 core

in vec2 v_texcoord;
in vec4 v_color;

out vec4 color;

uniform sampler2D u_texture;
uniform vec4 u_color;
uniform float u_tiling_factor;

void main()
{
        //color = texture(u_texture, v_texcoord * u_tiling_factor) * u_color;
	color = v_color;
}

