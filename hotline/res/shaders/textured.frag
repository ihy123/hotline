#version 330 core

in vec2 tc;

out vec4 col;

uniform sampler2D tex0;

void main() {
	col = texture(tex0, tc);
}
