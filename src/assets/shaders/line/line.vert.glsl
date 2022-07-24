#version 460 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 localPosition;
layout(location = 2) in float localLength;

out vec2 v_LocalPosition;
out float v_LocalLength;

void main() {
	gl_Position = position;
	v_LocalPosition = localPosition;
	v_LocalLength = localLength;
}