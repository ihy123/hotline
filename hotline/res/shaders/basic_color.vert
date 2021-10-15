#version 330 core

uniform mat4 view_proj, model;
layout(location = 0) in vec2 pos;

void main() {
	gl_Position = view_proj * model * vec4(pos, 0.0, 1.0);
}