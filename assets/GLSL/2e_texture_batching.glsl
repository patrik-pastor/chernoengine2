#type vertex
#version 330 core

layout(location = 0) in vec3 a_pos;
layout(location = 1) in vec4 a_color;
layout(location = 2) in vec2 a_texcoord;
layout(location = 3) in float a_texindex;
layout(location = 4) in float a_tilingfactor;

out vec4 v_color;
out vec2 v_texcoord;
out float v_texindex;
out float v_tilingfactor;

uniform mat4 u_view_projection;

void main()
{
	v_color = a_color;
	v_texcoord = a_texcoord;
	v_texindex = a_texindex;
	v_tilingfactor = a_tilingfactor;
	gl_Position = u_view_projection * vec4(a_pos, 1.0);
}

#type fragment
#version 330 core

in vec4 v_color;
in vec2 v_texcoord;
in float v_texindex;
in float v_tilingfactor;
 
out vec4 color;

uniform sampler2DArray u_textures;

void main()
{
        color = texture(u_textures, vec3(v_texcoord.xy * v_tilingfactor, v_texindex)) * v_color;
}

