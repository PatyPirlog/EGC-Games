#version 330

uniform vec3 color;

layout(location = 0) out vec4 out_color;

void main()
{	
	out_color = vec4(abs(color), 1);
	//out_color = vec4(abs(1.0, 1.0, 0.0), 1);
}