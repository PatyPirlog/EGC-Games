#version 330

// TODO: get values from fragment shader

in vec3 frag_normal;
in vec2 frag_text;
in vec3 frag_color;
in vec3 frag_position;

layout(location = 0) out vec4 out_color;

void main()
{
	// TODO: write pixel out color
	//out_color = vec4(1);
	out_color = vec4(frag_color, 1);
}