#version 460 core

layout(location = 0) out vec4 color;

in vec2 v_LocalPosition;
in float v_LocalLength;

void main() {
	float fade = 0.1;

	float alpha = 1;
	if (v_LocalPosition.x < -v_LocalLength) {
		alpha = smoothstep(0.0, fade, 1 - distance(v_LocalPosition, vec2(-v_LocalLength, 0)));
	} else if (v_LocalPosition.x > v_LocalLength) {
		alpha = smoothstep(0.0, fade, 1 - distance(v_LocalPosition, vec2(v_LocalLength, 0)));
	} else {
		alpha = smoothstep(0.0, fade, 1 - length(v_LocalPosition.y));
	}
	color = vec4(0, 0, 0, alpha);
}