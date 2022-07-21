#version 460 core

layout(location = 0) out vec4 color;

in vec2 v_LocalPosition;
in float v_Thickness;

void main() {
	float alpha = 1;
	if (v_LocalPosition.x < -1) {
		if (distance(v_LocalPosition, vec2(-1, 0)) > v_Thickness) {
			alpha = 0;
		}
	} else if (v_LocalPosition.x > 1) {
		if (distance(v_LocalPosition, vec2(1, 0)) > v_Thickness) {
			alpha = 0;
		}
	}
	color = vec4(0, 0, 0, alpha);
}