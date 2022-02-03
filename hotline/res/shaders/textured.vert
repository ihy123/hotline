#version 330 core

layout(location = 0) in vec2 pos;
layout(location = 1) in vec2 texcoord;

out vec2 tc;

uniform mat4 model, viewProj;

void main() {
	tc = texcoord;
	gl_Position = viewProj * model * vec4(pos, 0.0, 1.0);
}
