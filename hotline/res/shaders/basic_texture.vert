#version 330 core

uniform mat4 view_proj, model;
layout(location = 0) in vec2 pos;
layout(location = 1) in vec2 texcoord;

out vec2 tc;

void main() {
	tc = texcoord;
	gl_Position = view_proj * model * vec4(pos, 0.0, 1.0);
}
