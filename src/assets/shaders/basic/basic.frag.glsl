#version 460 core

layout(location = 0) out vec4 color;

in vec2 v_LocalPosition;
in float v_Thickness;

void main() {
	float fade = 0.005;

	float alpha = 1;
	if (v_LocalPosition.x < -1) {
		alpha = smoothstep(0.0, fade, v_Thickness - distance(v_LocalPosition, vec2(-1, 0)));
	} else if (v_LocalPosition.x > 1) {
		alpha = smoothstep(0.0, fade, v_Thickness - distance(v_LocalPosition, vec2(1, 0)));
	} else {
		alpha = smoothstep(0.0, fade, v_Thickness - length(v_LocalPosition.y));
	}
	color = vec4(0, 0, 0, alpha);
}