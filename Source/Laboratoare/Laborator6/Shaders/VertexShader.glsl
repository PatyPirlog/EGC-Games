#version 330

// TODO: get vertex attributes from each location
layout(location = 0) in vec3 v_position;
layout(location = 3) in vec3 v_normal;
layout(location = 2) in vec2 v_text;
layout(location = 1) in vec3 v_color;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform float Time;

// TODO: output values to fragment shader
out vec2 frag_text;
out vec3 frag_normal;
out vec3 frag_color;
out vec3 frag_position;

void main()
{
	// TODO: send output to fragment shader
	frag_position = v_position;
	frag_color = Time * v_color;
	frag_normal = v_normal;
	frag_text = v_text;

	// TODO: compute gl_Position
	gl_Position = Projection * View * Model * vec4(v_position, 1.0);
}
