#version 330 core

layout (location = 0) in vec2 pos;

uniform mat4 model, viewProj;

void main() {
	gl_Position = viewProj * model * vec4(pos, 0.0, 1.0);
}
